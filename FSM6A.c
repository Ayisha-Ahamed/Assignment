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
#define FAIL 1
#define PASS 0

#include <stdio.h>
#include <malloc.h>

// States of the machine.
typedef enum {
   S0,  // Initial state.
   S1,  // After '0'
   S2,  // After '01'
   S3,  // After '011'
   T1,  // After '1'
   T2,  // After '11'
   T3,  // After '110'
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
   return S0;  // If the return value is not within the permissible states, return S0.
}

static int FSM (FILE* fIn, FILE* fOut) {
   // Calculate the size of the file.
   fseek (fIn, 0L, SEEK_END);
   size_t size = ftell (fIn);
   // Reset the file pointer to zeroth index.
   fseek (fIn, 0, SEEK_SET);
   // To accommodate NULL character size + 1 characters are dynamically allocated.
   char* fOutStr = malloc (size + 1), * fInStr = malloc (size + 1);
   if (fInStr == NULL || fOutStr == NULL) return FAIL;
   fread (fInStr, 1, size, fIn);
   fInStr[size] = '\0';
   State currentState = S0;  // Start in initial state.
   int output = 0, count = 0, input = fInStr[count];
   while (input == '0' || input == '1') {
      State nextState = NextState (currentState, input - '0', &output);
      if (nextState == S0) return FAIL; // Invalid output.
      currentState = nextState;
      fOutStr[count++] = output + '0';
      input = fInStr[count];
   };
   fOutStr[count] = '\0';
   fprintf (fOut, "%s", fOutStr);
   free (fOutStr);
   free (fInStr);
   return PASS;
}

int main (int argc, char* argv[]) {
   if (argc != 3) {
      printf ("FSM: Usage <input.txt> <output.txt>\n");
      return 1;
   }
   FILE* fIn = fopen (argv[1], "r"), * fOut = fopen (argv[2], "w");
   if (fIn == NULL || fOut == NULL) {
      printf ("FSM: Error opening file %s\n", fIn == NULL ? argv[1] : argv[2]);
      return 1;
   }
   if (FSM (fIn, fOut) != PASS) {
      printf ("FSM: Invalid state detected\n");
      return 1;
   };
   fclose (fOut);
   fclose (fIn);
   return 0;
}