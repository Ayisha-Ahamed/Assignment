// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// FSMTest.c
// Program on branch A6-B.
// Program for testing FSM6A.c.
// ------------------------------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#pragma warning (disable:4996)

#define MAX_STR 30
#define NTESTS 5

static int ExecProgram (char* exeFilePathAndName, char* inputFilePathAndName, char* outputFilePathAndName) {
   char* cmdline = malloc (strlen (exeFilePathAndName) + strlen (inputFilePathAndName) +
                           strlen (outputFilePathAndName) + 3);
   if (cmdline == NULL) {
      printf ("Unable to allocate memory\n");
      return 1;
   }
   sprintf (cmdline, "%s%s%s%s%s", exeFilePathAndName, " ", inputFilePathAndName, " ",
            outputFilePathAndName);

   // Set up structures for process information
   STARTUPINFOA si;
   PROCESS_INFORMATION pi;

   // Initialize memory for STARTUPINFO and PROCESS_INFORMATION structures
   ZeroMemory (&si, sizeof (si));
   si.cb = sizeof (si);
   ZeroMemory (&pi, sizeof (pi));

   // Attempt to create the process
   if (!CreateProcessA (
      NULL,            // Application name (NULL if using command line)
      cmdline,         // Command line (path to the executable)
      NULL,            // Process handle not inheritable
      NULL,            // Thread handle not inheritable
      FALSE,           // Set handle inheritance to FALSE
      0,               // No creation flags
      NULL,            // Use parent's environment block
      NULL,            // Use parent's starting directory
      &si,             // Pointer to STARTUPINFO structure
      &pi))            // Pointer to PROCESS_INFORMATION structure
   {
      // If CreateProcess fails, print an error message
      int err = GetLastError ();
      printf ("Failed to start process. Error: %lu\n", GetLastError ());
      free (cmdline);
      return 1;
   }

   // Wait until the process has finished execution
   WaitForSingleObject (pi.hProcess, INFINITE);

   // Close handles
   CloseHandle (pi.hProcess);
   CloseHandle (pi.hThread);

   free (cmdline);
   return 0;
}

// Function to compare the output file with the reference file
static int FileCompare (FILE* fRef, FILE* fOut, int* bitNo) {
   fseek (fRef, 0L, SEEK_END);
   fseek (fOut, 0L, SEEK_END);
   size_t refSize = ftell (fRef), outSize = ftell (fOut);
   fseek (fRef, 0, SEEK_SET);
   fseek (fOut, 0, SEEK_SET);
   char* fRefStr = malloc (refSize + 5), * fOutStr = malloc (outSize + 5);
   if (fRefStr == NULL || fOutStr == NULL) return -3;
   fread (fRefStr, 1, refSize, fRef);
   fread (fOutStr, 1, refSize, fOut);
   fRefStr[refSize] = '\0';
   fOutStr[outSize] = '\0';
   *bitNo = 0;
   char refChar = fRefStr[*bitNo], outChar = fOutStr[*bitNo];
   while (refChar != '\0' && outChar != '\0') {
      *bitNo += 1;
      if (refChar != outChar) {
         free (fRefStr);
         free (fOutStr);
         return refChar;
      }  // Return reference character
      refChar = fRefStr[*bitNo];
      outChar = fOutStr[*bitNo];
   }
   free (fRefStr);
   free (fOutStr);
   // To check if both the output and the reference files are of same length
   if (refChar != outChar)
      return outChar == '\0' ? -1 : -2;
   return 2; // Successful comparision of files
}

int main (int argc, char** argv) {
   char input[MAX_STR], output[MAX_STR] = "Files/temp.txt", ref[MAX_STR];
   int passCount = 0;
   if (argc != 2) {
      printf ("Usage: %s <FSM executable name>\n,", argv[0]);
      return -1;
   }
   printf ("FSM Test Harness\n");
   for (int i = 0; i < NTESTS; i++) {
      sprintf (input, "Files/test%dIn.txt", i + 1);
      sprintf (ref, "Files/test%dRef.txt", i + 1);
      if (ExecProgram (argv[1], input, output) != 0) printf ("Error executing test %d\n", i + 1);
      else {
         FILE* fRef = fopen (ref, "r"), * fOut = fopen (output, "r");
         if (fRef == NULL || fOut == NULL) {
            printf ("Error opening file: %s\n", fRef == NULL ? ref : output);
            continue;
         }
         int bitNo, result = FileCompare (fRef, fOut, &bitNo);
         switch (result) {
            case -1: case -2: printf ("Error at bit no. %d %s reached EOF\n",
                                      bitNo + 1, result == -1 ? output : ref); break;
            case -3: printf ("Error allocating memory\n"); break;
            case 2: printf ("No error testing %s\n", input); break;
            default: printf ("Error at bit no. %d, Expected %d, Actual %d\n",
                             bitNo, result - '0', result == '0' ? 1 : 0); break;
         }
         passCount += result - 1;
         if (result != -1) fclose (fRef);
         if (result != -2) fclose (fOut);
      }
   }
   printf ("Test %s\n", passCount == 5 ? "Pass" : "Fail");
}