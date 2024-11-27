// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch Test1.2
// Program performs addition, subtraction and multiplication of two complex numbers.
// Program returns modulus and conjugate of a complex number.
// ------------------------------------------------------------------------------------------------

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
   ComplexNumber result = Op_Mul (num, Conjugate (num));
   return sqrt (result.Real + result.Img);
}