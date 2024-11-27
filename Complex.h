#pragma once
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Complex.h
// Program on branch Test1.2
// ------------------------------------------------------------------------------------------------

typedef struct {
   float Real;
   float Img;
}ComplexNumber;

/// <summary> Adds two complex numbers </summary>
ComplexNumber Op_Add (ComplexNumber num1, ComplexNumber num2);

/// <summary> Subtracts two complex numbers </summary>
ComplexNumber Op_Sub (ComplexNumber num1, ComplexNumber num2);

/// <summary> Multiplies two complex numbers </summary>
ComplexNumber Op_Mul (ComplexNumber num1, ComplexNumber num2);

/// <summary> Returns the conjugate of a complex number </summary>
ComplexNumber Conjugate (ComplexNumber num);

/// <summary> Returns the modulus of a complex number </summary>
double Modulus (ComplexNumber num);
