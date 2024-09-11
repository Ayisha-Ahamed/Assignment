#ifndef CONVERSION_H
#define CONVERSION_H
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// conversion.h
// Program on main branch
// ------------------------------------------------------------------------------------------------

#define MAX_BIT 32   
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define ERROR_MEM_ALLOC "Memory Allocation Failure"
#define ERROR_INVALID_INPUT "Invalid Input"

/// <summary>Returns the nearest bit length.</summary>
int NearestBitLen (int digit);

/// <summary>Converts the given input to binary.</summary>
char* Binary (char* input);

/// <summary>Converts the given input to hexadecimal.</summary>
char* Hexadecimal (char* input);

#endif CONVERSION_H