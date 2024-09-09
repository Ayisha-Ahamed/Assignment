#ifndef CONVERSION_H
#define CONVERSION_H
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------------------------------------
// conversion.h
// Program on main branch
// ------------------------------------------------------------------------------------------------

#include <stdbool.h>

#define MAX_BIT 32   
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

/// <summary>Returns the nearest bit length.</summary>
int NearestBitLen (int digit);

/// <summary>Returns the binary equivalent of input to string.</summary>
char* BinaryString (bool isNegative, int len, long int num, bool isThirtyOne);

/// <summary>Converts the given input to binary.</summary>
char* Binary (long int num);

/// <summary>Converts the given input to hexadecimal.</summary>
char* Hexadecimal (char* bin);

#endif CONVERSION_H