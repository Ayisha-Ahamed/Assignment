// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch Test2
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Header.h"
#include <limits.h>

static bool Choice () {
   while (1) {
      int c = getchar ();
      switch (tolower (c)) {
         case 'y': return true;
         case 'n': return false;
         case '\n': break;
         default: while (getchar () != '\n'); break;
      }
      printf ("Please enter (y/n) : ");
   }

}

static int GetInt (char* prompt) {
   while (1) {
      printf ("%s", prompt);
      char input[15], * endptr = NULL;
      char newLineChar[2] = { '\n','\0' };
      fgets (input, 15, stdin);
      long long int num = strtoll (input, &endptr, 10);
      if (strpbrk (input, newLineChar) == NULL) while (getchar () != '\n');
      if (*endptr != '\n' || num > INT_MAX || num < INT_MIN || input[0] == '\n' || num < 0) {
         printf ("Please enter a positive integer within INT range and press 'enter' \n");
         continue;
      }
      int integer = (int)num;
      if (atoll (input) != integer) return -1; // Check if the integer cast resulted in overflow
      return integer;
   }
}

void PrintRes (Coin input) {
   printf ("Ten Rupee Coins : %d\n", input.Ten);
   printf ("Five Rupee Coins : %d\n", input.Five);
   printf ("Two Rupee Coins : %d\n", input.Two);
   printf ("One Rupee Coins : %d\n", input.One);
}

int main () {
   bool choice = true;
   while (choice) {
      int cost = GetInt ("\nEnter the amount to be paid to the store : ");
      int money = GetInt ("Enter the amount paid by the customer : ");
      if (cost > money || cost < 0 || money < 0) {
         printf ("The cost is not fully paid. Please try again\n");
         continue;
      }
      Coin result = Change (cost, money);
      PrintRes (result);
      printf ("Do you wish to continue ? (y/n) ");
      choice = Choice ();
      while (getchar () != '\n');
   }
}