// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch AB3.
// Program to test LCM(), GCD() and IsPrime().
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <malloc.h>
#include "Header.h"

typedef struct {
   int Arr[10];
   int Len;
}Test;

static void PrintArray (int arr[], int length) {
   for (int i = 0; i < length; i++) printf ("%-5d%5s", arr[i], "");
};

// Tests input function.
static void TestFunc (int (*func)(int[], int), int expOut[], char* prompt) {
   Test arr[] = { { {3,6,9,12},4 }, {{2,3,5,7},4}, {{10,15,5,20},4},{{9,12,27,33},4},
                 {{302,251,128,876},4},{{45,60,90,72},4} };
   int length = sizeof (arr) / sizeof (Test);
   printf ("\n                             Test %s()\n", prompt);
   printf ("------------------------------------------------------------------------------------\n");
   printf ("                 Array                    ExpOut           ActOut           Status\n");
   printf ("------------------------------------------------------------------------------------\n");
   for (int i = 0; i < length; i++) {
      PrintArray (arr[i].Arr, arr[i].Len);
      // Sorted array of integers are given as input.
      BubbleSort (arr[i].Arr, arr[i].Len);
      int output = func (arr[i].Arr, arr[i].Len);
      printf ("| %-10d%5s| %-10d%5s| %4s\n", expOut[i], "", output, "", output == expOut[i] ?
              CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("------------------------------------------------------------------------------------\n");
}

static void TestLCM () {
   int expOut[] = { 36,210,60,1188,1062440832,360 };
   TestFunc (LCM, expOut, "LCM");
}

static void TestGCD () {
   int expOut[] = { 3,1,5,3,1,3 };
   TestFunc (GCD, expOut, "GCD");
}

// Gets positive integer input within range [1 - 10,000]
static int GetInt (char prompt[]) {
   while (true) {
      printf ("%s :", prompt);
      char input[10], * endptr = NULL;
      fgets (input, sizeof (input), stdin);
      if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
      errno = 0;
      int num = strtol (input, &endptr, 10);
       // A limit is set such that the maximum value the program can take is 10,000.
      if (errno == ERANGE || *endptr != '\n' || num < 1 || num > 10000)
         printf ("Please enter a positive integer within range [1 - 10,000]\n");
      else return num;
   }
}

// Prints the results obtained by calling GCD or LCM.
static void PrintResult (int(*func)(int[], int), int arr[], int length, char* prompt) {
   BubbleSort (arr, length);
   int output = func (arr, length);
   if (output < 0) printf ("%s could not be calculated\n", prompt);
   else printf ("%s: %d\n", prompt, output);
}

// Calls functions GCD and LCM.
static void Call () {
   while (true) {
      int length = GetInt (YELLOW"Enter the number of elements in the array"RESET);
      if (length <= 50 && length > 0) {
         int* arr = malloc (sizeof (int) * length);
         if (arr == NULL) return;
         for (int i = 0; i < length; i++) {
            printf ("%-2d. ", i + 1);
            arr[i] = GetInt ("Enter element");
         }
         PrintResult (GCD, arr, length, "GCD");
         PrintResult (LCM, arr, length, "LCM");
         free (arr);
         return;
      } else printf (MAGENTA"Please enter a value within range [1-50]\n"RESET);
   }
}

void main () {
   TestLCM ();
   TestGCD ();
   int input;
   do {
      input = GetInt ("\nEnter 1 to find GCD and LCM.\nEnter 2 to check if the input integer "
                      "is a prime number.\nEnter 3 to exit.\nEnter option");
      system ("cls");
      switch (input) {
         case 1: Call (); break;
         case 2: printf ("%s\n", IsPrime (GetInt ("Enter an integer")) ?
                         CYAN"Prime number"RESET : MAGENTA"Not a prime number"RESET); break;
      }
   } while (input != 3);
   printf ("Thank you\n");
}