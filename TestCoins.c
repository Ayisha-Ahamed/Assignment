// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// TestCoins.c
// Program on branch Test 2.2
// Program tests Coins.c
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "Coins.h"

#define NO_OF_TESTS 10

static bool IsEqual (Coins a, Coins b) {
   return a.Ten == b.Ten && a.Five == b.Five && a.Two == b.Two && a.One == b.One;
}

static bool Choice () {
   int choice;
   do {
      printf ("Enter (y/n) : ");
      choice = tolower (getchar ());
      while (getchar () != '\n');
   } while (choice != 'y' && choice != 'n');
   system ("cls");
   return choice == 'y';
}

static void Test_Change () {
   printf ("--------------------------------------------------\n");
   printf ("|     Balance            |        Result         |\n");
   printf ("--------------------------------------------------\n");
   for (int i = 0; i < NO_OF_TESTS; i++) {
      int expected = rand () % 100000;
      Coins res = Change (expected);
      int actual = res.Ten * 10 + res.Five * 5 + res.Two * 2 + res.One * 1;
      printf ("|    %6d              |        %5s          |\n", expected,
               expected == actual ? "Pass" : "Fail");
      printf ("--------------------------------------------------\n");
   }

}

static int GetInt (char* prompt) {
   while (true) {
      char input[15], * endptr = NULL;
      char newLineChar[2] = { '\n','\0' };
      printf ("%s", prompt);
      fgets (input, 15, stdin);
      errno = 0;
      int num = strtol (input, &endptr, 10);
      if (strpbrk (input, newLineChar) == NULL) while (getchar () != '\n');
      // The input range is fixed such that the maximum value that can be entered is 10,00,000
      if (*endptr != '\n' || num < 1 || num > 1000000 || input[0] == '\n' || errno == ERANGE) {
         printf ("Please enter a valid integer (1 - 10,00,000) and press 'enter' \n");
         continue;
      }
      return num;
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