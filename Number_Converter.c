// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch AB1.
// Program to display input numbers as words and roman numerals.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

// Prints the number in terms of hundreds.
static void PrintBaseThree (int num) {
   char* tens[11] = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy",
                      "Eighty", "Ninety" };
   char* ones[11] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
                      "Nine" };
   char* elevenToNineteen[11] = { "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                                  "Seventeen", "Eighteen", "Nineteen" };
   if (num / 100) printf ("%s Hundred ", ones[num / 100]);
   num %= 100;
   if (num >= 11 && num <= 19) {
      printf ("%s ", elevenToNineteen[num - 11]);
      return;
   }
   if (num / 10)  printf ("%s ", tens[num / 10]);
   num %= 10;
   if (num) printf ("%s ", ones[num]);
}

static void PrintString (int num) {
   if (num == 0) {
      printf ("Zero\n");
      return;
   }
   // Higher multipliers of base 10.
   char* multiplier[4] = { "Billion", "Million", "Thousand", "\n" };
   // The highest base value that can be converted to string is 1 billion i.e 1000,000,000.
   int base = 1000000000;
   for (int i = 0; i < 4; i++) {
      int quotient = num / base;
      num %= base;
      base /= 1000;
      if (quotient > 0) {
         PrintBaseThree (quotient);
         printf ("%s ", multiplier[i]);
      }
   }
   printf ("\n");
}

static void PrintRomanNumerals (int num) {
   char romNum[7] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
   int romBase[7] = { 1,5,10,50,100,500,1000 };
   // Roman number notation only supports characters from 1 to 3999.
   if (num > 3999 || num < 1) {
      printf ("Please enter a number within range 1 - 3999\n");
      return;
   }
   for (int i = 6; i >= 0; i--) {
      int quotient = num / romBase[i];
      int nine = romBase[i - 1] * 9;  // 9 x multiplier of base 10.
      int four = romBase[i - 1] * 4;  // 4 x multiplier of base 10.
      // Prints multiples of 10.
      if (quotient == 1 && i % 2 == 0) printf ("%c", romNum[i]);
      // Prints multiples of 4.
      else if (quotient == 4 && i < 6) {
         printf ("%c%c", romNum[i], romNum[i + 1]);
         num %= four;
      }
      // Prints multiples of 9.
      else if (i > 0 && i < 6 && num >= nine) {
         printf ("%c%c", romNum[i - 1], romNum[i + 1]);
         num %= nine;
      }
      // Prints repeated characters.
      else for (int j = quotient; j > 0; j--) printf ("%c", romNum[i]);
      num %= romBase[i];
   }
   printf ("\n");
}

static int GetInt (char* prompt) {
   while (true) {
      printf ("%s: ", prompt);
      char str[15], * endptr = NULL;
      fgets (str, sizeof (str), stdin);
      if (str[strlen (str) - 1] != '\n') while (getchar () != '\n');
      errno = 0;
      int strToNum = strtol (str, &endptr, 10);
      if (*endptr != '\n' || errno == ERANGE)
         printf ("Invalid integer. Please enter a valid positive integer and press enter\n");
      else return strToNum;
   }
}

int main () {
   int input;
   do {
      input = GetInt ("Number Converter : \nEnter 1 to convert number to string\n"
                      "Enter 2 to convert number to roman numeral\nEnter 3 to exit\nEnter your option");
      system ("cls");
      switch (input) {
         case 1: PrintString (GetInt ("Enter any positive integer")); break;
         case 2: PrintRomanNumerals (GetInt ("Enter any positive integer")); break;
      }
   } while (input != 3);
}