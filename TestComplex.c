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
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Complex.h"

typedef struct {
   ComplexNumber num1;
   ComplexNumber num2;
   ComplexNumber out;
}Test;

static bool IsEqual (ComplexNumber num1, ComplexNumber num2) {
   // Check if difference between the two floating point numbers is negligibly small
   return ((num1.Real - num2.Real < 0.0001) && (num1.Img - num2.Img < 0.0001));
}

static PrintNum (ComplexNumber num, char* str) {
   printf ("  %5.3f + i %5.3f%s", num.Real, num.Img, str);
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
                    {{52,-8.5},{63,-7.5},{115,-16}}
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
                    {{50,78},{51,71.5},{-1,6.5}},
                    {{52,-8.5},{63,-7.5},{-11,-1}}
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

static float Get_Float (char* prompt) {
   // The maximum input characters is limited to 30 to prevent overflow.
   char input[30];
   while (true) {
      printf ("%s ", prompt);
      fgets (input, sizeof (input), stdin);
      char* endptr = NULL;
      float num = strtof (input, &endptr);
      if (*endptr != '\n' || input[0] == '\n') {
         char endOfLine[2] = { '\n','\0' };
         // To check of the end of line character is present within the input string
         if (strpbrk (input, endOfLine) == NULL) while (getchar () != '\n');
         printf ("Please enter a valid floating point number within 30 characters\n");
         continue;
      }
      return num;
   }
}

static void Get_Variable (ComplexNumber* num1, ComplexNumber* num2) {
   num1->Real = Get_Float ("Enter num 1 real :");
   num1->Img = Get_Float ("Enter num 1 img :");
   if (num2 != NULL) {
      num2->Real = Get_Float ("Enter num 2 real :");
      num2->Img = Get_Float ("Enter num 2 img :");
   }
}

int main () {
   Test_Op_Add ();
   Test_Op_Sub ();
   Test_Op_Mul ();
   while (true) {
      printf ("Choose the complex number operation to be performed (Enter 6 to exit): \n1. Addition"
              "\n2. Subtraction \n3. Multiplication\n4. Conjugate\n5. Modulus\nEnter option : ");
      int num = getchar ();
      if (num != '\n') while (getchar () != '\n');
      ComplexNumber var1 = { 0,0 }, var2 = { 0,0 };
      switch (num) {
         case '1': Get_Variable (&var1, &var2);
            PrintNum (Op_Add (var1, var2), "\n\n");
            break;
         case '2': Get_Variable (&var1, &var2);
            PrintNum (Op_Sub (var1, var2), "\n\n");
            break;
         case '3': Get_Variable (&var1, &var2);
            PrintNum (Op_Mul (var1, var2), "\n\n");
            break;
         case '4': Get_Variable (&var1, NULL);
            PrintNum (Conjugate (var1), "\n\n");
            break;
         case '5': Get_Variable (&var1, NULL);
            printf ("%f\n\n", Modulus (var1));
            break;
         case '6': printf ("Thank you!"); return 0;
         default:
            printf ("Please enter a valid option\n");
            continue;
      }
   }
}