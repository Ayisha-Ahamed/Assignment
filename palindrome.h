#pragma once
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// palindrome.h
// Program to define palindrome function definitions.
// ------------------------------------------------------------------------------------------------

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

#define PAL_TRUE "Palindrome"
#define PAL_FALSE "Not a palindrome"
#define INVALID_INPUT "Invalid input"
#define INVALID_INT_INPUT "Invalid integer input"
#define INT_OVERFLOW "Integer overflow"
#define ERROR_MEM_ALLOC "Memory Allocation Error"

/// <summary>Returns the reversed input integer.</summary>
char* NumPalindrome (char* input, char* string, char* revStr);

/// <summary>Returns if the input string is a palindrome.</summary>
char* Reverse (char* input);