#pragma once
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Complex.h
// Program on branch Test1.2
// ------------------------------------------------------------------------------------------------

#include <stdbool.h>

typedef struct {
   float Real;
   float Img;
}ComplexNumber;

/// <summary>Returns the sum of two complex numbers.</summary>
ComplexNumber Op_Add (ComplexNumber num1, ComplexNumber num2);

/// <summary>Returns the difference of two complex numbers.</summary>
ComplexNumber Op_Sub (ComplexNumber num1, ComplexNumber num2);

/// <summary>Returns the product of two complex numbers.</summary>
ComplexNumber Op_Mul (ComplexNumber num1, ComplexNumber num2);

/// <summary>Returns the conjugate of a complex number.</summary>
ComplexNumber Conjugate (ComplexNumber num);

/// <summary>Returns the modulus of a complex number.</summary>
double Modulus (ComplexNumber num);

/// <summary>Checks if two complex numbers are equal.</summary>
bool IsEqual (ComplexNumber num1, ComplexNumber num2);