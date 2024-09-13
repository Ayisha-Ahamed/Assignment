// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// test.c
// Program to test palindrome.c
// ------------------------------------------------------------------------------------------------

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdbool.h>
#include "palindrome.h"
#include <string.h>
#include <ctype.h>

void GetStr () {
   int c;
   char str[101];
   while ((c = getchar ()) != '\n' && c != EOF);                  // Clear input buffer
   printf ("Enter input : ");
   fgets (str, 100, stdin);
   str[strcspn (str, "\n")] = '\0';
   char* result = Reverse (str);
   if (isdigit (result[0]) || result[0] == '-' && isdigit (result[1])) {
      printf ("Output : %s\n", result);
      if (strcmp (str, result) == 0) printf (PAL_TRUE"\n");
      else printf (PAL_FALSE"\n");
      return;
   }
   printf ("%s\n", result);
   return;
}

int PrintTable () {
   int c;
   while ((c = getchar ()) != '\n' && c != EOF);                                                           // Clear input buffer
   bool check, isPal;
   char* intArr[10] = { "121", "-221", "-1234321", "32123", "123456", "2147483647", "-214748364890", "16322361", "421124", "4004" };      // Integer inputs
   char* intRes[10] = { "121", "-122", "-1234321", "32123", "654321", "7463847412", INT_OVERFLOW, "16322361", "421124", "4004" };         // Expected Outputs
   char* strArr[10] = { "Malayalam", "Apple", "I did,did I?",                                                                             // String inputs
                        "Madam","Do geese see God?", "Eva, can I see bees in a cave?",
                        "Borrow or rob?",
                        "Mom", "Alphabet", "Banner" };
   bool strRes[10] = { 1, 0, 1, 1, 1, 1, 1, 1, 0, 0 };                                                     // Expected outputs for string inputs in boolean - 1 representing that the string in i'th position is a palindrome
   // Integer inputs comparision table
   printf ("----------------------------------------"MAGENTA"Integer Palindrome"RESET"---------------------------------------------\n");
   printf ("   "YELLOW "Input"RESET"            "YELLOW"Expected Output"RESET"       "YELLOW"Actual Output"RESET"           "YELLOW"Result"RESET"                 "YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 10; i++) {
      char* revNum = Reverse (intArr[i]);
      check = 0, isPal = 0;
      if (strcmp (revNum, intRes[i]) == 0)check = 1;
      if (strcmp (revNum, intArr[i]) == 0)isPal = 1;
      if (check == 1 && isPal == 1)printf ("%16s |  %16s |  %16s |  %24s | "CYAN"\t  PASS\n"RESET, intArr[i], intRes[i], revNum, PAL_TRUE);
      else if (check == 1 && isPal == 0)printf ("%16s |  %16s |  %16s |  %24s | "CYAN"\t  PASS\n"RESET, intArr[i], intRes[i], revNum, PAL_FALSE);
      else printf ("%16s |  %16s |  %16s |  %24s | "MAGENTA"\t  FAIL\n"RESET, intArr[i], intRes[i], revNum, PAL_FALSE);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");

   // String inputs comparision table
   printf ("----------------------------------------"MAGENTA"String Palindrome"RESET"----------------------------------------------\n");
   printf ("   "YELLOW "\t\tInput"RESET"          "YELLOW"\t\tExpected Output"RESET"       "YELLOW"\t\tActual Output"RESET"          "YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 10; i++) {
      check = 0;
      isPal = strRes[i];                                                                                  //Expected boolean output
      char* result = Reverse (strArr[i]);
      if (isPal ^ strcmp (result, PAL_TRUE)) check = 1;
      if (check == 1 && isPal == true) printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, strArr[i], PAL_TRUE, PAL_TRUE);
      else if (check == 1 && isPal == false) printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, strArr[i], PAL_FALSE, PAL_FALSE);
      else printf ("%34s |  %24s |  %24s |  "MAGENTA"\tFAIL\n"RESET, strArr[i], isPal ? PAL_TRUE : PAL_FALSE, !(isPal) ? PAL_TRUE : PAL_FALSE);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
   return 0;
}

int main () {
   bool start = true; char choice;
   while (start) {
      printf ("\nSelect Option : \n1. Enter '1' to give input\n2. Enter '2' to print test cases\nEnter option (Enter '3' to stop): ");
      choice = getchar ();
      switch (choice) {
         case '1': GetStr (); break;
         case '2': PrintTable (); break;
         case '3': start = false; break;
         default:
            printf ("Please enter a valid option\n");
            break;
      }
   }
}