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
#include <string.h>
#include <limits.h>
#include "conversion.h"

#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

int main () {
	bool status;
	char* bin;
	char* hex;
	char* binRes[10];

	// Sample inputs
	int arr[10] = { 0,255,INT_MAX,INT_MIN,-2147463433,-2139479,-2139479678,-312456790,1234567890,65536 };

	// Expected binary outputs
	char* binArr[10] = {
		"00000000",
		"11111111",
		"01111111111111111111111111111111",
		"10000000000000000000000000000000",
		"10000000000000000100111011110111",
		"11111111110111110101101010101001",
		"10000000011110100010000110000010",
		"11101101011000000100100110101010",
		"01001001100101100000001011010010",
		"00000000000000010000000000000000"
	};

	// Expected hexadecimal output
	char* hexArr[10] = {
		"00",
		"FF",
		"7FFFFFFF",
		"80000000",
		"80004EF7",
		"FFDF5AA9",
		"807A2182",
		"ED6049AA",
		"499602D2",
		"00010000"
	};

	// Binary comparision table
	printf ("---------------------------------------------"MAGENTA"Binary Comparision"RESET"---------------------------------------\n");
	printf ("   "YELLOW "Input"RESET"                 "YELLOW"Expected Output"RESET"                        "YELLOW"Actual Output"RESET"             "YELLOW"Status"RESET"\n");
	printf ("-------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < 10; i++) {
		bin = Binary (arr[i]);
		status = 0;
		binRes[i] = bin;
		if (strcmp (bin, binArr[i]) == 0)status = 1;
		if (status == 1)printf ("%12d |  %34s |  %34s  "CYAN"PASS\n"RESET, arr[i], binArr[i], binRes[i]);
		else printf ("%12d |  %34s |  %34s  "MAGENTA"FAIL\n"RESET, arr[i], binArr[i], binRes[i]);
	}
	printf ("-------------------------------------------------------------------------------------------------------\n\n");

	// Hexadecimal comparision table
	printf ("---------------------------------------------"MAGENTA"Hexadecimal Comparision"RESET"-------------------------------------- - \n");
	printf ("   "YELLOW "Input"RESET"                 "YELLOW"Expected Output"RESET"                        "YELLOW"Actual Output"RESET"             "YELLOW"Status"RESET"\n");
	printf ("-------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < 10; i++) {
		hex = Hexadecimal (binRes[i]);
		status = 0;
		if (strcmp (hex, hexArr[i]) == 0)status = 1;
		if (status == 1)printf ("%12d |  %34s |  %34s  "CYAN"PASS\n"RESET, arr[i], hexArr[i], hex);
		else printf ("%12d |  %34s |  %34s  "MAGENTA"FAIL\n"RESET, arr[i], hexArr[i], binRes[i]);
	}
	printf ("-------------------------------------------------------------------------------------------------------\n\n");
	return 0;
}