#pragma once
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Header.h
// Program on branch A4.
// Reversal 
// Program to check if the given input is a palindrome.
// Returns the value of reversed integer if the reversed number is within integer bounds.
// ------------------------------------------------------------------------------------------------
#include <stdbool.h>

#define RED "\033[1;31m"                   // Color codes
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

#define OVERFLOW -1                        // Indicates that the reversed number exceeds integer range
#define ERROR_MEM_ALLOC "Memory Allocation Error"
#define EMPTY "Empty String"

/// <summary>Returns the reversed input integer.</summary>
int ReverseNum (int num);

/// <summary>Returns if the input string is a palindrome.</summary>
bool IsPalindrome (char* input);