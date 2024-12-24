// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch AB2.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void Print (int i, int num) {
   printf ("Term %-3d:  %-5d\n", i, num);
}

void PrintFibonacci (int num) {
   int n1 = 0;
   int n2 = 1;
   if (num > 1) Print (1, 0);
   if (num > 2) Print (2, 1);
   for (int i = 3; i <= num; i++) {
      int sum = n1 + n2;
      n1 = n2;
      n2 = sum;
      Print (i, sum);
   }
}

int GetInt (char* prompt) {
   printf ("%s : ", prompt);
   char input[5], * endptr = NULL;
   fgets (input, sizeof (input), stdin);
   if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
   errno = 0;
   int num = strtol (input, &endptr, 10);
   if (errno == ERANGE || *endptr != '\n' || num < 0 || num > 47) {
      // After the 47th term, the Fibonacci series values exceed the INT range.
      printf ("Please enter an integer value within range 1 - 47\n");
      return -1;
   }
   return num;
}

int main () {
   int input = GetInt ("Enter input(Enter 0 to exit)");
   while (input != 0) {
      PrintFibonacci (input);
      printf ("\n");
      input = GetInt ("Enter input(Enter 0 to exit)");
   };
   printf ("Thank you\n");
}