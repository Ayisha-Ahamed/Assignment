// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch AB2.
// Program to print Fibonacci series.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static void Print (int i, long long int num) {
   printf ("Term %-3d:  %-5lld\n", i, num);
}

static void PrintFibonacci (int num) {
   if (num < 1) return;
   long long int n1 = 0;
   long long int n2 = 1;
   Print (1, 0);
   for (int i = 2; i <= num; i++) {
      Print (i, n2);
      long long int sum = n1 + n2;
      n1 = n2;
      n2 = sum;
   }
}

static int GetInt (char* prompt) {
   printf ("%s : ", prompt);
   char input[5], * endptr = NULL;
   fgets (input, sizeof (input), stdin);
   if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
   errno = 0;
   int num = strtol (input, &endptr, 10);
   if (errno == ERANGE || *endptr != '\n' || num < 0 || num > 93) {
      // After the 93rd term, the Fibonacci series exceeds long long int range.
      printf ("Please enter an integer value within range 1 - 93\n");
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