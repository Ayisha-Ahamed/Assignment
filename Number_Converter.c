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
#include <errno.h>
#include <string.h>
#include <stdlib.h>

// Array of string for multiples of ten.
char* Tens[11] = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

// Array of string for multiples of one.
char* Ones[11] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };

// Numbers between 10 - 20.
char* After_Ten[11] = { "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen",
"Nineteen" };

// Higher multipliers.
char* Mul[4] = { "Billion", "Million", "Thousand", "\n" };

int Base[4] = { 1000000000, 1000000, 1000, 1 };

void Base_Three (int num) {
   if (num / 100) printf ("%s Hundred ", Ones[num / 100]);
   num %= 100;
   if (num >= 11 && num <= 19) {
      printf ("%s ", After_Ten[num - 11]);
      return;
   }
   if (num)  printf ("%s ", Tens[num / 10]);
   num %= 10;
   if (num) printf ("%s ", Ones[num]);
}

void Num_To_Str (int num) {
   // Maps the corresponding quotient values when the number is divided by the base.
   for (int i = 0; i < 4; i++) {
      int k = num / Base[i];
      num %= Base[i];
      if (k > 0) {
         Base_Three (k);
         printf ("%s ", Mul[i]);
      }
   }
   printf ("\n");
};

int Get_Int (char* prompt) {
   while (true) {
      printf ("%s: ", prompt);
      char str[15], * endptr = NULL;
      fgets (str, sizeof (str), stdin);
      if (str[strlen (str) - 1] != '\n') while (getchar () != '\n');
      errno = 0;
      int strToNum = strtol (str, &endptr, 10);
      if (*endptr != '\n' || errno == ERANGE) {
         printf ("Invalid integer. Please enter a valid positive integer and press enter\n");
         continue;
      }
      return strToNum;
   }
}
int main () {
   bool choice = true;
   do {
      Num_To_Str (Get_Int ("Enter any positive integer"));
   } while (choice);
}