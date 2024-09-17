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
#include "palindrome.h"

char* ReverseStr (char* input) {
   if (input == NULL)return NULL;
   int len = (int)strlen (input), rIdx = 0;
   char* revStr = malloc (sizeof (char) * (len + 1));
   if (revStr == NULL) return ERROR_MEM_ALLOC;
   for (int i = len - 1; rIdx < len && i >= 0; i--)  revStr[rIdx++] = input[i]; 
   revStr[len] = '\0';
   return revStr;
}

char* ReverseNum (int num,int len) {
   int idx = 0;
   char* revNum = malloc (sizeof (char) * (len + 1));
   if (revNum == NULL) return ERROR_MEM_ALLOC;
   while (num) { 
      revNum[idx++] = (num % 10) + '0';
      num /= 10;
   }
   revNum[len] = '\0';
   return revNum;
}


