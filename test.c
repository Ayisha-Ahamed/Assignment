// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------------------------------------
// test.c
// Program to test conversion.c.
// ------------------------------------------------------------------------------------------------
#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <malloc.h>
#include "conversion.h"

///<summary>Produces a comparision table of expected and actual output for test cases.</summary>
void PrintTable () {
	int c;
	while ((c = getchar ()) != '\n' && c != EOF);                                // Clear input buffer
	bool check;
	char* bin, * hex;
	char* binRes[10];                                                            // Stores binary output strings
	int arr[10] = { 0,255,INT_MAX,INT_MIN,-2147463433,-2139479,-2139479678,-312456790,1234567890,65536 };                 // Sample inputs
	char* binArr[10] = { "00000000", "11111111", "01111111111111111111111111111111",                                      // Expected Binary Output
							  "10000000000000000000000000000000", "10000000000000000100111011110111",
							  "11111111110111110101101010101001", "10000000011110100010000110000010",
							  "11101101011000000100100110101010", "01001001100101100000001011010010",
							  "00000000000000010000000000000000" };
	char* hexArr[10] = { "00", "FF", "7FFFFFFF",                                 // Expected Hexadecimal Output
							  "80000000", "80004EF7",
							  "FFDF5AA9", "807A2182",
							  "ED6049AA", "499602D2",
							  "00010000" };
	// Binary comparision table
	printf ("----------------------------------------"MAGENTA"Binary Comparision Table"RESET"---------------------------------------\n");
	printf ("   "YELLOW "Input"RESET"                 "YELLOW"Expected Output"RESET"                        "YELLOW"Actual Output"RESET"             "YELLOW"Status"RESET"\n");
	printf ("-------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < 10; i++) {
		bin = Binary (arr[i]);
		check = 0;
		binRes[i] = bin;
		if (strcmp (bin, binArr[i]) == 0)check = 1;
		if (check == 1)printf ("%12d |  %34s |  %34s  "CYAN"PASS\n"RESET, arr[i], binArr[i], binRes[i]);
		else printf ("%12d |  %34s |  %34s  "MAGENTA"FAIL\n"RESET, arr[i], binArr[i], binRes[i]);
	}
	printf ("-------------------------------------------------------------------------------------------------------\n\n");

	// Hexadecimal comparision table
	printf ("----------------------------------------"MAGENTA"Hexadecimal Comparision Table"RESET"----------------------------------\n");
	printf ("   "YELLOW "Input"RESET"                 "YELLOW"Expected Output"RESET"                        "YELLOW"Actual Output"RESET"             "YELLOW"Status"RESET"\n");
	printf ("-------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < 10; i++) {
		hex = Hexadecimal (binRes[i]);
		check = 0;
		if (strcmp (hex, hexArr[i]) == 0)check = 1;
		if (check == 1)printf ("%12d |  %34s |  %34s  "CYAN"PASS\n"RESET, arr[i], hexArr[i], hex);
		else printf ("%12d |  %34s |  %34s  "MAGENTA"FAIL\n"RESET, arr[i], hexArr[i], binRes[i]);
	}
	printf ("-------------------------------------------------------------------------------------------------------\n\n");
}

///<summary>Gets decimal input from the user and converts it to binary and hexadecimal.</summary>
void GetInput () {
	int c;
	while ((c = getchar ()) != '\n' && c != EOF);                                                  // Clear input buffer
	char inStr[100];
	printf ("Enter an integer : ");
	fgets (inStr, 100, stdin);
	int lenIn = 0;
	while (lenIn < (strlen (inStr) - 1)) {
		if (lenIn > 10) {                                                                           // Exceeds maximum bit length (32 bit)
			printf ("The input exceeded maximum length \nEnter an integer : ");
			lenIn = 0;
			fgets (inStr, 15, stdin);
		} else if ((lenIn == 0 && inStr[lenIn] == '-') || (inStr[lenIn] >= '0' && inStr[lenIn] <= '9' && lenIn <= 10)) lenIn++; // First character can be negative, others within 0-9
		else {
			printf ("The input is not an integer \nEnter an integer : ");                            // Prints when a non-integer input is given
			lenIn = 0;
			fgets (inStr, 15, stdin);
		}
	}
	inStr[lenIn] = '\0';
	long long int input = atoll (inStr);
	if (input <= INT_MAX && input >= INT_MIN) {
		int num = (int)input;
		if (num == 0) printf ("BIN : 00000000\nHEX : 0000\n");                                      // For input = 0
		else {
			char* bin = Binary (num), * hex = Hexadecimal (bin);
			if (bin == NULL) printf ("Memory allocation error\n");
			else printf ("BIN : %s\nHEX : %s\n", bin, hex);
			if (strcmp ("80000000", hex) != 0) free (bin);
			free (hex);
		}
	} else printf ("The given 10 digit number exceedes 32 bit\n");
}


int main () {
	char c = '0', scanOut; bool run = true;
	while (run) {
		printf ("\n");
		printf ("Select Option : \n1. Enter '1' to provide input\n2. Enter '2' to see test cases\n3. Enter '3' to stop\nEnter Input : ");
		scanOut = scanf ("%c", &c);
		switch (c) {
			case '1': GetInput (); break;
			case '2': PrintTable (); break;
			case '3': run = false; break;
			default:
				printf ("Please enter a valid option.\n");
				while ((c = getchar ()) != '\n' && c != EOF);
				break;
		}
	}
	printf ("Thank you!\n");
	return 0;
}