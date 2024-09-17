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

char* FilterStr (char* input) {
   if (strcmp(input,"")==0) return "";
   int len = (int)strlen (input), idx = 0;
   bool isNum = 1;
   char* string = malloc (sizeof (char) * (len + 1));
   if (string == NULL) return ERROR_MEM_ALLOC;
   isNum = 1;
   for (int i = 0; i < len; i++) {
      if (idx == 0 && input[i] == '-') continue;
      if (isalnum (input[i]) != 0) string[idx++] = tolower (input[i]);
      if (isdigit (input[i]) == 0) isNum = 0;
   }
   string[idx] = '\0';
   if (isNum) {     
      if (idx < len) return INVALID_INPUT;
      int len = strlen (string), idx = 0;
      int num = atoi (string);
      if (len > 10 || string[0] == '-' && len > 11) return  INT_OVERFLOW;
      if (num + 1 < num || num - 1 > num) return INT_OVERFLOW;
      string = ReverseNum (num, len);
      return string;
   }
   return string;                         // If the input is a string the function will return the filtered string.
}

void Palindrome (char* input, char* reverse) {
   if (strcmp (input, reverse) == 0 && reverse != INT_OVERFLOW&& reverse!= ERROR_MEM_ALLOC)  printf (PAL_TRUE"\n");
   else printf (PAL_FALSE"\n");
   return;
}

void GetStr () {
   int c;
   char str[101];
   while ((c = getchar ()) != '\n' && c != EOF);                  // Clear input buffer
   printf ("Enter input : ");
   fgets (str, 100, stdin);
   str[strcspn (str, "\n")] = '\0';
   if (str[0] == '\0') {                                          // Empty input
      printf (PAL_TRUE"\n");
      return;
   }
   char* input = FilterStr(str);
   if (input == INT_OVERFLOW||input == ERROR_MEM_ALLOC||input==INVALID_INPUT||input==NULL) {
      printf ("Output = %s\n", input);
   } else if (isdigit(input[1])) {
      printf ("Output = %s\n", input);
      Palindrome (str, input);
      free (input);
   } else {
      char* reverse = ReverseStr (input);
      Palindrome (input, reverse);
      free (input);
   }
   return;
}

int PrintTable () {
   int c;
   while ((c = getchar ()) != '\n' && c != EOF);                                                           // Clear input buffer
   bool check, isPal;
   char* intArr[10] = { "121", "1234321", "-1234321", "32123", "123456", "214748364789", "", "16322361", "421124", "4004" };      // Integer inputs
   char* intRes[10] = { "121", "1234321", INVALID_INPUT, "32123", "654321", INT_OVERFLOW, "", "16322361", "421124", "4004" };     // Expected Outputs
   char* strArr[10] = { "Malayalam", "Apple", "I did,did I?",                                                                     // String inputs
                        "Madam","Do geese see God?", "Eva, can I see bees in a cave?",
                        "Borrow or rob?",
                        "Mom", "Alphabet", "Banner"};
   bool strRes[10] = { 1, 0, 1, 1, 1, 1, 1, 1, 0, 0 };                                                     // Expected outputs for string inputs in boolean - 1 representing that the string is a palindrome
   // Integer inputs comparision table
   printf ("----------------------------------------"MAGENTA"Integer Palindrome"RESET"---------------------------------------------\n");
   printf ("   "YELLOW "Input"RESET"            "YELLOW"Expected Output"RESET"       "YELLOW"Actual Output"RESET"           "YELLOW"Result"RESET"                 "YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 10; i++) {
      char* revNum = FilterStr(intArr[i]);
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
      isPal = strRes[i];                                                                                  // Expected output in boolean
      char* input = FilterStr(strArr[i]);
      char* output = ReverseStr (input);
      if (isPal == (strcmp (input, output)==0)) check = 1;
      if (check == 1) {
         if (isPal) printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, strArr[i], PAL_TRUE, PAL_TRUE);
         else printf ("%34s |  %24s |  %24s | "CYAN"\tPASS\n"RESET, strArr[i], PAL_FALSE, PAL_FALSE);
      }
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
   printf ("Thank you!");
   return 0;
}