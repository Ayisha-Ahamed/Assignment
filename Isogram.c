// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch B11.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

// Returns if the input string is an isogram.
bool Isogram (char* str, int* error);

bool Isogram (char* str, int* error) {
   int alphabetTable[26], spaceCount = 0, letterCount = 0;
   // The integer array of 26 elements is set to zero to represent the initial count of alphabets.
   for (int i = 0; i < 26; i++) alphabetTable[i] = 0;
   for (int i = 0; i < strlen (str); i++) {
      int tableIndex = tolower (str[i]) - 'a';
      // Non-alphabetic characters are excluded for isogram detection.
      if (tableIndex >= 0 && tableIndex < 27) {
         letterCount++;
         // If the index holds a non-zero value, return false.
         if (alphabetTable[tableIndex]) return false;
         alphabetTable[tableIndex] += 1;
      } else if (isspace (str[i])) spaceCount++;
   }
   // If the string consists solely of space characters, return false.
   if (spaceCount == strlen (str)) {
      *error = -1;
      return false;
   }
   // If the string consists solely of non-alphabetic characters, return false.
   if (!letterCount) {
      *error = -2;
      return false;
   }
   return true;
}

static bool Continue () {
   printf ("Press 'y' to enter input ");
   return tolower (_getch ()) == 'y';
}

void main () {
   printf ("Isogram:\n");
   while (Continue ()) {
      system ("cls");
      char input[105];
      int error = 0;
      printf ("Enter input: ");
      fgets (input, sizeof (input), stdin);
      if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
      if (strlen (input) > 101) printf ("Input is too long\n");
      else {
         printf ("%s\n"RESET, Isogram (input, &error) ? CYAN"Isogram" : MAGENTA"Not an Isogram");
         switch (error) {
            case -1: printf ("Please enter a valid input string and press 'enter'\n"); break;
            case -2: printf ("Input string does not have any alphabetic characters\n"); break;
         }
      }
   }
}