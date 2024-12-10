// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch A5.
// Program to test heap sort and binary search.
// ------------------------------------------------------------------------------------------------
#pragma warning(disable:4996)
#include "Header.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Number of tests and maximum size of array to be generated in TestSort().
#define NUM_OF_TESTS 10
#define MAX_ARR_SIZE 8

typedef struct {
   int Array[MAX_ARR_SIZE];
   int Size;
}Test;

// Checks if the array is sorted in ascending order.
static bool IsSorted (int arr[], int length) {
   for (int i = 1; i < length; i++) if (arr[i - 1] > arr[i]) return false;
   return true;
}

static void PrintArray (int arr[], int size) {
   for (int i = 0; i < size; i++) printf ("%6d", arr[i]);
   for (int i = MAX_ARR_SIZE - size; i > 0; i--) printf ("%6s", "");
}

static void PrintLine () {
   printf ("----------------------------------------------------------------------"
           "--------------------------------------\n");
}

static void TestSearch () {
   Test arr[8] = { { { 1,2,3,4,5,6,7,8 },8 }, { { -5,-4,-3,-2,-1,0,1,2 },8 } ,
                  { { 435,560,780,799,801,802,890,999 },8 } ,{ { -234,-123,-90,-9,-5,-3,-1 },7 } ,
                  { { 1,1,1,1,1 },5 }, { { 2 },1 } };
   // Keys and expected index positions
   int search[][2] = { { 3 , 2 } , { 0 , 5 }, { 801 , 4 } , { -9 , 3 },
                       { 1 , 2 } , { 5 , -1 } };
   int length = sizeof (search) / sizeof (search[0]);
   printf (YELLOW"\n                                           Test BinarySearch()\n"RESET);
   PrintLine ();
   printf ("              Sorted Input                         |   Key   |");
   printf ("  Found at  |     Status     |     Search    \n");
   PrintLine ();
   for (int i = 0; i < length; i++) {
      PrintArray (arr[i].Array, arr[i].Size);
      int index = BinarySearch (arr[i].Array, arr[i].Size, search[i][0]);
      printf ("   |   %3d   |    %4d    ", search[i][0], index);
      printf ("|    %10s   ", index == -1 ? BLUE"Not found"RESET : CYAN"  Found  "RESET);
      printf ("|      %6s    \n", search[i][1] == index ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
      PrintLine ();
   }
}

static void TestSort () {
   printf (YELLOW"\n                                           Test HeapSort()\n"RESET);
   PrintLine ();
   printf ("                      Input                      |                       Output            ");
   printf ("        |  Sort  \n");
   for (int i = 0; i < NUM_OF_TESTS; i++) {
      int arrSize = rand () % MAX_ARR_SIZE + 1;
      int* arr = malloc (arrSize * sizeof (int));
      if (arr == NULL) return;
      // The upper limit for array elements is set to 1,00,000.
      for (int j = 0; j < arrSize; j++) arr[j] = rand () % 100000 + 1;
      PrintLine ();
      PrintArray (arr, arrSize);
      HeapSort (arr, arrSize);
      printf (" | ");
      PrintArray (arr, arrSize);
      printf ("|  %6s\n",
              IsSorted (arr, arrSize) ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
      free (arr);
   }
   PrintLine ();
}

// Gets user input and returns true if 'y' is pressed.
static bool Choice () {
   char choice[5];
   char newLine[2] = { '\n','\0' };
   do {
      printf (YELLOW"Enter (y/n): "RESET);
      fgets (choice, sizeof (choice), stdin);
      if (strpbrk (choice, newLine) == NULL) while (getchar () != '\n');
   } while (strcmp (strlwr (choice), "y\n") && strcmp (strlwr (choice), "n\n"));
   return !strcmp (choice, "y\n");
}

// Returns valid integer from user input.
static int GetInt (char* input) {
   while (true) {
      printf ("%s : ", input);
      // NewLine character as a string to compare with strpbrk() function to check for '\n'
      char newLine[2] = { '\n','\0' };
      char strInput[15], * endptr = NULL;
      fgets (strInput, 15, stdin);
      // If the string length exceeds 14, clear input buffer
      if (strpbrk (strInput, newLine) == NULL) while (getchar () != '\n');
      errno = 0;  // Reset errno.
      // Converts input string to long long int
      int num = strtol (strInput, &endptr, 10);
      if (*endptr != '\n' || errno == ERANGE || strInput[0] == '\n') {
         printf (MAGENTA"Invalid input."
                 "Please provide an integer within INT range and press 'enter'\n"RESET);
         continue;
      }
      int input = (int)num;
      return input;
   }
}

// Implements BinarySearch().
static void Search (int array[], int length) {
   while (true) {
      int search = GetInt (CYAN"Enter an integer to search"RESET);
      int index = BinarySearch (array, length - 1, search);
      if (index == -1) printf ("The given integer doesn't exist in the array\n");
      else printf ("The given integer is found at index position %d\n", index);
      printf (YELLOW"Do you wish to search another integer? "RESET);
      if (!Choice ()) break;
   }
}

// Gets user input and implements sort and search.
static void ManualTest () {
   system ("cls");
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
      PrintArray (array, length);
      HeapSort (array, length);
      printf (YELLOW" %6s    "RESET"|", "\n Output");
      PrintArray (array, length);
      printf (YELLOW"\n Status  "RESET"  | %6s%s", "",
              IsSorted (array, length) ? CYAN"Pass\n\n"RESET : MAGENTA"Fail\n\n"RESET);
      Search (array, length);
      free (array);
   }
}

void main () {
   TestSort ();
   TestSearch ();
   printf (YELLOW"Do you wish to give input? "RESET);
   if (!Choice ()) return;
   do {
      ManualTest ();
      printf (YELLOW"Do you wish to continue sort and search? "RESET);
   } while (Choice ());
   printf (CYAN"Thank you !!!"RESET);
}