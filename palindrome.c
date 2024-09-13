// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// palindrome.c
// Program to define palindrome functions.
// ------------------------------------------------------------------------------------------------
#pragma warning(disable:4996)
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <limits.h>
#include "palindrome.h"

char* NumPalindrome (char* input, char* string, char* revStr) {
   int inLen = strlen (input), revLen = strlen (revStr), i;
   if (revLen > 11)return INT_OVERFLOW;
   long int num = atol (string);
   if (num > INT_MAX || num < INT_MIN) return INT_OVERFLOW;
   if (inLen == revLen || revLen == (inLen - 1) && input[0] == '-') return revStr;
   else return INVALID_INT_INPUT;
}

char* Reverse (char* input) {
   int len = strlen (input), idx = 0, rIdx = 0;
   char* string = malloc (sizeof (char) * (len + 1));
   bool isNum = 1, isPal = 0;
   if (string == NULL) return NULL;
   for (int i = 0; i < len; i++) {                               // Filters out the non-alphanumeric characters from the string 
      if (idx == 0 && input[i] == '-') {                         // Excludes negative symbol at the beginning from being filtered
         string[idx++] = input[i];
         continue;
      }
      if (isalnum (input[i])) string[idx++] = tolower (input[i]);
      if (isdigit (input[i]) == 0) isNum = 0;                    // Flag resets if a non-numeric character is present in the string
   }
   string[idx] = '\0';
   char* revStr = malloc (sizeof (char) * (idx + 1));
   if (revStr == NULL) return NULL;
   if (string[0] == '-' && isNum) revStr[rIdx++] = '-';
   for (int i = idx - 1; rIdx < idx && i >= 0; i--) revStr[rIdx++] = string[i];
   revStr[idx] = '\0';
   if (strcmp (string, revStr) == 0) isPal = true;
   if (isNum) return NumPalindrome (input, string, revStr);
   if (isPal) return PAL_TRUE;
   return PAL_FALSE;
}

