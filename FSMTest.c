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
#include <stdlib.h>
#pragma warning (disable:4996)

#define MAX_STR 30
#define NTESTS 5

// FileCompare() method return values.
#define OUT_FILE_EOF -1  // Output file reached EOF before the reference file.
#define REF_FILE_EOF -2  // Reference file reached EOF before the output file.
#define MEM_ALLOC_ERROR -3  // Memory allocation error.
#define IDENTICAL_FILES 0   // Output and reference files are identical.

static int ExecProgram (char* exeFilePathAndName, char* inputFilePathAndName, char* outputFilePathAndName) 
{
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
   DWORD exitCode; // Stores the exit code from FSM6A.exe
   //CHeck if GetExitCodeProcess() has succeeded in retrieving the exit code.
   if (GetExitCodeProcess (pi.hProcess, &exitCode) && exitCode != 0) {
      // Non-zero return value indicates an error.
      printf ("FSM6A.exe exited with code %lu\nTest Failed\nTerminating program...\n", exitCode);
      CloseHandle (pi.hProcess);
      CloseHandle (pi.hThread);
      free (cmdline);
      exit (1);
   }
   // Close handles.
   CloseHandle (pi.hProcess);
   CloseHandle (pi.hThread);
   free (cmdline);
   return 0;
}

// Function to compare the output file with the reference file.
static int FileCompare (FILE* fRef, FILE* fOut, int* bitNo) {
   // Calculate the size of the file.
   fseek (fRef, 0L, SEEK_END);
   fseek (fOut, 0L, SEEK_END);
   size_t refSize = ftell (fRef), outSize = ftell (fOut);
   fseek (fRef, 0, SEEK_SET);
   fseek (fOut, 0, SEEK_SET);
   // If the files are of different size, return error code.
   if (refSize != outSize) return outSize < refSize ? OUT_FILE_EOF : REF_FILE_EOF;
   // To accommodate NULL character, size + 1 characters are dynamically allocated.
   char* fRefStr = malloc (refSize + 1), * fOutStr = malloc (outSize + 1);
   if (fRefStr == NULL || fOutStr == NULL) return MEM_ALLOC_ERROR;
   fread (fRefStr, 1, refSize, fRef);
   fread (fOutStr, 1, refSize, fOut);
   fRefStr[refSize] = '\0';
   fOutStr[outSize] = '\0';
   // Check if both files are same.
   if (!strcmp (fRefStr, fOutStr)) {
      free (fRefStr);
      free (fOutStr);
      return IDENTICAL_FILES;  // Two files are equal, successful comparision of files.
   }
   *bitNo = 0;
   char refChar = fRefStr[*bitNo], outChar = fOutStr[*bitNo];
   while (refChar != '\0' && outChar != '\0') {
      *bitNo += 1;
      if (refChar != outChar) break;
      refChar = fRefStr[*bitNo];
      outChar = fOutStr[*bitNo];
   }
   free (fRefStr);
   free (fOutStr);
   return refChar; // / Return reference character i.e expected bit at position *bitNo.
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
      if (ExecProgram (argv[1], input, output) != 0) printf ("Error executing test %d\n", i + 1);
      else {
         FILE* fRef = fopen (ref, "r"), * fOut = fopen (output, "r");
         if (fRef == NULL || fOut == NULL) {
            printf ("Error opening file: %s\n", fRef == NULL ? ref : output);
            continue;
         }
         int bitNo, result = FileCompare (fRef, fOut, &bitNo);
         switch (result) {
            case OUT_FILE_EOF: case REF_FILE_EOF:
               printf ("Error at bit no. %d %s reached EOF\n", bitNo + 1,
                       result == OUT_FILE_EOF ? output : ref); break;
            case MEM_ALLOC_ERROR: printf ("Error allocating memory\n"); break;
            case IDENTICAL_FILES: printf ("No error testing %s\n", input); break;
            default: printf ("Error at bit no. %d, Expected %d, Actual %d\n",
                             bitNo, result - '0', result == '0' ? 1 : 0); break;
         }
         if (result != IDENTICAL_FILES) {
            printf ("Test Failed\nTerminating the program....\n");
            return -1;
         }
         if (fRef) fclose (fRef);
         if (fOut) fclose (fOut);
      }
   }
   printf ("Test Passed\n");
   return 0;
}