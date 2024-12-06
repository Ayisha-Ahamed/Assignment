// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch Test1.2
// Library to perform arithmetic operations on complex numbers.
// ------------------------------------------------------------------------------------------------

#include <stdbool.h>
#include "Complex.h"
#include "math.h"

ComplexNumber Op_Add (ComplexNumber num1, ComplexNumber num2) {
   ComplexNumber result = { num1.Real + num2.Real , num1.Img + num2.Img };
   return result;
}

ComplexNumber Op_Sub (ComplexNumber num1, ComplexNumber num2) {
   ComplexNumber result = { num1.Real - num2.Real , num1.Img - num2.Img };
   return result;
}

ComplexNumber Op_Mul (ComplexNumber num1, ComplexNumber num2) {
   ComplexNumber result = { (num1.Real * num2.Real) - (num1.Img * num2.Img),
    (num1.Img * num2.Real) + (num2.Img * num1.Real) };
   return result;
}

ComplexNumber Conjugate (ComplexNumber num) {
   num.Img = -num.Img;
   return num;
}

double Modulus (ComplexNumber num) {
   return sqrt (num.Real * num.Real + num.Img * num.Img);
}

bool IsEqual (ComplexNumber num1, ComplexNumber num2) {
   const float epsilon = 0.001f;
   // Check if difference between the two floating point numbers is negligibly small
   return ((num1.Real - num2.Real < epsilon) && (num1.Img - num2.Img < epsilon));
}