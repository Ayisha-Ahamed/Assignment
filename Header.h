#pragma once
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Header.h
// Program on branch main.
// ------------------------------------------------------------------------------------------------


typedef struct {
   float Real;
   float Img;
}ComplexNumber;

ComplexNumber Op_Add (ComplexNumber num1, ComplexNumber num2);

ComplexNumber Op_Sub (ComplexNumber num1, ComplexNumber num2);

ComplexNumber Op_Mul (ComplexNumber num1, ComplexNumber num2);

ComplexNumber Conjugate (ComplexNumber num);

ComplexNumber Modulus (ComplexNumber num);

