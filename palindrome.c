// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// palindrome.c
// Program to define palindrome functions.
// ------------------------------------------------------------------------------------------------
#pragma warning(disable:4996)
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "palindrome.h"
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

char* ReverseStr (char* input) {
   if (input == NULL) return EMPTY;
   int len = (int)strlen (input), rIdx = 0;
   char* revStr = malloc (sizeof (char) * (len + 1));
   if (revStr == NULL) return ERROR_MEM_ALLOC;
   for (int i = len - 1; rIdx < len && i >= 0; i--)  revStr[rIdx++] = input[i];
   revStr[len] = '\0';
   return revStr;
}

int ReverseNum (int num) {
   char numStr[12];
   sprintf (numStr, "%d", num);                          // Converts integer to string
   char* revNumStr = ReverseStr (numStr);
   long long int revNum = atoll (revNumStr);
   if (num < 0) revNum = -revNum;
   if (revNum > INT_MAX || revNum < INT_MIN) return -1;  // If the reversed number is beyond the range of int, -1 is returned
   return (int)revNum;
}

bool IsPalindrome (char* input, char* reverse) {
   return (strcmp (input, reverse) == 0);
}