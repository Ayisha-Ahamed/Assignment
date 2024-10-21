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
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
   int error;            // Stores the error code.
   int num;              // Stores the input value.
}Type;

/// <summary>Windows OS specific command to clear console screen.</summary>
static void ClearScreen () {
#ifdef _WIN32
   system ("cls");
#endif
}

/// <summary>Checks if the array is in ascending order.</summary>
bool Check (int arr[], int length) {
   for (int i = 1; i < length; i++) if (arr[i - 1] > arr[i]) return false;
   return true;
}

void PrintArray (int arr[], int size, int expLength) {
   printf ("      "YELLOW"Input\t"RESET"|");
   for (int i = 0; i < size; i++) printf ("%12d", arr[i]);
   for (int i = expLength - size; i > 0; i--)printf ("%12s", "");
   HeapSort (arr, size);
   printf ("      | %4s", Check (arr, size) ? CYAN"   Pass     "RESET"\n" : MAGENTA"   Fail     "RESET"\n");
   printf ("     "YELLOW"Output\t"RESET"|");
   for (int i = 0; i < size; i++) printf ("%12d", arr[i]);
   for (int i = expLength - size; i > 0; i--)printf ("%12s", "");
   printf ("      | %12s\n", "");
}

void TestHeapSort () {
   int arr[8][8] = { { 1,2,3,5,4,6,7,8 } , { 8,7,6,5,4,3,2,1 } ,
                     { -1,-3,-5,-9,-234,-90,-123,0 } ,
                     { 0,5,-567,67,8,2,9,124 } ,
                     { 1,1,1,1,1,1,1,1 } , { 2 } };
   int size[] = { 8,8,8,8,8,1 };
   for (int i = 0; i < 6; i++) {
      printf ("   ------------------------------------------------------------------------------------------------------------------------------------\n");
      PrintArray (arr[i], size[i], 8);
   }
   printf ("   ------------------------------------------------------------------------------------------------------------------------------------\n");
}

/// <summary>Gets user input and returns true if 'y' is pressed.</summary>
bool Choice () {
   char choice[5];
   fgets (choice, 2, stdin);
   if (strcmp ("y", choice) == 0) return true;
   else if (strcmp ("n", choice) == 0) return false;
   else {
      if (choice[0] != '\n') while (getchar () != '\n'); //-----------------------------------------------------------------------------------
      printf ("  Please enter a valid option. \n  Enter (y/n) ");
      Choice ();
   }
}

/// <summary>Gets integer from the user and checks if the input is valid.</summary>
Type GetInt () {
   char str[150], strCpy[150];
   fgets (str, sizeof (str), stdin);
   Type error = { 0, -1 };
   if (str[0] == '-')strcpy (strCpy, str + 1);
   else strcpy (strCpy, str);
   strCpy[strcspn (strCpy, "\n")] = '\0';                                     // Removes the new line character at the end of the input string
   if (strspn (strCpy, "0123456789") == 0) error.error = 1;                   // Checks if the input has any non-integer character
   long long int num = atoll (str);
   if (strlen (str) > 12 || num > INT_MAX || num < INT_MIN) error.error = 2;    // Checks if the input exceeds INT range
   else  error.num = (int)num;
   switch (error.error) {
      case 1: printf (MAGENTA"  Invalid input. Please provide a valid integer and press 'enter'\n"RESET); break;
      case 2: printf (MAGENTA"  Input is out of range\n"RESET); break;
   }
   return error;
}

/// <summary>Prints the first index position of input element.</summary>
void Search (int array[], int length) {
   printf (BLUE"\n\n  Enter an integer to search : "RESET);
   Type search = GetInt ();
   if (search.error == 0) {
      int index = BinarySearch (array, length - 1, search.num);
      if (index == -1) printf ("  The given integer doesn't exist in the array\n");
      else printf ("  The given integer is found at index position %d\n", index);
   }
   printf ("  Do you wish to search another integer? (y/n) ");
   if (Choice () == false) return;
   while (getchar () != '\n');               // Clear input buffer
   Search (array, length);
}

/// <summary>Gets user input and implements sort and search.</summary>
void ManualTest () {
   ClearScreen ();
   while (getchar () != '\n');
   printf ("  Enter the number of integers in the array : ");
   Type length = GetInt ();
   if (length.num <= 0 && length.error == 0) printf (MAGENTA"  Invalid length. A list should have atleast one element\n"RESET);
   else if (length.error == 0) {
      int* array = malloc (sizeof (int) * length.num);
      if (array == NULL) return;
      for (int index = 0; index < length.num; index++) {
         printf ("  Enter integer %d : ", index + 1);
         Type value = GetInt ();
         if (value.error != 0) {
            index--;
            continue;
         };
         array[index] = value.num;
      }
      PrintArray (array, length.num, length.num);
      Search (array, length.num);
      free (array);
      while (getchar () != '\n');
   }
   printf (YELLOW"  Do you wish to continue? (y/n) "RESET);
   if (Choice () == true) ManualTest ();
}

void main () {
   TestHeapSort ();
   printf (YELLOW"   Do you wish to give input ? (y/n) "RESET);
   if (Choice () == false) return;
   ManualTest ();
   printf (CYAN"  Thank you !!!"RESET);
}