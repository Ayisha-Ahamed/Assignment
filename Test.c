// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch A4.
// Program implements test cases, gets user input and checks if its a palindrome
// Prints if the given input string is a palindrome or if reversed INT overflows
// Prints the reversed integer if the input is within INT range
// ------------------------------------------------------------------------------------------------

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdbool.h>
#include "Header.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct {
   char* String;
   bool IsPal;
}Type;

void TestIsPalindrome ();

void TestReverseNum ();

void PrintResult (char* str);

char* Filter (char* input, bool* isNumCpy); // Filters the input string from punctuations

char* Filter (char* input, bool* isNumCpy) {
   // Variable num is set to 1 assuming the input is an integer.
   int len = (int)strlen (input), index = 0, space = 0;
   bool isNum = true;
   char* str = malloc (sizeof (char) * (len + 1));
   if (str == NULL) return ERROR_MEM_ALLOC;
   // Negative symbol in first index position of input is included in the filtered string.
   if (input[0] == '-') str[index++] = '-';
   for (int k = index; k < len; k++) {
      if (isNum) isNum = isdigit (input[k]); // Checks if the input character is a digit
      char ch[2] = { input[k],'\0' };
      // If the character isn't a punctuation , include character in string.
      if (strpbrk (" \'?,.-\"!;:/`~(){}[]", ch) == NULL)
         str[index++] = tolower (input[k]);
      else if (isspace (input[k])) space++;
   }
   str[index] = '\0';
   // Returns EMPTY if the input consists exclusively of space characters.
   if (space == len) return EMPTY;
   // If the input string consists solely of punctuation characters, returns the input.
   if (index == 0) return input;
   if (isNum == true) {
      long long int strToNum = atoll (str);
      // For integer overflow conditions the input is taken as a string i.e isNum = false.
      if (index > 12 || strToNum > INT_MAX || strToNum < INT_MIN) isNum = false;
   }
   if (isNumCpy != NULL) *isNumCpy = isNum;
   return str;
}

void PrintResult (char* str) {
   bool isNum = false;
   char* input = Filter (str, &isNum);                                     // Filtered input string
   if (!strcmp (str, "\\n") || !strcmp (str, "\\t") || !strcmp (str, "\\r") || !strcmp (input, EMPTY))
      printf ("Output =  %s\n", EMPTY"\n"PAL_FALSE);
   else if (isNum) {
      int num = atoi (input), revNum = ReverseNum (num);
      if (num == -1 && strcmp (input, "-1") != 0) printf ("Output = %s\n", "Overflow");
      else printf ("Output = %d%s\n", revNum, num < 0 ? "-" : "");
      printf ("%s\n", num == revNum ? PAL_TRUE : PAL_FALSE);
   } else
      printf ("%s\n", IsPalindrome (input) ? PAL_TRUE : PAL_FALSE);
}

void TestReverseNum () {
   long long int test[8][12] = { { 121 , 121 }, { 1234321 , 1234321 }, { 2147447412 , 2147447412 },
                               { 123456 , 654321 }, { 2147483646 , -1 },{ -123 , 321 },
                               { 421124 , 421124 }, { 999999999999 , -1 } };
   printf ("------------------------------"MAGENTA"Test ReverseNum"RESET
           "-------------------------------------\n");
   printf (YELLOW"   Input      Expected Output   Actual Output        Result            Status\n"RESET);
   printf ("----------------------------------------------------------------------------------\n");
   for (int i = 0; i < 8; i++) {
      int fOut = ReverseNum (test[i][0]);
      printf ("%12lld |  %12lld |  %12d |  %18s |    %s\n",
              test[i][0], test[i][1], fOut,
              test[i][0] == fOut ? "Palindrome" : "Not a Palindrome",
              fOut == test[i][1] ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("----------------------------------------------------------------------------------\n\n");
}

void TestIsPalindrome () {
   Type test[] = { {"Malayalam",1} , {"Was it a car or a cat I saw",1} , {"Piano",0} ,
                   {"Sit on a potato pan, Otis!",1} , {"Mr. Owl ate my metal worm.",1} ,
                   {"Eva, can I see bees in a cave?",1}, {"#2#",1} , {"@#$2",0},{"!;!",1 },{"{;",0 },{"12@21",1 } };
   int length = sizeof (test) / sizeof (test[0]);
   printf ("-----------------------------------"MAGENTA"Test ReverseStr"RESET
           "------------------------------------------\n");
   printf (YELLOW "             Input                  Expected Output          Actual Output         Status\n"RESET);
   printf ("--------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < length; i++) {
      char* fIn = Filter (test[i].String, NULL);              // Filtered string input
      bool isPalindrome = IsPalindrome (fIn);
      printf ("%30s |  %20s |  %20s |    %s\n",
              test[i].String, test[i].IsPal ? "Palindrome" : "Not a Palindrome",
              isPalindrome ? "Palindrome" : "Not a Palindrome",
              isPalindrome == test[i].IsPal ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("--------------------------------------------------------------------------------------------\n\n");
}

void main () {
   TestReverseNum ();
   TestIsPalindrome ();
   bool choice = true;
   while (choice) {
      char* str = NULL;
      int count = 0;
      printf ("Enter input : ");
      while (1) {
         int c = getc (stdin);
         if (c == '\n')break;
         char* temp = realloc (str, sizeof (char) * (count + 2));
         if (temp == NULL) {
            printf (ERROR_MEM_ALLOC);
            if (str != NULL) free (str);
            return;
         }
         str = temp;
         str[count++] = c;
      }
      if (str == NULL) printf (MAGENTA"Please press 'enter' after the input\n"RESET);
      else if (count > 4000) printf (MAGENTA"The input exceeded maximum length.\n"RESET);
      else {
         str[count] = '\0';
         PrintResult (str);
         free (str);
      }
      printf (YELLOW"Do you wish to continue? press '1' : "RESET);
      choice = (getch () == '1');
      system ("cls");
   }
   printf (CYAN"\nThank you!"RESET);
}