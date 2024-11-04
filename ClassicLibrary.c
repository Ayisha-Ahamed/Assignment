// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch A4.
// Program that contains the definiton of functions defined in Header.h.
// ------------------------------------------------------------------------------------------------
#pragma warning(disable:4996)
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include "Header.h"

bool IsPalindrome (char* input) {
   if (input[0] == '\0') return false;
   for (int end = (int)strlen (input) - 1, start = 0; start <= end;)
      if (input[start++] != input[end--]) return false;
   return true;
}

int ReverseNum (long long int input) {
   if (input <= INT_MIN || input > INT_MAX) return OVERFLOW;  // Since abs(INT_MIN) is invalid, return as overflow 
   long long int revNum = 0;
   int num = abs ((int)input);
   for (; num > 0; num /= 10) revNum = revNum * 10 + num % 10;
   // If the reversed number is beyond the range of int, -1 is returned
   if (revNum > INT_MAX || revNum < INT_MIN) return OVERFLOW;
   return (int)revNum;
}