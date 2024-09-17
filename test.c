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

// Removes unwanted characters from the input string
char* Filter (char* input, bool* isNum) {
   int len = (int)strlen (input), i = 0;
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
      if (i < len) return INVALID_INPUT;
      int len = strlen (str), idx = 0;
      int num = atoi (str);
      if (len > 10 || str[0] == '-' && len > 11) return ReverseStr (str);  // For oveflow conditions the integer is taken as a string
      if (num + 1 < num || num - 1 > num) return ReverseStr (str);         // Overflow check
      str = ReverseNum (num, len);
      return str;
   }
   return str;                         // If the input is a string the function will return the filtered string.
}

// Prints if the input and reversed string is a palindrome
void PrintPal (char* input, char* reverse) {
   if (Palindrome(input,reverse) && reverse != ERROR_MEM_ALLOC && reverse != INVALID_INPUT && reverse != EMPTY) printf (CYAN""PAL_TRUE""RESET"\n");
   else printf (MAGENTA""PAL_FALSE""RESET"\n");
}

// Gets string from the user
void GetStr () {
   int c;
   char str[101];
   bool isNum = 0;
   while ((c = getchar ()) != '\n' && c != EOF);                  // Clear input buffer
   printf ("Enter input : ");
   fgets (str, 100, stdin);
   str[strcspn (str, "\n")] = '\0';
   char* input = Filter (str, &isNum);
   if (input == INT_OVERFLOW || input == ERROR_MEM_ALLOC || input == INVALID_INPUT || input == EMPTY) {
      printf ("Error : %s\n", input);
   } else if (isdigit (input[1])) {
      printf ("Output = %s\n", input);
      PrintPal (str, input);
      free (input);
   } else {
      char* reverse = ReverseStr (input);
      PrintPal (input, reverse);
      free (input);
   }
}

void PrintTable () {
   bool check, isPal, isNum = 0;
   char* intArr[10] = { "121", "1234321", "-1234321", "32123", "123456", "2147483647", "-2147483648", "",    "421124", "4004" };      // Integer inputs
   char* intRes[10] = { "121", "1234321", "1234321-", "32123", "654321", "7463847412", "8463847412-", EMPTY, "421124", "4004" };      // Expected Outputs
   char* strArr[10] = { "Malayalam",  "Was it a car or a cat I saw",  "I did,did I?",                                                        // String inputs
                        "Madam",      "Do geese see God?",            "Eva, can I see bees in a cave?",
                        "Borrow or rob?",                             "#2#",
                        "@#$2",      "@2@#" };
   bool strRes[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 };         // Expected outputs for string inputs in boolean i.e: 1 representing that the string is a palindrome
   printf ("----------------------------------------"MAGENTA"Integer Palindrome"RESET"---------------------------------------------\n");
   printf ("   "YELLOW "Input"RESET"            "YELLOW"Expected Output"RESET"       "YELLOW"Actual Output"RESET"           "YELLOW"Result"RESET"                 "YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 10; i++) {
      char* revNum = Filter (intArr[i], &isNum);
      check = Palindrome (revNum, intRes[i]), isPal = Palindrome (revNum, intArr[i]);
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
      isPal = Palindrome (input, output);
      if (strRes[i] == isPal) check = 1;
      if (check == 1) {
         if (isPal) printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, strArr[i], PAL_TRUE, PAL_TRUE);
         else printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, strArr[i], PAL_FALSE, PAL_FALSE);
      } else printf ("%34s |  %24s |  %24s |  "MAGENTA"\tFAIL\n"RESET, strArr[i], strRes[i] ? PAL_TRUE : PAL_FALSE, strRes[i] ? PAL_FALSE : PAL_TRUE);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

void main () {
   char choice,c;
   PrintTable ();
   while (1) {
      printf ("\nSelect Option : \n1. Enter '1' to give input\nEnter option (Enter '2' to stop): ");
      choice = getchar ();
      switch (choice) {
         case '1': GetStr (); break;
         default:
            break;
            break;
      }
      if(choice=='1')printf ("Do you wish to continue? (y/n) : ");
      if ((choice = getchar ()) == 'y') { 
         ClearScreen (); 
         while ((c = getchar ()) != '\n' && c != EOF);
      } else break;
   }
   printf ("Thank you!");
}