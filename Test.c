// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch AB9.
// Program to print Pascal's triangle.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "Header.h"

static void PrintTriangle (int noOfRows) {
   if (noOfRows <= 0 || noOfRows > 30) return;
   else {
      for (int row = 0; row <= noOfRows - 1; row++) {
         // Prints space characters.
         for (int i = 0; i < noOfRows - row; printf (" "), i++);
         // Prints numeric elements.
         for (int col = 0; col <= row; col++)
            printf ("%d%s", Combination (row, col), " ");
         printf ("\n");
      }
      printf ("\n");
   }
}

static int GetInt (char* prompt) {
   while (true) {
      printf ("%s: ", prompt);
      char input[15], * endptr = NULL;
      fgets (input, sizeof (input), stdin);
      if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
      errno = 0;
      int num = strtol (input, &endptr, 10);
      if (errno == ERANGE || *endptr != '\n' || num > 30 || num < 0)
         printf ("Please enter an integer within range [0-30]\n");
      else return num;
   }
}

int main () {
   int input;
   printf ("Pascal's Triangle\n");
   do {
      input = GetInt ("1. Enter 1 to give input\n2. Enter 0 to exit\nInput");
      system ("cls");
      if (input == 1)
         PrintTriangle (GetInt ("Enter the number of rows to print"));
   } while (input != 0);
   return 0;
}