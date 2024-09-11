// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// test.c
// Program to test conversion.c.
// ------------------------------------------------------------------------------------------------
#pragma warning (disable:4996)
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include "conversion.h"

// Method to print hexadecimal numbers using format specifier.
void Hex (int num) {
   printf ("HEX : %X", num);
}

// Produces a comparision table of expected and actual output for test cases.
int PrintTable () {
   int c;
   while ((c = getchar ()) != '\n' && c != EOF);                                // Clear input buffer
   bool check;
   char* bin, * hex;
   char* arr[12] = { "0","255","2147483647","-2147483648","-2147463433","-2139479","-2139479678","-312456790","1234567890","65536","asdf","12-90" };                 // Sample inputs
   char* binArr[12] = { "00000000", "11111111", "01111111111111111111111111111111",                                      // Expected Binary Output
                        "10000000000000000000000000000000", "10000000000000000100111011110111",
                        "11111111110111110101101010101001", "10000000011110100010000110000010",
                        "11101101011000000100100110101010", "01001001100101100000001011010010",
                        "00000000000000010000000000000000",  ERROR_INVALID_INPUT,  ERROR_INVALID_INPUT };
   char* hexArr[12] = { "00", "FF", "7FFFFFFF",                                                                          // Expected Hexadecimal Output
                        "80000000", "80004EF7",
                        "FFDF5AA9", "807A2182",
                        "ED6049AA", "499602D2",
                        "00010000",  ERROR_INVALID_INPUT,
                         ERROR_INVALID_INPUT };
   // Binary comparision table
   printf ("----------------------------------------"MAGENTA"Binary Comparision Table"RESET"---------------------------------------\n");
   printf ("   "YELLOW "Input"RESET"                 "YELLOW"Expected Output"RESET"                        "YELLOW"Actual Output"RESET"             "YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 12; i++) {
      bin = Binary (arr[i]);
      if (bin == NULL) return ERROR_MEM_ALLOC;
      check = 0;
      if (strcmp (bin, binArr[i]) == 0)check = 1;
      if (check == 1)printf ("%12s |  %34s |  %34s  "CYAN"PASS\n"RESET, arr[i], binArr[i], bin);
      else printf ("%12s |  %34s |  %34s  "MAGENTA"FAIL\n"RESET, arr[i], binArr[i], bin);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");

   // Hexadecimal comparision table
   printf ("----------------------------------------"MAGENTA"Hexadecimal Comparision Table"RESET"----------------------------------\n");
   printf ("   "YELLOW "Input"RESET"                 "YELLOW"Expected Output"RESET"                        "YELLOW"Actual Output"RESET"             "YELLOW"Status"RESET"\n");
   printf ("-------------------------------------------------------------------------------------------------------\n");
   for (int i = 0; i < 12; i++) {
      hex = Hexadecimal (arr[i]);
      check = 0;
      if (strcmp (hex, hexArr[i]) == 0)check = 1;
      if (check == 1)printf ("%12s |  %34s |  %34s  "CYAN"PASS\n"RESET, arr[i], hexArr[i], hex);
      else printf ("%12s |  %34s |  %34s  "MAGENTA"FAIL\n"RESET, arr[i], hexArr[i], hex);
   }
   printf ("-------------------------------------------------------------------------------------------------------\n\n");
   return 0;
}

// Gets decimal input from the user and converts it to binary and hexadecimal.
int GetInput () {
   int c;
   while ((c = getchar ()) != '\n' && c != EOF);                                                  // Clear input buffer
   char inStr[100];
   printf ("Enter an integer : ");
   fgets (inStr, 100, stdin);
   int lenIn = 0;
   inStr[strcspn (inStr, "\n")] = '\0';
   char* bin = Binary (inStr), * hex = Hexadecimal (inStr);
   if (bin == ERROR_MEM_ALLOC) return -1;
   else if (bin == ERROR_INVALID_INPUT) return -2;
   else printf ("BIN : %s\nHEX : %s\n", bin, hex);
   if (hex != "80000000") free (bin), free (hex);
   return 0;
}



int main () {
   char c = '0', scanOut; bool run = true;
   while (run) {

      printf ("\n");
      printf ("Select Option : \n1. Enter '1' to provide input\n2. Enter '2' to see test cases\n3. Enter '3' to stop\nEnter Input : ");
      scanOut = scanf ("%c", &c);
      switch (c) {
         case '1':
            scanOut = GetInput ();
            if (scanOut == 0) printf ("GetInput() :"GREEN" Passed\n"RESET);
            else {
               printf ("GetInput() :"RED" Failed\n"RESET);
               switch (scanOut) {
                  case -1: printf (RED"Error : Memory allocation failure\n"RESET); break;
                  case -2: printf (RED"Error : Invalid Input\n"RESET); break;
               }
            }
            break;
         case '2':
            scanOut = PrintTable ();
            if (scanOut == 0)  printf ("PrintTable() :"GREEN" Passed\n"RESET);
            else printf ("PrintTable() :"RED" Failed\nError : Memory allocation failure\n"RESET);
            break;
         case '3': run = false; break;
         default:
            printf ("Please enter a valid option.\n");
            while ((c = getchar ()) != '\n' && c != EOF);                                        // Clear input buffer
            break;
      }
   }
   printf ("Thank you!\n");
   return 0;
}
