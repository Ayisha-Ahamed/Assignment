// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch A4.
// Program that contains the definiton of functions defined in Header.h.
// Returns if the given input string is a palindrome
// Reverses the input integer and returns the same if the reversed integer is within INT range
// ------------------------------------------------------------------------------------------------
#pragma warning(disable:4996)
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "Header.h"

bool IsPalindrome (char* input) {
   if (input[0] == '\0') return false;
   for (int end = strlen (input) - 1, start = 0; start <= end;) if (tolower (input[start++]) != tolower (input[end--])) return false;
   return true;
}

int ReverseNum (int num) {
   if (num == INT_MIN) return OVERFLOW;                           // Since abs(INT_MIN) is invalid, return as overflow 
   long long int revNum = 0;
   for (; abs (num) > 0; num /= 10) revNum = revNum * 10 + num % 10;
   if (revNum > INT_MAX || revNum < INT_MIN) return OVERFLOW;     // If the reversed number is beyond the range of int, -1 is returned
   return (int)revNum;
}