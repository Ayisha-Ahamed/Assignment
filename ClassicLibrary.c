// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch Test1.
// Program that contains the definiton of functions defined in Header.h.
// ------------------------------------------------------------------------------------------------
#include "Header.h"

ComplexNumber Op_Add (ComplexNumber num1, ComplexNumber num2) {
   ComplexNumber result = { 0,0 };
   result.Real = num1.Real + num2.Real;
   result.Img = num1.Img + num2.Img;
   return result;
}

ComplexNumber Op_Sub (ComplexNumber num1, ComplexNumber num2) {
   ComplexNumber result = { 0,0 };
   result.Real = num1.Real - num2.Real;
   result.Img = num1.Img - num2.Img;
   return result;
}

ComplexNumber Op_Mul (ComplexNumber num1, ComplexNumber num2) {
   ComplexNumber result = { 0,0 };
   result.Real = (num1.Real * num2.Real) - (num1.Img * num2.Img);
   result.Img = (num1.Img * num2.Real) + (num2.Img * num1.Real);
   return result;
}

ComplexNumber Conjugate (ComplexNumber num) {
   num.Img = -num.Img;
   return num;
}

ComplexNumber Modulus (ComplexNumber num) {
   Op_Mul (num, Conjugate (num));
}