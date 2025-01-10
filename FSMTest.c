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
#include <string.h>
#pragma warning (disable:4996)

#define MAX_STR 30
#define NTESTS 5
#define MEM_ALLOC_ERROR -3 // Memory allocation error.
#define MAGENTA "\033[1;35m"
#define RESET "\033[0m"

static int ExecProgram (char* exeFilePathAndName, char* inputFilePathAndName,
                        char* outputFilePathAndName) {
   char* cmdline = malloc (strlen (exeFilePathAndName) + strlen (inputFilePathAndName) +
                           strlen (outputFilePathAndName) + 3);
   if (cmdline == NULL) {
      printf ("Unable to allocate memory\n");
      return 1;
   }
   sprintf (cmdline, "%s%s%s%s%s", exeFilePathAndName, " ", inputFilePathAndName, " ",
            outputFilePathAndName);
   // Set up structures for process information.
   STARTUPINFOA si;
   PROCESS_INFORMATION pi;
   // Initialize memory for STARTUPINFO and PROCESS_INFORMATION structures.
   ZeroMemory (&si, sizeof (si));
   si.cb = sizeof (si);
   ZeroMemory (&pi, sizeof (pi));
   // Attempt to create the process
   if (!CreateProcessA (
      NULL,            // Application name (NULL if using command line).
      cmdline,         // Command line (path to the executable).
      NULL,            // Process handle not inheritable.
      NULL,            // Thread handle not inheritable.
      FALSE,           // Set handle inheritance to FALSE.
      0,               // No creation flags.
      NULL,            // Use parent's environment block.
      NULL,            // Use parent's starting directory.
      &si,             // Pointer to STARTUPINFO structure.
      &pi))            // Pointer to PROCESS_INFORMATION structure.
   {
      // If CreateProcess fails, print an error message.
      int err = GetLastError ();
      printf ("Failed to start process. Error: %lu\n", GetLastError ());
      free (cmdline);
      return 1;
   }
   // Wait until the process has finished execution.
   WaitForSingleObject (pi.hProcess, INFINITE);
   // Close handles.
   CloseHandle (pi.hProcess);
   CloseHandle (pi.hThread);
   free (cmdline);
   return 0;
}

// Checks whether the files are identical.
static int FileCompare (FILE* fRef, FILE* fOut, int* bitNo) {
   // Calculate the size of the file.
   fseek (fRef, 0L, SEEK_END);
   fseek (fOut, 0L, SEEK_END);
   size_t refSize = ftell (fRef), outSize = ftell (fOut);
   fseek (fRef, 0, SEEK_SET);
   fseek (fOut, 0, SEEK_SET);
   if (refSize != outSize) return -1; // Files are different.
   // To accommodate NULL character, size + 1 characters are dynamically allocated.
   char* fRefStr = malloc (refSize + 1), * fOutStr = malloc (outSize + 1);
   if (fRefStr == NULL || fOutStr == NULL) return MEM_ALLOC_ERROR;
   fread (fRefStr, 1, refSize, fRef);
   fread (fOutStr, 1, refSize, fOut);
   fRefStr[refSize] = '\0';
   fOutStr[outSize] = '\0';
   *bitNo = 0;
   char refChar = fRefStr[*bitNo], outChar = fOutStr[*bitNo];
   while (refChar != '\0') {
      *bitNo += 1;
      if (refChar != outChar) {
         free (fRefStr);
         free (fOutStr);
         return -2; // Files have different bit sequence.
      }
      refChar = fRefStr[*bitNo];
      outChar = fOutStr[*bitNo];
   }
   free (fRefStr);
   free (fOutStr);
   return 0; // Files are identical.
}

int main (int argc, char** argv) {
   char input[MAX_STR], output[MAX_STR] = "Files/temp.txt", ref[MAX_STR];
   if (argc != 2) {
      printf ("Usage: %s <FSM executable name>\n,", argv[0]);
      return -1;
   }
   printf ("FSM Test Harness\n");
   for (int i = 0; i < NTESTS; i++) {
      sprintf (input, "Files/test%dIn.txt", i + 1);
      sprintf (ref, "Files/test%dRef.txt", i + 1);
      if (ExecProgram (argv[1], input, output) != 0)
         printf ("Error executing test %d\n", i + 1);
      else {
         FILE* fRef = fopen (ref, "r"), * fOut = fopen (output, "r");
         if (fRef == NULL || fOut == NULL) {
            printf ("Error opening file: %s\n", fRef == NULL ? ref : output);
            continue;
         }
         int bitNo = 0, result = FileCompare (fRef, fOut, &bitNo);
         switch (result) {
            case -1: printf ("Error: %s Reference and output files are different\n", input); break;
            case -2: printf ("Error: %s Reference bit position: %d\n", input, bitNo); break;
            case -3: printf ("Error: %s Memory allocation error\n", input); break;
         }
         if (result != 0) {
            printf (MAGENTA"Test Failed\nTerminating program....\n"RESET);
            return -1;
         }
         if (fRef) fclose (fRef);
         if (fOut) fclose (fOut);
      }
   }
   printf ("Test Passed\n");
   return 0;
}