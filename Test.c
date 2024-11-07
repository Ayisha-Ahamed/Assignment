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

#define MAX_SIZE 20

typedef struct {
   int Array[MAX_SIZE];
   int Length;
}Test;

/// <summary>Checks if the array is sorted in ascending order.</summary>
bool IsSorted (int arr[], int length) {
   for (int i = 1; i < length; i++) if (arr[i - 1] > arr[i]) return false;
   return true;
}

void PrintArray (int arr[], int size, int expLength) {
   for (int i = 0; i < size; i++) printf ("%5d", arr[i]);
   for (int i = expLength - size; i > 0; i--) printf ("%5s", "");
}

void PrintLine () {
   printf ("--------------------------------------------------------------------------");
   printf ("------------------------------------------------------------------------\n");
}

void TestSortAndSearch () {
   Test arr[] = { { { 1,2,3,5,4,6,7,8 } , 8 },
                  { { 8,7,5,4,3,1 } , 6 } ,
                  { { -1,-3,-5,-9,-234,-90,-123,0 } , 8 },
                  { { 0,5,-567,67,8,2,9,124 } , 8 } ,
                  { { 1,1,1,1,1,1,1 } , 7} ,
                  { { 2 } ,1 } };
   int search[][2] = { { 3 , 2 } , { 8 , 5 },
                       { -9 , 3 } , { 9 , 5 },
                       { 1 , 0 } , { 5 , -1 } };
   int length = sizeof (arr) / sizeof (arr[0]);
   PrintLine ();
   printf ("|                  Input                  |                   Output        ");
   printf ("          |  Sort  ||   Key  | Found at |     Status      |  Search  | \n");
   for (int i = 0; i < length; i++) {
      PrintLine ();
      printf ("|");
      PrintArray (arr[i].Array, arr[i].Length, 8);
      HeapSort (arr[i].Array, arr[i].Length);
      printf (" | ");
      PrintArray (arr[i].Array, arr[i].Length, 8);
      printf ("  |  %6s  ",
              IsSorted (arr[i].Array, arr[i].Length) ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
      int index = BinarySearch (arr[i].Array, arr[i].Length, search[i][0]);
      printf ("||  %4d  |  %4d    ", search[i][0], index);
      printf ("|    %10s    ", index == -1 ? BLUE"Not found"RESET : CYAN"  Found  "RESET);
      printf ("|   %6s   |\n", search[i][1] == index ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   PrintLine ();
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
      // Converts input string to long long int
      long long int num = strtoll (strInput, &endptr, 10);
      // If the string length exceeds 14, clear input buffer
      if (strchr (strInput, '\n') == NULL) while (getchar () != '\n');
      if (*endptr != '\n' || num > INT_MAX || num < INT_MIN || strInput[0] == '\n') {
         printf (MAGENTA"Invalid input."
                 "Please provide an integer within INT range and press 'enter'\n"RESET);
         continue;
      }
      int input = (int)num;
      return input;
   }
}

/// <summary>Prints the first index position of input element.</summary>
void Search (int array[], int length) {
   while (1) {
      int search = GetInt (CYAN"\n\nEnter an integer to search"RESET);
      int index = BinarySearch (array, length - 1, search);
      if (index == -1) printf ("The given integer doesn't exist in the array\n");
      else printf ("The given integer is found at index position %d\n", index);
      printf ("Do you wish to search another integer? (y/n) ");
      if (!Choice ()) break;
      while (getchar () != '\n');
   }
}

/// <summary>Gets user input and implements sort and search.</summary>
void ManualTest () {
   system ("cls");
   while (getchar () != '\n');
   int length = GetInt (CYAN"Enter the number of integers in the array"RESET);
   if (length <= 0 || length > 100)
      printf (MAGENTA"Invalid length. Please enter a value between 1-100 \n"RESET);
   else {
      int* array = malloc (sizeof (int) * length);
      if (array == NULL) return;
      for (int index = 0; index < length; index++) {
         char prompt[50];
         sprintf (prompt, "Element %d", index + 1);     // Converts index to string
         int value = GetInt (prompt);
         array[index] = value;
      }
      printf (YELLOW" %6s    "RESET"|", "\n Input ");
      PrintArray (array, length, length);
      HeapSort (array, length);
      printf (YELLOW" %6s    "RESET"|", "\n Output");
      PrintArray (array, length, length);
      printf (YELLOW"\n Status  "RESET"  | %6s%s", "",
              IsSorted (array, length) ? CYAN"Pass\n"RESET : MAGENTA"Fail\n"RESET);
      Search (array, length);
      free (array);
      while (getchar () != '\n');
   }
}

void main () {
   TestSortAndSearch ();
   printf (YELLOW"Do you wish to give input ? (y/n) "RESET);
   if (!Choice ()) return;
   do {
      ManualTest ();
      printf (YELLOW"Do you wish to continue? (y/n) "RESET);
   } while (Choice ());
   printf (CYAN"Thank you !!!"RESET);
}