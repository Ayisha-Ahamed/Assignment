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
   char* str;
   bool isPal;
}Type;

char* Filter (char* input, bool* isNumCpy) {
   // Variable num is set to 1 assuming the input is an integer.
   int len = (int)strlen (input), index = 0, space = 0;
   bool isNum = true;
   char* str = malloc (sizeof (char) * (len + 1));
   if (str == NULL) return ERROR_MEM_ALLOC;
   // Negative symbol in first index position of input is included in the filtered string.
   if (input[0] == '-') str[index++] = '-';
   for (int k = index; k < len; k++) {
      if (isdigit (input[k]) == 0) isNum = false;// Check if the input character is a digit.
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

char* NumToString (int num, char* input) {
   char* strNum = malloc (sizeof (char) * 12);
   if (strNum == NULL) strNum = ERROR_MEM_ALLOC;
   else if (num == -1 && strcmp (input, "-1") != 0) strNum = "Overflow";
   else sprintf (strNum, "%d", abs (num));
   return strNum;
}

void PrintResult (char* str) {
   bool* isNum = false;
   char* input = Filter (str, &isNum);                                     // Filtered input string
   if (!strcmp (str, "\\n") || !strcmp (str, "\\t") || !strcmp (str, "\\r") || !strcmp (input, EMPTY))
      printf ("Output =  %s\n", EMPTY"\n"PAL_FALSE);
   else if (isNum == true) {
      int num = atoi (input), numRev = ReverseNum (num);
      char* reverseStr = NumToString (numRev, str);  // Converts the reversed number/ output message to a string
      printf ("Output = %s%s\n", reverseStr, (num < 0) && strcmp (reverseStr, "Overflow") ? "-" : "");
      printf ("%s\n", (num >= 0) && (num == numRev) ? PAL_TRUE : PAL_FALSE);
   } else
      printf ("%s\n", IsPalindrome (input) ? PAL_TRUE : PAL_FALSE);
}

void TestReverseNum () {
   long long int test[8][12] = { { 121 , 121 }, { 1234321 , 1234321 }, { 2147447412 , 2147447412 },
                               { 123456 , 654321 }, { 2147483646 , -1 },{ -123 , -321 },
                               { 421124 , 421124 }, { 999999999999 , -1 } };
   printf ("------------------------------"MAGENTA"Test ReverseNum"RESET
           "-------------------------------------\n");
   printf ("   "YELLOW"Input"RESET"      "YELLOW"Expected Output  "RESET" "YELLOW"Actual Output "RESET
           "\t    "YELLOW"Result\t"RESET"\t"YELLOW"Status"RESET"\n");
   printf ("----------------------------------------------------------------------------------\n");
   for (int i = 0; i < 8; i++) {
      int fOut = ReverseNum (test[i][0]);
      printf ("%12lld |  %12lld |  %12d |  %18s |    %s\n",
              test[i][0], test[i][1], fOut,
              (test[i][0] == fOut && fOut >= 0) ? "Palindrome" : "Not a Palindrome",
              fOut == test[i][1] ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("----------------------------------------------------------------------------------\n\n");
}

void TestIsPalindrome () {
   Type test[] = { {"Malayalam",1} , {"Was it a car or a cat I saw",1} , {"Piano",0} ,
                   {"Sit on a potato pan, Otis!",1} , {"Mr. Owl ate my metal worm.",1} ,
                   {"Eva, can I see bees in a cave?",1}, {"#2#",1} , {"@#$2",0},{"!;!",1 },{"{;",0 } };
   int length = sizeof (test) / sizeof (test[0]);
   printf ("-----------------------------------"MAGENTA"Test ReverseStr"RESET
           "------------------------------------------\n");
   printf (""YELLOW "\tInput"RESET"\t\t"YELLOW"\t\tExpected Output"RESET"\t"
           YELLOW"\tActual Output"RESET"\t    "YELLOW"Status"RESET"\n");
   printf ("--------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < length; i++) {
      char* fIn = Filter (test[i].str, NULL);              // Filtered string input
      bool isPalindrome = IsPalindrome (fIn);
      printf ("%30s |  %20s |  %20s |    %s\n",
              test[i].str, test[i].isPal ? "Palindrome" : "Not a Palindrome",
              isPalindrome ? "Palindrome" : "Not a Palindrome",
              isPalindrome == test[i].isPal ? CYAN"Pass"RESET : MAGENTA"Fail"RESET);
   }
   printf ("--------------------------------------------------------------------------------------------\n\n");
}

void main () {
   char entry[5];
   TestReverseNum ();
   TestIsPalindrome ();
   printf ("\n\nDo you wish to continue? Enter '1' : ");
   fgets (entry, 5, stdin); // To eliminate invalid inputs the input length is fixed at 5 eg : 12, 1ab,1@ etc
   entry[strcspn (entry, "\n")] = '\0';
   bool choice = strcmp (entry, "1");
   while (1) {
      if (!choice) {
         system ("cls");
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
         choice = (getch () != '1');
      } else break;
   }
   printf ("\nThank you!");
}