// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch AB3.
// Program to find the GCD and LCM of an array of natural numbers.
// Program checks if a positive integer is a prime number.
// ------------------------------------------------------------------------------------------------
#include <stdbool.h>

/// <summary>Sorts the array in ascending order.</summary>
void BubbleSort (int arr[], int sizeOfArr) {
   for (int i = 0; i < sizeOfArr; i++) {
      bool isSorted = true;
      for (int j = 1; j < sizeOfArr; j++) {
         if (arr[j - 1] > arr[j]) {
            arr[j - 1] = arr[j - 1] + arr[j];
            arr[j] = arr[j - 1] - arr[j];
            arr[j - 1] = arr[j - 1] - arr[j];
            isSorted = false;
         }
      }
      if (isSorted) return;
   }
}

/// <summary>Checks if the input positive integer is a prime number.</summary>
bool IsPrime (int num) {
   if (num <= 1) return false;
   int half = num / 2;
   // Factor of a number n cannot be greater than n / 2.
   for (int i = 2; i <= num / 2; i++)
      if (num % i == 0) return false;
   return true;
}

/// <summary>Returns the GCD of a array of natural numbers.</summary>
int GCD (int arr[], int length) {
   int smallest = arr[0];
   // Assume that the smallest number of the array is its GCD.
   bool isDivisible = true;
   // Check if all the numbers are divisible by the smallest number.
   for (int index = 1; isDivisible && index < length; index++)
      if (arr[index] % arr[0] != 0) isDivisible = false;
   if (isDivisible) return arr[0];
   // Check if all the elements are divisible by factors of smallest element.
   for (int divisor = smallest / 2; divisor > 1; divisor--) {
      isDivisible = true;
      for (int k = 0; isDivisible && k < length; k++) {
         if ((arr[k] % divisor) != 0)
            isDivisible = false;
      }
      if (isDivisible) return divisor;
   }
   return  1;
}

/// <summary>Returns the LCM of a array of natural numbers.</summary>
int LCM (int arr[], int length) {
   int lcm = arr[length - 1];
   for (int i = 0; lcm > 0 && i < length - 1; i++) {
      if (lcm % arr[i] != 0) {
            int arrOfTwo[2] = { arr[i],lcm };
            int gcd = GCD (arrOfTwo, 2);
            if (!(gcd == arr[i] || gcd * arr[i] == arr[length - 1])) lcm = (lcm * arr[i]) / gcd;
      }
   }
   return lcm;
}