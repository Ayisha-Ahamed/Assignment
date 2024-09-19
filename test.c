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
#include <conio.h>

void ClearScreen () {
#ifdef _WIN32
   system ("cls");
#endif
}

// Removes unwanted characters from the input string
char* Filter (char* input, int* isNum) {
   int len = (int)strlen (input), i = 0;
   *isNum = 1;
   char* str = malloc (sizeof (char) * (len + 1));
   if (str == NULL) return ERROR_MEM_ALLOC;
   for (int k = 0; k < len; k++) {
      if (i == 0 && input[k] == '-') {
         str[i++] = '-';
         continue;
      }
      if (input[k] != ' ' && input[k] != '\'' && input[k] != '?' && input[k] != ',' && input[k] != '.' && input[k] != '!') str[i++] = tolower (input[k]);
      if (isdigit (input[k]) == 0) *isNum = 0;
   }
   str[i] = '\0';
   if (i == 0) return input;
   if (*isNum == 1) {
      long long int num = atoll (str);
      if (i > 12 || num > INT_MAX || num < INT_MIN) {      // For overflow input conditions the integer is taken as a string
         *isNum = 0;
         return str;
      }
      *isNum = ReverseNum (num);
   }
   return str;                                             // If the input is a string the function will return the filtered string.
}

char* NumToString (int num, char* input) {
   char* strNum = malloc (sizeof (char) * 12);
   int len;
   if (strNum == NULL) strNum = ERROR_MEM_ALLOC;
   if (num == -1)strNum = "Overflow";
   else {
      sprintf (strNum, "%d", num);
      if (input[0] == '-') {
         len = strlen (strNum);
         strNum[len] = '-';
         strNum[len + 1] = '\0';
      }
   }
   return strNum;
}

void GetStr () {
   char str[101];
   int isNum = 0;
   printf ("Enter input : ");
   fgets (str, 100, stdin);
   str[strcspn (str, "\n")] = '\0';
   if (strcmp (str, "0") == 0 || str[0] == '\0') {
      printf ("Output =  %s\n"MAGENTA"%s\n"RESET, str[0] == NULL ? EMPTY : str, str[0] == '\0' ? "Not a Palindrome" : "Palindrome");
      return;
   }
   char* input = Filter (str, &isNum);
   char* reverse = ReverseStr (input);
   if (isNum != 0) {
      char* reverse = NumToString (isNum, str);
      printf ("Output = %s\n", NumToString (isNum, str));
      printf ("%s\n", IsPalindrome (input, reverse) ? CYAN"Palindrome"RESET : MAGENTA"Not a Palindrome"RESET);
      if (!IsPalindrome (str, input))free (input);
      free (reverse);
   } else {
      char* reverse = ReverseStr (input);
      printf ("%s\n", IsPalindrome (input, reverse) ? CYAN"Palindrome"RESET : MAGENTA"Not a Palindrome"RESET);
      if (!IsPalindrome (str, input)) free (input);
   }
}

void TestReverseNum () {
   bool check, isPal;
   int fOut = 0;
   int testIn[8]  = { 121 , 1234321 ,  32123 , 123456 , 2147483647 , 1 , 421124 , 4004 };     // Integer inputs
   int testOut[8] = { 121 , 1234321 ,  32123 , 654321 ,    -1      , 1 , 421124 , 4004 };     // Expected int Outputs
    
   printf ("----------------------------------------"MAGENTA"Test ReverseNum"RESET"-----------------------------------------------\n");
   printf ("\t\t"YELLOW "Input"RESET"\t\t"YELLOW"Expected Output"RESET"\t\t"YELLOW"Actual Output"RESET"\t\t"YELLOW"Result"RESET"\t\t"YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");

   for (int i = 0; i < 8; i++) {
      fOut = ReverseNum (testIn[i]);                                                                             // Converts the integer output to string
      check = fOut == testOut[i], isPal = testIn[i] == fOut;
      if (check == 1 && isPal == 1)printf ("%16d |  %16d |  %16d |  %24s | "CYAN"\t  PASS\n"RESET, testIn[i], testOut[i], fOut, "Palindrome");
      else if (check == 1 && isPal == 0)printf ("%16d |  %16d |  %16d |  %24s | "CYAN"\t  PASS\n"RESET, testIn[i], testOut[i], fOut, "Not a Palindrome");
      else printf ("%16d |  %16d |  %16d |  %24s | "MAGENTA"\t  FAIL\n"RESET, testIn[i], testOut[i], fOut, "Not a Palindrome");
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

void TestReverseStr () {
   bool check, isPal;
   int isNum;
   char* testIn[8] = { "Malayalam", "Was it a car or a cat I saw", "Piano", "Sit on a potato pan, Otis!",     "Mr. Owl ate my metal worm.", "Eva, can I see bees in a cave?", "#2#",  "@#$2" };
   char* testOut[8] = { "Palindrome", "Palindrome", "Not a Palindrome", "Palindrome","Palindrome","Palindrome", "Palindrome", "Not a Palindrome" };

   printf ("----------------------------------------"MAGENTA"Test ReverseStr"RESET"------------------------------------------------\n");
   printf (""YELLOW "\tInput"RESET"\t\t"YELLOW"\t\tExpected Output"RESET"\t\t"YELLOW"\tActual Output"RESET"\t\t"YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");

   for (int i = 0; i < 8; i++) {
      check = 0, isPal = false;
      char* filter  = Filter (testIn[i], &isNum);                                              // Filtered string input
      char* fOut = ReverseStr (filter);                                                        // Function output
      isPal = IsPalindrome (filter, fOut);
      if (IsPalindrome (testOut[i], "Palindrome") == isPal) check = 1;
      if (check == 1) {
         if (isPal) printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, testIn[i], "Palindrome", "Palindrome");
         else printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, testIn[i], "Not a Palindrome", "Not a Palindrome");
      } else printf ("%34s |  %24s |  %24s |  "MAGENTA"\tFAIL\n"RESET, testIn[i], testOut[i] ? "Palindrome" : "Not a Palindrome", testOut[i] ? "Not a Palindrome" : "Palindrome");
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

void main () {
   int c;
   char entry[5];
   bool choice;
   TestReverseNum ();
   TestReverseStr ();
   printf ("\nSelect Option : \n1. Enter '1' to give input\n"YELLOW"Enter option (Enter '2' to stop): "RESET);
   fgets (entry, 5, stdin);
   entry[strcspn (entry, "\n")] = '\0';
   choice = strcmp (entry, "1") == 0 ? true : false;
   while (1) {
      if (choice) {
         ClearScreen ();
         GetStr ();
         printf (YELLOW"Do you wish to continue? press(y/n) : "RESET);
         c = getch ();
         choice = false;
         if (c=='y') choice = true;
      } else break;
   }
   printf ("\nThank you!");
}