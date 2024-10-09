// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch A5
// ------------------------------------------------------------------------------------------------
#pragma warning(disable:4996)
#include "Header.h"
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

/// <summary>Windows OS specific command to clear console screen.</summary>
static void ClearScreen () {
#ifdef _WIN32
   system ("cls");
#endif
}

/// <summary>Checks if the input array is in ascending order.</summary>
bool Check (int arr[], int length) {
   for (int i = 1; i < length; i++) if (arr[i - 1] > arr[i]) return false;
   return true;
}

/// <summary>Checks if the .</summary>expected output equals the actual output.
bool CheckTable (int input[], int output[], int length) {
   for (int i = 0; i < length; i++)if (input[i] != output[i]) return false;
   return true;
};

/// <summary>Prints the elements of the array.</summary>
void PrintArray (int arr[], int length, int expLength) {
   printf (" ");
   for (int i = 0; i < length; i++) printf ("%7d", arr[i]);
   int fillSpace = expLength - length;
   while (fillSpace > 0) {
      printf ("%7s", "");
      fillSpace--;
   }
}

/// <summary>Tests HeapSort().</summary>
void TestHeapSort () {
   int arr[8][8] = { { 1,2,3,5,4,6,7,8 } ,
                     { 8,7,6,5,4,3,2,1 } ,
                     { -1,-3,-5,-9,-234,-90,-123,0 } ,
                     { 0,5,-567,67,8,2,9,124 } ,
                     { 1,1,1,1,1,1,1,1 } ,
                     { 2 } };
   int expOutput[8][8] = { { 1,2,3,4,5,6,7,8 } ,
                           { 1,2,3,4,5,6,7,8 } ,
                           { -234,-123,-90,-9,-5,-3,-1,0 } ,
                           { -567,0,2,5,8,9,67,124 } ,
                           { 1,1,1,1,1,1,1,1 } ,
                           { 2 } };
   int size[] = { 8,8,8,8,8,1 };
   for (int i = 0; i < 6; i++) {
      printf ("   --------------------------------------------------------------------------------------------\n");
      printf ("   |   "YELLOW"Input\t"RESET"|");
      PrintArray (arr[i], size[i], 8);
      HeapSort (arr[i], size[i]);
      printf ("      | %4s", CheckTable (arr[i], expOutput[i], size[i]) ? CYAN"   Pass     "RESET"|\n" : MAGENTA"   Fail     "RESET"|\n");
      printf ("   |  "YELLOW"Output\t"RESET"|");
      PrintArray (arr[i], size[i], 8);
      printf ("      | %12s|\n", "");
   }
   printf ("   --------------------------------------------------------------------------------------------\n");
}

void main () {
   TestHeapSort ();
   int ch, input, num;
   char choice[2];
   printf ("Enter '1' to give input : ");
   fgets (choice, 2, stdin);
   if (strcmp ("1", choice) != 0) {
      printf ("Exiting the program....");
      return;
   }
   while (1) {
      ClearScreen ();
      printf ("Enter the number of elements in the array : ");
      scanf_s ("%d", &input);
      int* array = malloc (sizeof (int) * input);
      if (array == NULL)return;
      for (int i = 0; i < input; i++) {
         int num;
         printf ("Enter element %d : ", i + 1);
         scanf_s ("%d", &num);
         array[i] = num;
      }
      printf ("      "YELLOW"Input\t"RESET":");
      PrintArray (array, input, input + 4);
      HeapSort (array, input);
      printf (" Status: %4s", Check (array, input) ? CYAN"   Pass     "RESET"\n" : MAGENTA"   Fail     "RESET"|\n");
      printf ("     "YELLOW"Output\t"RESET":");
      PrintArray (array, input, input + 4);
      printf ("       %12s\n", "");
      printf ("Enter an element to search : ");
      scanf_s ("%d", &num);
      int index = BinarySearch (array, 0, input, num);
      if (index == -1) printf ("The given element doesn't exist in the array\n");
      else printf ("The element is found at index position %d\n", index);
      printf ("Press '1' to continue : ");
      ch = getch ();
      if (ch != '1') break;
   }
}