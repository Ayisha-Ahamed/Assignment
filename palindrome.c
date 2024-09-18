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

char* ReverseStr (char* input) {
   if (input == NULL)return NULL;
   int len = (int)strlen (input), rIdx = 0;
   char* revStr = malloc (sizeof (char) * (len + 1));
   if (revStr == NULL) return ERROR_MEM_ALLOC;
   for (int i = len - 1; rIdx < len && i >= 0; i--)  revStr[rIdx++] = input[i];
   revStr[len] = '\0';
   return revStr;
}

int ReverseNum (int num, int len) {
   char* revNum = malloc (sizeof (char) * (len + 1));
   if (revNum == NULL) return ERROR_MEM_ALLOC;
   sprintf (revNum, "%d", num);                      // Converts integer to string
   revNum = ReverseStr (revNum);
   long long int rNum = atoll (revNum);
   if (rNum > INT_MAX || rNum < INT_MIN) return -1;  // If the reversed number is beyond the range of int, -1 is returned
   return rNum;
}

bool CheckPal (char* input, char* reverse) {
   bool result = (strcmp (input, reverse) == 0) ? true : false;
   return result;
}