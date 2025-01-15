// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch AB6.
// Program to print multiplication tables.
// ------------------------------------------------------------------------------------------------
#include <stdio.h>

void PrintTable () {
   for (int i = 1; i < 11; i++, printf ("\n"))
      for (int j = 1; j < 11; j++)
         printf ("%2d *  %2d = %-2d\n", i, j, i * j);
}

int main () {
   PrintTable ();
   return 0;
}