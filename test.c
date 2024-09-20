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

char* Filter (char* input, int* storeNum) {
   int len = (int)strlen (input), i = 0, num = 1;
   char* str = malloc (sizeof (char) * (len + 1));
   if (str == NULL) return ERROR_MEM_ALLOC;
   for (int k = 0; k < len; k++) {
      if (i == 0 && input[k] == '-') {
         str[i++] = '-';
         continue;
      }
      if (input[k] != ' ' && input[k] != '\'' && input[k] != '?' && input[k] != ',' && input[k] != '.' && input[k] != '!') str[i++] = tolower (input[k]);
      if (isdigit (input[k]) == 0) num = 0;
   }
   str[i] = '\0';
   if (i == 0) return input;
   if (num == 1) {
      long long int strToNum = atoll (str);
      if (i > 12 || strToNum > INT_MAX || strToNum < INT_MIN) {      // For overflow input conditions the integer is taken as a string
         num = 0;
      } else num = (int)strToNum;
   }
   if (storeNum != NULL)*storeNum = num;                             // Stores the value of the integer if the input is an integer
   return str;
}

char* NumToString (int num, char* input) {
   char* strNum = malloc (sizeof (char) * 12);
   if (strNum == NULL) strNum = ERROR_MEM_ALLOC;
   if (num == -1 && strcmp (input, "-1") != 0)strNum = "Overflow";
   else sprintf (strNum, "%d", num);
   return strNum;
}

void PrintResult (char* str) {
   int storeNum = 0;
   if (strcmp (str, "0") == 0 || str[0] == '\0' || strcmp (str, "\\n") == 0) {
      printf ("Output =  %s\n%s\n", str[0] != '0' ? EMPTY : str, str[0] != '0' ? MAGENTA"Not a Palindrome"RESET : CYAN"Palindrome"RESET);
      return;
   }
   char* input = Filter (str, &storeNum);
   if (storeNum != 0) {
      char* reverse = NumToString (ReverseNum (storeNum), str);
      printf ("Output = %s\n", reverse);
      printf ("%s\n", IsPalindrome (input, reverse) && storeNum > 0 ? CYAN"Palindrome"RESET : MAGENTA"Not a Palindrome"RESET);
   } else {
      char* reverse = ReverseStr (input);
      printf ("%s\n", IsPalindrome (input, reverse) ? CYAN"Palindrome"RESET : MAGENTA"Not a Palindrome"RESET);
   }
}

void TestReverseNum () {
   int testIn[8] = { 121 , 1234321 ,  32123 , 123456 , 2147483647 , -111 , 421124 , 4004 };     // Integer inputs
   int testOut[8] = { 121 , 1234321 ,  32123 , 654321 ,    -1     , -111 , 421124 , 4004 };     // Expected int Output
   printf ("----------------------------------------"MAGENTA"Test ReverseNum"RESET"-----------------------------------------------\n");
   printf ("\t\t"YELLOW "Input"RESET"\t\t"YELLOW"Expected Output"RESET"\t\t"YELLOW"Actual Output"RESET"\t\t"YELLOW"Result"RESET"\t\t"YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");

   for (int i = 0; i < 8; i++) {
      int fOut = ReverseNum (testIn[i]);                // Function output
      printf ("%16d |  %16d |  %16d |  %24s |  %s\n",
              testIn[i], testOut[i], fOut,
              testIn[i] == fOut && fOut >= 0 ? "Palindrome" : "Not a Palindrome",
              fOut == testOut[i] ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

void TestReverseStr () {
   char* testIn[8] = { "Malayalam", "Was it a car or a cat I saw", "Piano",
                       "Sit on a potato pan, Otis!", "Mr. Owl ate my metal worm.",
                       "Eva, can I see bees in a cave?", "#2#",  "@#$2" };
   bool testOut[8] = { 1,1,0,1,1,1,1,0 };
   printf ("----------------------------------------"MAGENTA"Test ReverseStr"RESET"------------------------------------------------\n");
   printf (""YELLOW "\tInput"RESET"\t\t"YELLOW"\t\tExpected Output"RESET"\t\t"YELLOW"\tActual Output"RESET"\t\t"YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 8; i++) {
      char* fIn = Filter (testIn[i], NULL);                                              // Filtered string input
      char* fOut = ReverseStr (fIn);                                                     // Function output 
      printf ("%34s |  %24s |  %24s | \t%s\n",
              testIn[i], testOut[i] ? "Palindrome" : "Not a Palindrome",
              IsPalindrome (fIn, fOut) ? "Palindrome" : "Not a Palindrome",
              IsPalindrome (fIn, fOut) == testOut[i] ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

void main () {
   char entry[5];
   TestReverseNum ();
   TestReverseStr ();
   printf ("\nSelect Option : \n1. Enter '1' to give input\n"YELLOW"Enter option (Enter '2' to stop): "RESET);
   fgets (entry, 5, stdin);
   entry[strcspn (entry, "\n")] = '\0';
   bool choice = strcmp (entry, "1") == 0 ? true : false;
   while (1) {
      if (choice) {
         ClearScreen ();
         char str[101];
         printf ("Enter input : ");
         fgets (str, 100, stdin);
         str[strcspn (str, "\n")] = '\0';
         PrintResult (str);
         printf (YELLOW"Do you wish to continue? press(y/n) : "RESET);
         int c = getch ();
         choice = (c == 'y') ? true : false;
      } else break;
   }
   printf ("\nThank you!");
}