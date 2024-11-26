// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// FSMTest.c
// Program on branch A6B.
// Program for testing FSM6A.c.
// ------------------------------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#pragma warning (disable:4996)

#define MAX_STR 30
#define NTESTS 5

static int ExecProgram (char* exeFilePathAndName, char* inputFilePathAndName, char* outputFilePathAndName) {
   char* cmdline = malloc (strlen (exeFilePathAndName) + strlen (inputFilePathAndName) + strlen (outputFilePathAndName) + 3);
   if (cmdline == NULL) {
      printf ("Unable to allocate memory\n");
      return 1;
   }
   sprintf (cmdline, "%s%s%s%s%s", exeFilePathAndName, " ", inputFilePathAndName, " ", outputFilePathAndName);

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
static int FileCompare (FILE* ref, FILE* fOut, int* bitNo) {
   char refChar = getc (ref), outChar = getc (fOut);
   *bitNo = 0;
   while (refChar != EOF && outChar != EOF) {
      *bitNo += 1;
      if (refChar != outChar) return refChar;  // Return reference character
      refChar = getc (ref);
      outChar = getc (fOut);
   }
   // To check if both the output and the reference files are of same length
   if (refChar != outChar)
      return outChar == EOF ? -1 : -2;
   return 2; // Successful comparision of files
}

int main (int argc, char** argv) {
   if (argc != 2) {
      printf ("Usage: %s <FSM executable name>\n,", argv[0]);
      return -1;
   }
   printf ("FSM Test Harness\n");
   char input[MAX_STR], output[MAX_STR], ref[MAX_STR];
   for (int i = 0; i < NTESTS; i++) {
      sprintf (input, "Files/test%dIn.txt", i + 1);
      sprintf (output, "Files/test%dOut.txt", i + 1);
      sprintf (ref, "Files/test%dRef.txt", i + 1);
      if (ExecProgram (argv[1], input, output) != 0)
         printf ("Error executing test %d\n", i + 1);
      else {
         FILE* fRef = fopen (ref, "r"), * fOut = fopen (output, "r");
         if (fRef == NULL || fOut == NULL) {
            printf ("Error opening file: %s\n", fRef == NULL ? ref : output);
            continue;
         }
         int bitNo, result = FileCompare (fRef, fOut, &bitNo);
         if (result < 0) {    // If the reference and output files are of different length
            printf ("Error at bit no. %d %s reached EOF\n",
                    bitNo + 1, result == -1 ? output : ref);
            continue;
         }
         switch (result) {
            case 2: printf ("No error testing %s\n", input); break;
            default: printf ("Error at bit no. %d, Expected %d, Actual %d\n",
                             bitNo, result - '0', result == '0' ? 1 : 0); break;
         }
         if (result != -1) fclose (fRef);
         if (result != -2) fclose (fOut);
      }
   }
}