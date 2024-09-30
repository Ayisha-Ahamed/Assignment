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
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <malloc.h>
#include <ctype.h>

/// <summary>Windows OS specific command to clear console screen.</summary>
static void ClearScreen () {
#ifdef _WIN32
   system ("cls");
#endif
}

/// <summary>Filters the string from non alphanumeric characters.</summary>
static char* Filter (char* str) {
   if (str == NULL) return NULL;
   int len = (int)strlen (str);
   char* filtered = malloc (sizeof (char) * (len + 1));
   if (filtered == NULL) return ERROR_MEM_ALLOC;
   int newCount = 0;
   for (int i = 0; i < len; i++) if (isalnum (str[i])) filtered[newCount++] = tolower (str[i]);
   filtered[newCount] = '\0';
   return filtered;
}

/// <summary>Prints the output after processing the input.</summary>
static void PrintResult (char* str) {
   char* input = Filter (str);
   if (str[0] == '\0' || !strcmp (str, "\\t") || !strcmp (str, "\\r") || !strcmp (str, "\\n") || input[0] == '\0') {
      printf ("Output =  %s\n%s\n", EMPTY, MAGENTA"Not a Palindrome"RESET);
      return;
   }
   if (strpbrk ("abcdefghijklmnopqrstuvwxyz", input) == NULL) {               // For integer input 
      long long int strToNum = atoll (input);
      if (strlen (str) < 12 && (strlen (input) == strlen (str) || strlen (input) + 1 == strlen (str) && str[0] == '-') && !(strToNum > INT_MAX || strToNum < INT_MIN)) {
         int num = str[0] == '-' ? -(int)strToNum : (int)strToNum, revNum = ReverseNum (num);
         if (revNum == -1 && strcmp (str, "-1") != 0) printf ("Output = Overflow\n");               // Checks if the function returns -1 due to Overflow or input = -1
         else printf ("Output = %d%s\n", abs (revNum), num < 0 ? "-" : "");
         printf ("%s\n", (revNum == num && num >= 0) ? CYAN"Palindrome"RESET : MAGENTA"Not a Palindrome"RESET);
         return;
      }
   }                                                                         // For string input
   printf ("%s%s\n", !strcmp (str, EMPTY) ? "Output : "EMPTY"\n" : "", IsPalindrome (input) ? CYAN"Palindrome"RESET : MAGENTA"Not a Palindrome"RESET);
}

/// <summary>Tests "ReverseNum" function in palindrome.h.</summary>
static void TestReverseNum () {
   long long int testIn[9] = { -1 , 1234321 , 2147447412 , 123456 , 2147483646 , -123 , 421124 , 4004 , 999999999999999 };
   int testOut[9] = { -1 , 1234321 , 2147447412 , 654321 ,    -1     , -321 , 421124 , 4004 ,-1 };
   printf ("----------------------------------------"MAGENTA"Test ReverseNum"RESET"------------------------------------------------\n");
   printf ("\t"YELLOW"Input "RESET"\t   "YELLOW"Expected Output"RESET"  \t"YELLOW"Actual Output"RESET"\t\t  "YELLOW"Result "RESET"\t\t"YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 9; i++) {
      int fOut = (int)ReverseNum ((int)testIn[i]);
      printf ("%16lld |  %16d |  %16d |  %24s |  %s\n", testIn[i], testOut[i], fOut,
              (testIn[i] == fOut && fOut >= 0) ? "Palindrome" : (fOut == -1 && testIn[i] != fOut) ? "Overflow" : "Not a Palindrome",
              fOut == testOut[i] ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

/// <summary>Tests "IsPalindrome" function in palindrome.h.</summary>
static void TestIsPalindrome () {
   char* testIn[8] = { "Malayalam" , "Was it a car or a cat I saw" , "" , "Sit on a potato pan, Otis!" ,
                       "Mr. Owl ate my metal worm.", "Eva, can I see bees in a cave?" , "Apple" , "!@#" };
   bool testOut[8] = { 1,1,0,1,1,1,0,0 };                                   // Expected outputs in boolean
   printf ("----------------------------------------"MAGENTA"Test IsPalindrome"RESET"----------------------------------------------\n");
   printf (""YELLOW "\tInput"RESET"\t\t"YELLOW"\t\tExpected Output"RESET"\t\t"YELLOW"\tActual Output"RESET"\t\t"YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 8; i++) {
      char* input = Filter (testIn[i]);
      bool isPalindrome = IsPalindrome (input);
      printf ("%34s |  %24s |  %24s | \t%s\n", testIn[i], testOut[i] ? "Palindrome" : "Not a Palindrome", isPalindrome ? "Palindrome" : "Not a Palindrome",
              isPalindrome == testOut[i] ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
      free (input);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

void main () {
   char entry[5];
   TestReverseNum ();
   TestIsPalindrome ();
   printf ("\n\nEnter '1' to give input\n"YELLOW"Enter option : "RESET);
   fgets (entry, 5, stdin);                              // To eliminate invalid inputs the input length is fixed at 5 eg : 12, 1ab,1@ etc
   entry[strcspn (entry, "\n")] = '\0';
   bool choice = strcmp (entry, "1");
   while (1) {
      if (!choice) {
         ClearScreen ();
         char* str = NULL;
         int count = 0;
         printf ("Enter input : ");
         while (1) {
            int c = getc (stdin);
            if (c == '\n')break;
            char* temp = realloc (str, sizeof (char) * (count + 1) * 2);
            if (temp == NULL) {
               free (str);
               return;
            }
            str = temp;
            str[count++] = c;
         }
         if (str != NULL) {
            str[count] = '\0';
            PrintResult (str);
            free (str);
         } else printf ("Please press 'enter' after the input\n");
         printf (YELLOW"Do you wish to continue? press '1' : "RESET);
         int c = getch ();
         choice = (c != '1');
      } else break;
   }
   printf ("\nThank you!");
}