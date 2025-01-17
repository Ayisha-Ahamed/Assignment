// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch AB6
// Program to print diamond.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

static int GetInt (char* prompt) {
   while (true) {
      printf ("%s : ", prompt);
      char input[15], * endptr = NULL;
      fgets (input, sizeof (input), stdin);
      if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
      errno = 0;
      int num = strtol (input, &endptr, 10);
      if (input[0] == '\n' || errno == ERANGE || *endptr != '\n' || num < 0 || num > 100)
         printf ("Please enter a valid number within [1-100] and press 'Enter'\n");
      else return num;
   }
}

static void PrintDiamond (int num) {
   int midLine = num + 1; // The middle line has to have num + 1 stars.
   for (int i = num * 2 + 1; i > 0; i--) {
      for (int j = 0; j < midLine; j++) {
         if (i >= midLine && j >= i % (midLine) || i < midLine && j >= midLine - i)
            printf ("%s ", "*");
         else printf ("%s ", "");
      }
      printf ("\n");
   }
}

int main () {
   do {
      system ("cls");
      PrintDiamond (GetInt ("Enter the height of the diamond [1-100]"));
      printf ("Would you like to give another input ? press 'y' ");
   } while (tolower (_getch ()) == 'y');
}