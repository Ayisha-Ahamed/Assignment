#pragma once
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// palindrome.h
// Program to define palindrome function definitions.
// ------------------------------------------------------------------------------------------------
#include <stdbool.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

#define PAL_TRUE "Palindrome"
#define PAL_FALSE "Not a palindrome"
#define NEGATIVE -2                        // Input is a negative number
#define OVERFLOW -1                        // The reversed integer exceedes integer bounds
#define ERROR_MEM_ALLOC "Memory Allocation Error"
#define EMPTY "Empty String"

/// <summary>Returns the reversed input integer.</summary>
int ReverseNum (int num, int len);

/// <summary>Returns if the input string is a palindrome.</summary>
char* ReverseStr (char* input);

/// <summary>Checks if the given input is palindrome.</summary>
bool CheckPal (char* input, char* reverse);

/// <summary>Function to clear console screen.</summary>
void ClearScreen ();