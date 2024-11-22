// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch main
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include "Header.h"

typedef struct {
   ComplexNumber num1;
   ComplexNumber num2;
   ComplexNumber out;
}Test;

bool IsEqual (ComplexNumber num1, ComplexNumber num2) {
   return ((num1.Real == num2.Real) && (num1.Img == num2.Img));
}

PrintNum (ComplexNumber num, char* str) {
   printf ("  %5.3f + i %5.3f%s", num.Real, num.Img, str);
}

void Test_Op_Mul () {
   Test input[] = { {{50,30},{60,70},{900,5300}},
                    {{89,90},{89,-90},{16021,0}},
                    {{50,78},{6,7},{-246,818}},
                    {{52,-81},{63,-79},{-3123,-9211}}
   };
   printf ("                           Multiplication                                          \n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].num1, " , ");
      PrintNum (input[i].num2, "   ");
      ComplexNumber res = Op_Mul (input[i].num1, input[i].num2);
      PrintNum (res, "    ");
      printf ("%s\n", IsEqual (res, input[i].out) ? "Pass" : "Fail");
   }
   printf ("-------------------------------------------------------------\n");
}

void Test_Op_Add () {
   Test input[] = { {{50,30},{60,70},{110,100}},
                    {{89,90},{89,-90},{178,0}},
                    {{50,78},{6,7},{56,85}},
                    {{52,-81},{63,-79},{115,-160}}
   };
   printf ("                           Addition                                          \n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].num1, " , ");
      PrintNum (input[i].num2, "   ");
      ComplexNumber res = Op_Add (input[i].num1, input[i].num2);
      PrintNum (res, "    ");
      printf ("%s\n", IsEqual (res, input[i].out) ? "Pass" : "Fail");
   }
   printf ("--------------------------------------------------------------\n");
}

void Test_Op_Sub () {
   Test input[] = { {{50,30},{60,70},{-10,-40}},
                    {{89,90},{89,-90},{0,180}},
                    {{50,78},{6,7},{44,71}},
                    {{52,-81},{63,-79},{-11,-2}}
   };
   printf ("                           Multiplication                                          \n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].num1, " , ");
      PrintNum (input[i].num2, "   ");
      ComplexNumber res = Op_Sub (input[i].num1, input[i].num2);
      PrintNum (res, "    ");
      printf ("%s\n", IsEqual (res, input[i].out) ? "Pass" : "Fail");
   }
   printf ("-------------------------------------------------------------\n");
}
int main () {
   Test_Op_Add ();
   Test_Op_Mul ();
   Test_Op_Sub ();
}