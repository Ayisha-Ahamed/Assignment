#ifndef HEADER_H
#define HEADER_H
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Header.h
// Program on branch AB3.
// Program to generate GCD and LCM of an array of natural numbers.
// Program checks if a positive integer is a prime number.
// ------------------------------------------------------------------------------------------------
#include <stdbool.h>

#define YELLOW "\033[1;33m"        // Color codes
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

/// <summary>Sorts the array in ascending order.</summary>
void BubbleSort (int arr[], int sizeOfArr);

/// <summary>Checks if the input positive integer is a prime number.</summary>
bool IsPrime (int num);

/// <summary>Returns the GCD of a array of natural numbers.</summary>
int GCD (int arr[], int length);

/// <summary>Returns the LCM of a array of natural numbers.</summary>
int LCM (int arr[], int length);

#endif 