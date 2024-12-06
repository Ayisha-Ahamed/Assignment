// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch Test1.2
// Program tests Complex.c
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include "Complex.h"

typedef struct {
   ComplexNumber N1;
   ComplexNumber N2;
   ComplexNumber Out;
}Test;

static PrintNum (ComplexNumber num, char* separator) {
   printf ("%5.3f  %+5.3f i%s", num.Real, num.Img, separator);
}

static void Test_Op_Mul () {
   Test input[] = { {{50.24f,30.57f},{60.23f,70.56f},{868.936f,5386.1655f}},
                    {{89,90},{89,-90},{16021,0}},
                    {{50,78},{60,70},{-2460,8180}},
                    {{52,-81},{63,-75},{-2799,-9003}}
   };
   printf ("                  Multiplication\n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].N1, " , ");
      PrintNum (input[i].N2, "   ");
      ComplexNumber res = Op_Mul (input[i].N1, input[i].N2);
      printf ("%s\n", IsEqual (res, input[i].Out) ? "Pass" : "Fail");
   }
   printf ("-----------------------------------------------\n");
}

static void Test_Op_Add () {
   Test input[] = { {{50,30},{60,70},{110,100}},
                    {{89.35f,90},{89.65f,-90},{179,0}},
                    {{50,78},{60,72},{110,150}},
                    {{52,-84},{63,-75},{115,-159}}
   };
   printf ("                   Addition\n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].N1, " , ");
      PrintNum (input[i].N2, "   ");
      ComplexNumber res = Op_Add (input[i].N1, input[i].N2);
      printf ("%s\n", IsEqual (res, input[i].Out) ? "Pass" : "Fail");
   }
   printf ("-----------------------------------------------\n");
}

static void Test_Op_Sub () {
   Test input[] = { {{50,30},{60,70},{-10,-40}},
                    {{89,90},{89,-90},{0,180}},
                    {{50,78},{51,71.5f},{-1,6.5f}},
                    {{52,-81.5},{63,-71.5f},{-11,-10}}
   };
   printf ("                   Subtraction\n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].N1, " , ");
      PrintNum (input[i].N2, "   ");
      ComplexNumber res = Op_Sub (input[i].N1, input[i].N2);
      printf ("%s\n", IsEqual (res, input[i].Out) ? "Pass" : "Fail");
   }
   printf ("-----------------------------------------------\n");
}

static void Test_Mod () {
   Test input[] = { {{6,8},{10,0}},{{2.56f,3.65f},{4.4582f,0}},
                   {{1,5},{5.1f,0}},{{7.66f,6.33f},{9.9370f,0}} };
   printf ("                   Modulus\n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].N1, "   ");
      ComplexNumber result = { (float)Modulus (input[i].N1),0 };
      printf ("%s\n", IsEqual (result, input[i].N2) ? "Pass" : "Fail");
   }
   printf ("-----------------------------------------------\n");
}

static Test_Conjugate () {
   Test input[] = { {{6,8},{6,-8}},{{2.56f,3.65f},{2.56f,-3.65f}},
                   {{5,-8},{5,8}},{{7.66f,-6.33f},{7.66f,6.33f}} };
   printf ("                   Conjugate\n\n");
   int length = sizeof (input) / sizeof (input[0]);
   for (int i = 0; i < length; i++) {
      PrintNum (input[i].N1, "   ");
      ComplexNumber result = Conjugate (input[i].N1);
      printf ("%s\n", IsEqual (result, input[i].N2) ? "Pass" : "Fail");
   }
   printf ("-----------------------------------------------\n");
}
int main () {
   Test_Op_Add ();
   Test_Op_Sub ();
   Test_Op_Mul ();
   Test_Mod ();
   Test_Conjugate ();
}