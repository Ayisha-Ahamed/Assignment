// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch AB9.
// Program to print Pascal's triangle.
// ------------------------------------------------------------------------------------------------

#define INTOVERFLOW -1

#include <limits.h>

// Calculation of nCk.
int Combination (int n, int k) {
   // nCk is the number of subsets of k elements from a set of n elements i.e k<=n.
   if (k > n) return 0;
   // nCk = nCn-k.
   int minTurns = n - k < k ? n - k : k;
   long long int numerator = 1, denominator = 1;
   for (int i = 1; i <= minTurns; i++, n--) {
      numerator *= n;
      denominator *= i;
   }
   long long int comb = numerator / denominator;
   if (comb<INT_MIN || comb > INT_MAX) return INTOVERFLOW;
   else return (int) comb;
}