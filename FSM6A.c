// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// FSM6A.c
// Program on branch A6-B.
// Program identifies patterns '0110' and '1101' in a bit sequence.
// ------------------------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

// Returns the status of FSM execution.
int FSM (FILE* fIn, FILE* fOut);

// States of the machine.
typedef enum {
   S0,  // Initial state.
   S1,  // After '0'
   S2,  // After '01'
   S3,  // After '011'
   T1,  // After '1'
   T2,  // After '11'
   T3,  // After '110'
   INVALID // Error state.
} State;

// State transition diagram implementation.
static State NextState (State currentState, int input, int* output) {
   switch (currentState) {
      case S0:
         *output = 0;
         return input ? T1 : S1;
      case S1:
         *output = 0;
         return input ? S2 : S1;
      case S2:
         *output = 0;
         return input ? S3 : S1;
      case T1:
         *output = 0;
         return input ? T2 : S1;
      case T2:
         *output = 0;
         return input ? T2 : T3;
      case T3:
         *output = input;
         return input ? S2 : S1;
      case S3:
         *output = !input;
         return input ? T2 : T3;
   }
   return INVALID;  // Return value is not a valid state.
}

int FSM (FILE* fIn, FILE* fOut) {
   // Calculate the size of the file.
   fseek (fIn, 0L, SEEK_END);
   size_t size = ftell (fIn);
   // Reset the file pointer to zeroth index.
   fseek (fIn, 0, SEEK_SET);
   // To accommodate NULL character size + 1 characters are dynamically allocated.
   char* fOutStr = malloc (size + 1), * fInStr = malloc (size + 1);
   if (fInStr == NULL || fOutStr == NULL) return -1; // Memory allocation error.
   fread (fInStr, 1, size, fIn);
   fInStr[size] = '\0';
   State currentState = S0;  // Start in initial state.
   int output = 0, count = 0, input = fInStr[count];
   for (int i = 0; i < size; i++) {
      if (!(input == '0' || input == '1')) return -2; // Invalid valid.
      State nextState = NextState (currentState, input - '0', &output);
      if (nextState == INVALID) return -3; // Invalid state.
      currentState = nextState;
      fOutStr[count++] = output + '0';
      input = fInStr[count];
   };
   fOutStr[count] = '\0';
   fprintf (fOut, "%s", fOutStr);
   free (fOutStr);
   free (fInStr);
   return 0;
}

int main (int argc, char* argv[]) {
   if (argc != 3) {
      printf ("FSM: Usage <input.txt> <output.txt>\n");
      return -1;
   }
   FILE* fIn = fopen (argv[1], "r"), * fOut = fopen (argv[2], "w");
   if (fIn == NULL || fOut == NULL) {
      printf ("FSM: Error opening file %s\n", fIn == NULL ? argv[1] : argv[2]);
      return -1;
   }
   switch (FSM (fIn, fOut)) {
      case -1: printf ("FSM: %s Memory allocation error.\n", argv[1]); break;
      case -2: printf ("FSM: %s Invalid input.\n", argv[1]); break;
      case -3: printf ("FSM: %s Invalid state detected.\n", argv[1]); break;
   };
   fclose (fOut);
   fclose (fIn);
   return 0;
}