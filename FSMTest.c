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

#define MAX_STR_SIZE 20
#define NTESTS 5

typedef struct {
   char In[MAX_STR_SIZE];
   char Out[MAX_STR_SIZE];
   char Ref[MAX_STR_SIZE];
}Test;

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
   while ((refChar != EOF) && (outChar != EOF)) {
      *bitNo += 1;
      if (refChar != outChar) return refChar;  // Return reference character
      refChar = getc (ref);
      outChar = getc (fOut);
   }
   // To check if both the output and the reference files are of same length
   if (refChar != outChar)
      return refChar != EOF ? -1 : -2;
   return 2; // Successful comparision of files
}

int main (int argc, char** argv) {
   printf ("FSM Test Harness\n");
   if (argc != 2) {
      printf ("Usage: %s <FSM executable name>\n,", argv[0]);
      return -1;
   }
   Test Files[] = { { "test1In.txt","test1Out.txt","test1Ref.txt" },
                    { "test2In.txt","test2Out.txt","test2Ref.txt" },
                    { "test3In.txt","test3Out.txt","test3Ref.txt" },
                    { "test4In.txt","test4Out.txt","test4Ref.txt" },
                    { "test5In.txt","test5Out.txt","test5Ref.txt" }
   };
   for (int i = 0; i < NTESTS; i++) {
      if (ExecProgram (argv[1], Files[i].In, Files[i].Out) != 0) {
         printf ("Error executing test %d\n", i + 1);
      } else {
         FILE* ref = fopen (Files[i].Ref, "r");
         if (ref == NULL) {
            printf ("Error opening reference file: %s\n", Files[i].Ref);
            continue;
         }
         FILE* fOut = fopen (Files[i].Out, "r");
         if (fOut == NULL) {
            printf ("Error opening output file: %s\n", Files[i].Out);
            continue;
         }
         int bitNo, result = FileCompare (ref, fOut, &bitNo);
         switch (result) {
            case -1: {
               printf ("Error at bit no. %d %s reached EOF\n", bitNo + 1, Files[i].Out);
               break;
            }
            case -2: {
               printf ("Error at bit no. %d %s reached EOF\n", bitNo + 1, Files[i].Ref);
               break;
            }
            case 2: printf ("No error testing %s\n", Files[i].Ref); break;
            default: {
               printf ("Error at bit no. %d, ", bitNo);
               printf ("Expected %d, Actual %d\n", result - '0', result == '0' ? 1 : 0);
               break;
            }
         }
         if (result != -1) fclose (ref);
         if (result != -2) fclose (fOut);
      }
   }
}
