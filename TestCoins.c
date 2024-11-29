// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// TestCoins.c
// Program on branch Test 2.2
// Program that tests Coins.c
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Coins.h"

static bool isEqual (Coins a, Coins b) {
   return a.Ten == b.Ten && a.Five == b.Five && a.Two == b.Two && a.One == b.One;
}

static bool Choice () {
   int choice;
   do {
      printf ("Enter (y/n) : ");
      choice = getchar ();
      if (choice == '\n') continue;
      while (getchar () != '\n');
   } while (choice != 'y' && choice != 'n');
   return choice == 'y';
}

static void Test_Change () {
   int balance[] = { 1,10,5,2,23456,76456,99999,968 };
   Coins expected[] = { { 0,0,0,1 },{ 1,0,0,0 },{ 0,1,0,0 },{ 0,0,1,0 },
      { 2345,1,0,1 },{ 7645,1,0,1 }, { 9999,1,2,0 },{ 96,1,1,1 } };
   int length = sizeof (balance) / sizeof (balance[0]);
   printf ("--------------------------------------------------\n");
   printf ("|     Balance            |        Result         |\n");
   printf ("--------------------------------------------------\n");
   for (int i = 0; i < length; i++) {
      Coins actual = Change (balance[i]);
      printf ("|    %6d              |        %5s          |\n", balance[i], isEqual (actual, expected[i]) ? "Pass" : "Fail");
      printf ("--------------------------------------------------\n");
   }

}

static int GetInt (char* prompt) {
   while (true) {
      char input[15], * endptr = NULL;
      char newLineChar[2] = { '\n','\0' };
      printf ("%s", prompt);
      fgets (input, 15, stdin);
      long long int num = strtoll (input, &endptr, 10);
      if (strpbrk (input, newLineChar) == NULL) while (getchar () != '\n');
      // The input range is fixed such that the maximum value that can be entered is 10,00,000
      if (*endptr != '\n' || num < 1 || num > 1000000 || input[0] == '\n') {
         printf ("Please enter a valid integer (1-1000k) and press 'enter' \n");
         continue;
      }
      int longToInt = (int)num;
      if (atoll (input) != longToInt) return -1; // Check if the integer cast resulted in overflow
      return longToInt;
   }
}

static void PrintRes (Coins input) {
   printf ("Ten Rupee Coins  : %d\n", input.Ten);
   printf ("Five Rupee Coins : %d\n", input.Five);
   printf ("Two Rupee Coins  : %d\n", input.Two);
   printf ("One Rupee Coins  : %d\n", input.One);
}

int main () {
   Test_Change ();
   do {
      int cost = GetInt ("\nEnter the amount to be paid to the store : ");
      int money = GetInt ("Enter the amount paid by the customer : ");
      if (cost > money || cost < 0 || money < 0)
         printf ("The cost is not fully paid. Please try again\n");
      else {
         int balance = money - cost;
         Coins result = Change (balance);
         PrintRes (result);
      }
      printf ("Do you wish to continue ? ");
   } while (Choice ());
   printf ("Thank you\n");
}