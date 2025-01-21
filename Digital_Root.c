// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch main
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int DigitalRoot (int num) {
   if (num < 1) return 0;
   int sum = 0;
   while (num) {
      sum += num % 10;
      num /= 10;
   }
   if (sum < 10) return sum;
   else return DigitalRoot (sum);
}

int GetInt (char* prompt) {
   while (true) {
      printf ("%s: ", prompt);
      char input[15], * endptr = NULL;
      fgets (input, sizeof (input), stdin);
      if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
      errno = 0;
      int num = strtol (input, &endptr, 10);
      if (*endptr != '\n' || errno == ERANGE)
         printf ("Please enter a valid natural number\n");
      else return num;
   }

}

int main () {
   int input, output;
   do {
      system ("cls");
      input = GetInt ("Enter a natural number(Enter any non-natural number to exit)");
      output = DigitalRoot (input);
      if (output != 0) printf ("Digital root: %d\n\n", output);
   } while (GetInt ("Do you wish to continue? Enter 1") == 1);
}