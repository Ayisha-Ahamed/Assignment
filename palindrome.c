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

void ClearScreen () {
#ifdef _WIN32
   system ("cls");
#endif
}

char* ReverseStr (char* input) {
   if (input == NULL)return NULL;
   int len = (int)strlen (input), rIdx = 0;
   char* revStr = malloc (sizeof (char) * (len + 1));
   if (revStr == NULL) return ERROR_MEM_ALLOC;
   for (int i = len - 1; rIdx < len && i >= 0; i--)  revStr[rIdx++] = input[i];
   revStr[len] = '\0';
   return revStr;
}

char* ReverseNum (int num, int len) {
   int idx = 0;
   char* revNum = malloc (sizeof (char) * (len + 1));
   if (revNum == NULL) return ERROR_MEM_ALLOC;
   sprintf (revNum, "%d", num);           // Converts integer to string
   return ReverseStr (revNum);
}

bool Palindrome (char* input, char* reverse) {
   if (strcmp (input, reverse) == 0) return true;
   return false;
}