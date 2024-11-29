// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch Test1.2
// Program displays test cases of Op_Add() Op_Mul() and Op_Sub() from Complex.c
// Program gets complex number(s) as input from user and displays the result.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include "Complex.h"

typedef struct {
   ComplexNumber num1;
   ComplexNumber num2;
   ComplexNumber out;
}Test;

static PrintNum (ComplexNumber num, char* separator) {
   printf ("  %5.3f  %+5.3f%s", num.Real, num.Img, separator);
}

static void Test_Op_Mul () {
   Test input[] = { {{50,30},{60,70},{900,5300}},
                    {{89,90},{89,-9},{8731,7209}},
                    {{50,78},{60,70},{-2460,8180}},
                    {{52,-8},{63,-7},{3220,-868}}
   };
   printf ("                           Multiplication                                          \n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].num1, " , ");
      PrintNum (input[i].num2, "   ");
      ComplexNumber res = Op_Mul (input[i].num1, input[i].num2);
      printf (" %s\n", IsEqual (res, input[i].out) ? "Pass" : "Fail");
   }
   printf ("-------------------------------------------------------------\n");
}

static void Test_Op_Add () {
   Test input[] = { {{50,30},{60,70},{110,100}},
                    {{89,90},{89,-9},{178,81}},
                    {{50,78},{60,72},{110,150}},
                    {{52,-8.5f},{63,-7.5f},{115,-16}}
   };
   printf ("                           Addition                                          \n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].num1, " , ");
      PrintNum (input[i].num2, "   ");
      ComplexNumber res = Op_Add (input[i].num1, input[i].num2);
      printf ("%s\n", IsEqual (res, input[i].out) ? "Pass" : "Fail");
   }
   printf ("--------------------------------------------------------------\n");
}

static void Test_Op_Sub () {
   Test input[] = { {{50,30},{60,70},{-10,-40}},
                    {{89,90},{89,-9},{0,99}},
                    {{50,78},{51,71.5f},{-1,6.5f}},
                    {{52,-8.5},{63,-7.5f},{-11,-1}}
   };
   printf ("                           Subtraction                                          \n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].num1, " , ");
      PrintNum (input[i].num2, "   ");
      ComplexNumber res = Op_Sub (input[i].num1, input[i].num2);
      printf ("%s\n", IsEqual (res, input[i].out) ? "Pass" : "Fail");
   }
   printf ("-------------------------------------------------------------\n");
}

int main () {
   Test_Op_Add ();
   Test_Op_Sub ();
   Test_Op_Mul ();
}