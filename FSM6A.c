// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// FSM6A.c
// Program on branch A6B.
// Program that implements identification of patterns '0110' and '1101' in a bit sequence.
// ------------------------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS  1
#include <stdio.h>
#include <malloc.h>

// States of the machine
typedef enum {
   S0,  // Initial state
   S1,  // After '0'
   S2,  // After '01'
   S3,  // After '011'
   T1,  // After '1'
   T2,  // After '11'
   T3,  // After '110'
} State;

// State transition diagram implementation
static State NextState (State currentState, int input, int* output) {
   switch (currentState) {
      case S0:
         *output = 0;
         if (input == 0)
            return S1;
         else
            return T1;

      case S1:
         *output = 0;
         if (input == 1)
            return S2;
         else
            return S1;

      case S2:
         *output = 0;
         if (input == 1)
            return S3;
         else
            return S1;

      case S3:
         *output = 0;
         if (input == 0) {
            *output = 1;
            return T3;
         } else
            return T2;

      case T1:
         *output = 0;
         if (input == 1)
            return T2;
         else
            return S1;

      case T2:
         *output = 0;
         if (input == 0)
            return T3;
         else
            return T2;

      case T3:
         if (input == 1) {
            *output = 1;
            return S2;
         } else {
            *output = 0;
            return S1;
         }
   }
   return S0;  // Default return to initial state
}

static void FSM (FILE* fIn, FILE* fOut, char fOutStr[]) {
   State currentState = S0;  // Start in initial state
   int input = getc (fIn), output = 0, count = 0;
   while (input == '0' || input == '1') {
      currentState = NextState (currentState, input - '0', &output);
      fOutStr[count++] = output + '0';
      input = getc (fIn);
   };
   fOutStr[count] = '\0';
   fprintf (fOut, "%s", fOutStr);
}

int main (int argc, char* argv[]) {
   if (argc < 3) {
      printf ("FSM: Usage <input.txt> <output.txt>\n");
      return -1;
   }
   FILE* fIn = fopen (argv[1], "r");
   if (fIn == NULL) {
      printf ("FSM: Error opening input file %s. ", argv[1]);
      return -1;
   }
   FILE* fOut = fopen (argv[2], "w");
   if (fOut == NULL) {
      printf ("FSM: Error opening output file %s. ", argv[2]);
      return -1;
   }
   // Calculating the size of the file 
   fseek (fIn, 0L, SEEK_END);
   int size = ftell (fIn);
   // Rest the file pointer to zeroth index
   fseek (fIn, 0, SEEK_SET);
   char* fOutStr = malloc (size + 5);
   FSM (fIn, fOut, fOutStr);
   free (fOutStr);
   fclose (fOut);
   fclose (fIn);
   return 0;
}