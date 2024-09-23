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
   int len = (int)strlen (input), i = 0, num = 1, space = 0;                  // Variable num is set to 1 assuming the input is an integer
   char* str = malloc (sizeof (char) * (len + 1));
   if (str == NULL) return ERROR_MEM_ALLOC;
   for (int k = 0; k < len; k++) {
      if (i == 0 && input[k] == '-' && k == 0) {
         str[i++] = '-';                                                      // Negative symbol in first index position of input is included in the filtered string
         continue;
      }
      if (input[k] != ' ' && input[k] != '\'' && input[k] != '?' && input[k] != ',' && input[k] != '.' && input[k] != '!') str[i++] = tolower (input[k]);
      if (isspace (input[k])) space++;
      if (isdigit (input[k]) == 0) num = 0;                                   // If the input character is not a digit the input is considered a string with num = 0
   }
   str[i] = '\0';
   if (space == len) return EMPTY;                                            // Returns EMPTY if the input consists exclusively of space characters
   if (i == 0) return input;                                                  // If the input string consists solely of punctuation characters, returns the input
   if (num == 1) {                                                            // Variable num = 1 if the input is an integer 
      long long int strToNum = atoll (str);
      if (i > 12 || strToNum > INT_MAX || strToNum < INT_MIN) num = 0;        // For integer overflow conditions the input is taken as a string with num = 0
      else num = (int)strToNum;
   }
   if (storeNum != NULL) *storeNum = num;                                     // Stores the value of the integer , num = 0 indicates that the input is a string
   return str;
}

char* NumToString (int num, char* input) {
   char* strNum = malloc (sizeof (char) * 12);
   if (strNum == NULL) strNum = ERROR_MEM_ALLOC;
   if (num == -1 && strcmp (input, "-1") != 0) strNum = "Overflow";           // Checks if the return value is due to overflow or a valid input i.e input = -1
   else sprintf (strNum, "%d", abs (num));
   return strNum;
}

void PrintResult (char* str) {
   int storeNum = 0;                                                          // Stores integer input, for string input storeNum remains zero
   char* input = Filter (str, &storeNum);                                     // Filtered input string
   if (str[0] == '0' || str[0] == '\0' || IsPalindrome (str, "\\n") || IsPalindrome (str, "\\t") || IsPalindrome (str, "\\r") || IsPalindrome (str, "\\r\\n") || IsPalindrome (input, EMPTY)) {
      printf ("Output =  %s\n%s\n", str[0] != '0' ? EMPTY : str, str[0] != '0' ? MAGENTA"Not a Palindrome"RESET : CYAN"Palindrome"RESET);
      return;
   }
   if (storeNum != 0) {
      char* reverse = NumToString (ReverseNum (storeNum), str);
      if (storeNum > 0 || strcmp ("Overflow", reverse) == 0) printf ("Output = %s\n", reverse);
      else { printf ("Output = %s-\n", reverse); }
      printf ("%s\n", IsPalindrome (input, reverse) && storeNum > 0 ? CYAN"Palindrome"RESET : MAGENTA"Not a Palindrome"RESET);
   } else {
      char* reverse = ReverseStr (input);
      printf ("%s\n", IsPalindrome (input, reverse) ? CYAN"Palindrome"RESET : MAGENTA"Not a Palindrome"RESET);
   }
}

void TestReverseNum () {
   int testIn[8] = { 121 , 1234321 , 2147447412 , 123456 , 2147483646 , -123 , 421124 , 4004 };     // Integer inputs
   int testOut[8] = { 121 , 1234321 , 2147447412 , 654321 ,    -1     , -321 , 421124 , 4004 };     // Expected integer Output
   printf ("----------------------------------------"MAGENTA"Test ReverseNum"RESET"------------------------------------------------\n");
   printf ("\t"YELLOW"Input "RESET"\t   "YELLOW"Expected Output"RESET"  \t"YELLOW"Actual Output"RESET"\t\t  "YELLOW"Result "RESET"\t\t"YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 8; i++) {
      int fOut = ReverseNum (testIn[i]);                                                            // Function output
      printf ("%16d |  %16d |  %16d |  %24s |  %s\n",
              testIn[i], testOut[i], fOut,
              (testIn[i] == fOut && fOut >= 0) ? "Palindrome" : "Not a Palindrome",
              fOut == testOut[i] ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

void TestReverseStr () {
   char* testIn[8] = { "Malayalam" , "Was it a car or a cat I saw" , "Piano" ,
                       "Sit on a potato pan, Otis!" , "Mr. Owl ate my metal worm." ,
                       "Eva, can I see bees in a cave?" , "#2#" , "@#$2" };
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
   printf ("\nSelect Option : \n1. Enter '1' to give input\n"YELLOW"Enter option : "RESET);
   fgets (entry, 5, stdin);                                                              // To eliminate invalid inputs the input length is fixed at 5 eg : 12, 1ab,1@ etc
   entry[strcspn (entry, "\n")] = '\0';
   bool choice = strcmp (entry, "1");
   while (1) {
      if (!choice) {
         ClearScreen ();
         char str[101];
         printf ("Enter input : ");
         fgets (str, 100, stdin);
         str[strcspn (str, "\n")] = '\0';
         PrintResult (str);
         printf (YELLOW"Do you wish to continue? press(y/n) : "RESET);
         int c = getch ();
         choice = (c != 'y');
      } else break;
   }
   printf ("\nThank you!");
}