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
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

static int GetInt (char* prompt) {
   while (true) {
      printf ("%s: ", prompt);
      char input[15], * endptr = NULL;
      fgets (input, sizeof (input), stdin);
      errno = 0;
      int num = strtol (input, &endptr, 10);
      if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
      else if (*endptr != '\n' || errno == ERANGE)
         printf ("Please enter a valid integer within INT range and press enter\n");
      else return num;
   }
}
static int GetProductArray (int input[], int output[], int length,
                            long long int productOfArr, int countOfZero) {
   switch (countOfZero) {
      case 0:case 1:
         for (int i = 0; i < length; i++) {
            long long int temp;
            if (output[i] != 0) temp = productOfArr / input[i];
            else temp = productOfArr;
            // If the product exceeds INT range, return.
            if (temp > INT_MAX || temp < INT_MIN) return -1;
            output[i] = (int)temp;
         } break;
      default: for (int i = 0; i < length; i++) output[i] = 0; break;
   }
   return 0;
}


void PrintArray (int length, int arr[], char* prompt) {
   printf ("[ ");
   for (int i = 0; i < length - 1; i++)
      printf ("%d, ", arr[i]);
   printf ("%d ]\n", arr[length - 1]);
}

int main () {
   do {
      system ("cls");
      int length;
      do length = GetInt ("Enter the length of the array[1-10]");
      while (length < 1 || length > 10);
      int* input = malloc (sizeof (int) * length), countOfZeros = 0,
         * output = malloc (sizeof (long long int) * length);
      long long int productOfArr = 1;  // Product of all the elements in the array.
      if (input == NULL || output == NULL) return -1;
      for (int i = 0; i < length; i++) {
         printf ("%d. ", i + 1);
         input[i] = GetInt ("Enter element");
         if (countOfZeros < 2 && !input[i]) productOfArr *= input[i];
         else countOfZeros++;
      }
      if (!GetProductArray (input, output, length, productOfArr, countOfZeros)) {
         printf ("The array of elements are: ");
         PrintArray (length, input, "Input");
         PrintArray (length, output, "Output");
      } else printf ("Product value exceeds INT range\n");
      free (input);
      free (output);
      printf ("To continue, press y ");
   } while (tolower (_getch ()) == 'y');
}