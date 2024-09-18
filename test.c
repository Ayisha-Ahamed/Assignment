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
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>

void ClearScreen () {
#ifdef _WIN32
   system ("cls");
#endif
}

// Removes unwanted characters from the input string
char* Filter (char* input, int* isNum) {
   int len = strlen (input), i = 0;
   *isNum = 1;
   char* str = malloc (sizeof (char) * (len + 1));
   if (str == NULL) return ERROR_MEM_ALLOC;
   for (int k = 0; k < len; k++) {
      if (i == 0 && input[k] == '-') {
         str[i++] = '-';
         continue;
      }
      if (input[k] != ' ' && input[k] != '\'' && input[k] != '?' && input[k] != ',' && input[k] != '.') str[i++] = tolower (input[k]);
      if (isdigit (input[k]) == 0) *isNum = 0;
   }
   str[i] = '\0';
   if (i == 0) return EMPTY;
   if (*isNum == 1) {
      long long int num = atoll (str);
      if (i > 12 || num > INT_MAX || num < INT_MIN) {      // For oveflow input conditions the integer is taken as a string
         *isNum = 0;
         return ReverseStr (str);
      }
      if (str[0] == '-') {
         *isNum = NEGATIVE;
         return str;
      }
      *isNum = ReverseNum (num, len);
   }
   return str;                                             // If the input is a string the function will return the filtered string.
}

void PrintPal (char* input, char* reverse) {
   if (IsPal (input, reverse) && reverse != ERROR_MEM_ALLOC && reverse != EMPTY) printf (CYAN""PAL_TRUE""RESET"\n");
   else printf (MAGENTA""PAL_FALSE""RESET"\n");
}

void PrintError (int num) {
   switch (num) {
      case -1: printf (BLUE"Overflow\n"RESET); break;
      case -2: printf (BLUE"Not a palindrome\nNegative number\n"RESET); break;
      default: printf (BLUE"Error\n"RESET); break;
   }
}

void GetStr () {
   int c;
   char str[101];
   int isNum = 0;
   while ((c = getchar ()) != '\n' && c != EOF);           // Clear input buffer
   printf ("Enter input : ");
   fgets (str, 100, stdin);
   str[strcspn (str, "\n")] = '\0';
   char* input = Filter (str, &isNum);
   if (input == ERROR_MEM_ALLOC || input == EMPTY) {
      printf ("Error : %s\n", input);
   } else if (isNum != 0) {
      if (isNum < 0) PrintError (isNum);
      else {
         printf ("Output = %d\n", isNum);
         sprintf (str, "%d", isNum);
         PrintPal (str, input);
         free (input);
      }
   } else {
      char* reverse = ReverseStr (input);
      PrintPal (input, reverse);
      free (input);
   }
}

void PrintTable () {
   bool check, isPal;
   int isNum = 0;
   char revNum[12];
   char* intArr[10] = { "121", "1234321", "-1234321", "32123", "123456", "2147483647", "-2147483648", "1",    "421124", "4004" };     // Integer inputs
   char* intRes[10] = { "121", "1234321", "-2",       "32123", "654321", "-1",         "-2",          "1",   "421124", "4004" };      // Expected int Outputs
   char* strArr[10] = { "Malayalam",  "Was it a car or a cat I saw",  "I did,did I?",                                                 // String inputs
                        "Madam",      "Do geese see God?",            "Eva, can I see bees in a cave?",
                        "Borrow or rob?",                             "#2#",
                        "@#$2",      "@2@#" };
   bool strRes[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 };         // Expected outputs for string inputs in boolean i.e: 1 representing that the string is a palindrome
   printf ("----------------------------------------"MAGENTA"Integer Palindrome"RESET"---------------------------------------------\n");
   printf ("   "YELLOW "Input"RESET"            "YELLOW"Expected Output"RESET"       "YELLOW"Actual Output"RESET"           "YELLOW"Result"RESET"                 "YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 10; i++) {
      Filter (intArr[i], &isNum);
      sprintf (revNum, "%d", isNum);                           // Converts the integer output to string
      check = IsPal (revNum, intRes[i]), isPal = IsPal (revNum, intArr[i]);
      if (check == 1 && isPal == 1)printf ("%16s |  %16s |  %16s |  %24s | "CYAN"\t  PASS\n"RESET, intArr[i], intRes[i], revNum, PAL_TRUE);
      else if (check == 1 && isPal == 0)printf ("%16s |  %16s |  %16s |  %24s | "CYAN"\t  PASS\n"RESET, intArr[i], intRes[i], revNum, PAL_FALSE);
      else printf ("%16s |  %16s |  %16s |  %24s | "MAGENTA"\t  FAIL\n"RESET, intArr[i], intRes[i], revNum, PAL_FALSE);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
   printf ("----------------------------------------"MAGENTA"String Palindrome"RESET"----------------------------------------------\n");
   printf ("   "YELLOW "\t\tInput"RESET"          "YELLOW"\t\tExpected Output"RESET"       "YELLOW"\t\tActual Output"RESET"          "YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 10; i++) {
      check = 0, isPal = false;
      char* input = Filter (strArr[i], &isNum);
      char* output = ReverseStr (input);
      isPal = IsPal (input, output);
      if (strRes[i] == isPal) check = 1;
      if (check == 1) {
         if (isPal) printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, strArr[i], PAL_TRUE, PAL_TRUE);
         else printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, strArr[i], PAL_FALSE, PAL_FALSE);
      } else printf ("%34s |  %24s |  %24s |  "MAGENTA"\tFAIL\n"RESET, strArr[i], strRes[i] ? PAL_TRUE : PAL_FALSE, strRes[i] ? PAL_FALSE : PAL_TRUE);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

void main () {
   char choice, c;
   PrintTable ();
   while (1) {
      printf ("\nSelect Option : \n1. Enter '1' to give input\n"YELLOW"Enter option (Enter '2' to stop): "RESET);
      choice = getchar ();
      switch (choice) {
         case '1': GetStr (); break;
         default:
            break;
            break;
      }
      if (choice == '1')printf (YELLOW"Do you wish to continue? (y/n) : "RESET);
      if ((choice = getchar ()) == 'y') {
         ClearScreen ();
         while ((c = getchar ()) != '\n' && c != EOF);
      } else break;
   }
   printf ("Thank you!");
}