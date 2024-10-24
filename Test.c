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
#include <stdlib.h>
#include <limits.h>

/// <summary>Checks if the array is sorted in ascending order.</summary>
bool IsSorted (int arr[], int length) {
   for (int i = 1; i < length; i++) if (arr[i - 1] > arr[i]) return false;
   return true;
}

void PrintArray (int arr[], int size, int expLength, char* str) {
   printf (YELLOW" %s\t\t "RESET"|", str);
   for (int i = 0; i < size; i++) printf ("%8d", arr[i]);
   for (int i = expLength - size; i > 0; i--) printf ("%12s", "");
}

void TestSortAndSearch () {
   int arr[8][8] = { { 1,2,3,5,4,6,7,8 } , { 8,7,6,5,4,3,2,1 } ,
                     { -1,-3,-5,-9,-234,-90,-123,0 } ,
                     { 0,5,-567,67,8,2,9,124 } ,
                     { 1,1,1,1,1,1,1,1 } , { 2 } };
   int size[] = { 8,8,8,8,8,1 }, search[] = { 3,8,-9,9,1,5 }, searchRes[] = { 2,7,3,5,0,-1 };
   int length = sizeof (size) / sizeof (int);
   for (int i = 0; i < length; i++) {
      printf ("   \n---------------------------------------------------------------------------------------\n");
      PrintArray (arr[i], size[i], 8, "Input");
      HeapSort (arr[i], size[i]);
      PrintArray (arr[i], size[i], 8, "\n Output");
      int index = BinarySearch (arr[i], size[i], search[i]);
      printf ("\n"YELLOW" Search Input"RESET"  \t |\t %d", search[i]);
      printf ("\n"YELLOW" Expected Index "RESET" |\t %d\n"YELLOW" Actual Index "RESET" \t |\t %d", searchRes[i], index);
      printf ("\n"YELLOW" Status"RESET"\t\t |  \t%12s",
              IsSorted (arr[i], size[i]) && index == searchRes[i] ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("\n---------------------------------------------------------------------------------------\n");
}

/// <summary>Gets user input and returns true if 'y' is pressed.</summary>
bool Choice () {
   switch (getchar ()) {
      case 'y': return true;
      case 'n': return false;
      case '\n': break;
      default: while (getchar () != '\n'); break;
   }
   printf ("Please enter a valid option. \nEnter (y/n) ");
   Choice ();
}

/// <summary>Gets integer from the user.</summary>
int GetInt (char* input) {
   while (1) {
      printf ("%s : ", input);
      char strInput[15], * endptr = NULL;
      fgets (strInput, 15, stdin);
      long long int num = strtoll (strInput, &endptr, 10);               // Converts input string to long long int
      if (strchr (strInput, '\n') == NULL) while (getchar () != '\n');   // If the string length exceeds 14, clear input buffer
      if (*endptr != '\n' || num > INT_MAX || num < INT_MIN || strInput[0] == '\n') {
         printf (MAGENTA"Invalid input. Please provide an integer within INT range and press 'enter' \n"RESET);
         continue;
      }
      return (int)num;
   }
}

/// <summary>Prints the first index position of input element.</summary>
void Search (int array[], int length) {
   int search = GetInt (CYAN"\n\nEnter an integer to search"RESET);
   int index = BinarySearch (array, length - 1, search);
   if (index == -1) printf ("The given integer doesn't exist in the array\n");
   else printf ("The given integer is found at index position %d\n", index);
   printf ("Do you wish to search another integer? (y/n) ");
   if (Choice () == false) return;
   while (getchar () != '\n');
   Search (array, length);
}

/// <summary>Gets user input and implements sort and search.</summary>
void ManualTest () {
   system ("cls");
   while (getchar () != '\n');
   int length = GetInt (CYAN"Enter the number of integers in the array"RESET);
   if (length <= 0 || length > 50) printf (MAGENTA"Invalid length. Please enter a value between 1-50 \n"RESET);
   else {
      int* array = malloc (sizeof (int) * length);
      if (array == NULL) return;
      for (int index = 0; index < length; index++) {
         char prompt[50];
         sprintf (prompt, "Element %d", index + 1);     // Converts index to string
         int value = GetInt (prompt);
         array[index] = value;
      }
      PrintArray (array, length, length, "\n Input");
      HeapSort (array, length);
      PrintArray (array, length, length, "\n Output");
      printf (YELLOW"\n Status \t | %6s%s"RESET, "", IsSorted (array, length) ? CYAN"Pass\n"RESET : MAGENTA"Fail\n"RESET);
      Search (array, length);
      free (array);
      while (getchar () != '\n');
   }
}

void main () {
   TestSortAndSearch ();
   printf (YELLOW"Do you wish to give input ? (y/n) "RESET);
   if (Choice () == false) return;
   do {
      ManualTest ();
      printf (YELLOW"Do you wish to continue? (y/n) "RESET);
   } while (Choice ());
   printf (CYAN"Thank you !!!"RESET);
}