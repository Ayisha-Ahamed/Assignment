// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// conversion.c
// Program to convert decimal number into binary and hexadecimal 
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#pragma warning (disable:4996)
#define ERROR_MEM_ALLOC_FAILURE -1
#define ERROR_EXCEEDED_LENGTH -2
#define ERROR_INVALID_INPUT -3
#define UNSIGNED_MAX 4294967295

char Arr[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };    // Array of hexadecimal equivalent characters

char* StoreBin;      // Global variable that stores the binary string output

int Length;          // Global variable that stores the length of the binary string output

/// <summary>Returns the nearest byte length</summary>
int NearestByte (int digit, bool isLargestNum) {
	int bitLen = 8;
	for (int i = 1; i <= digit; i++) {
		if (bitLen >= digit) return bitLen;
		bitLen *= 2;              // Bit lengths can be 8,16 or 32   
	}
	if (isLargestNum == true && digit != 0)bitLen *= 2;
	Length = bitLen;
	return bitLen;
}

/// <summary>Returns the binary equivalent of input to string</summary>
char* BinaryString (int len, unsigned long num) {
	if (num > UNSIGNED_MAX)return NULL;
	int rLen = 0, bit = 0, sIndex = len - 1;
	char* revBinStr = malloc (sizeof (char) * (len + 1));       // Stores the binary string starting from LSB to MSB
	if (revBinStr == NULL) exit (ERROR_MEM_ALLOC_FAILURE);
	for (; rLen < len; rLen++) revBinStr[rLen] = '0';           // Fills all the elements of the array to '0'
	revBinStr[rLen] = '\0';
	for (int i = 0; (num > 0 && i < len); i++) {
		bit = num % 2;
		if (bit == 1) revBinStr[i] = '1';
		num /= 2;
	}
	char* binStr = malloc (sizeof (char) * (len + 1));          // Stores the binary string from MSB to LSB
	if (binStr == NULL || StoreBin == NULL) exit (ERROR_MEM_ALLOC_FAILURE);
	binStr[len] = '\0';
	for (int i = 0; i < len; i++) {
		binStr[i] = revBinStr[sIndex];
		sIndex--;
	}
	free (revBinStr);
	return binStr;
}

/// <summary>Converts the given input to binary</summary>
char* Binary (int input) {
	int digit;
	bool largestNum = 0;                // Flag sets if the number is the largest within the given byte length ex. 256,-255
	unsigned num = (unsigned)input, numCpy = num;
	for (digit = 0; numCpy > 0; digit++) numCpy /= 2;
	if (digit > 32) return NULL;
	if (num == (pow (digit, 2) - 1)) largestNum = 1;
	printf ("Digit = %d\n", digit);
	char* binStr = BinaryString (NearestByte (digit, largestNum), num);
	if (binStr == NULL)exit (ERROR_MEM_ALLOC_FAILURE);
	return binStr;
}

/// <summary>Converts the given input to hexadecimal</summary>
char* Hexadecimal (char* StoreBin) {
	int binLen = 0, hexLen = 0, length = 0, sum = 0;
	if (StoreBin == NULL) return NULL;
	for (int i = 0; StoreBin[i] != '\0'; i++)length++;
	char* hexStr = malloc (sizeof (char) * ((length / 4) + 1));
	if (hexStr == NULL)exit (ERROR_MEM_ALLOC_FAILURE);
	while (binLen < length && hexLen < (length / 4)) {
		sum = 0;
		for (int i = 3; i >= 0; i--, binLen++) sum += (StoreBin[binLen] - '0') * (int)pow (2, i);
		hexStr[hexLen] = Arr[sum];
		hexLen++;
	}
	hexStr[hexLen] = '\0';
	return hexStr;
}

/// <summary>Method for printing hexadecimal characters using type specifier</summary>
void Hex (long int num) {
	printf ("HEX : %lX\n", num);
}

/// <summary>Prints the output of the program</summary>
int Call (int num) {
	StoreBin = malloc (sizeof (char) * (Length + 1));
	StoreBin = Binary (num);
	if (StoreBin == NULL) {
		printf ("The input exceeds the maximum length (32 bit)\n");
		return ERROR_EXCEEDED_LENGTH;
	}
	char* hex = Hexadecimal (StoreBin);
	printf ("Input : %d \nBIN : %s\nHEX : %s\n", num, StoreBin, hex);
	free (StoreBin);
	free (hex);
	return 0;
}

int main () {
	int c, lenIn = 0;
	char* inStr = malloc (sizeof (char) * 11);
	if (inStr == NULL) return ERROR_MEM_ALLOC_FAILURE;
	printf ("Enter an integer : \n");
	while ((c = getchar ()) != '\n') {
		if ((lenIn == 0 && c == '-') || (c >= '0' && c <= '9' && lenIn <= 10)) {        // First character can be negative, others within 0-9
			inStr[lenIn] = c;
			lenIn++;
		} else if (lenIn > 10) {         // Exceeds maximum bit length (32 bit)
			printf ("The input exceeded maximum length\n");
			free (inStr);
			return ERROR_EXCEEDED_LENGTH;
		} else {
			printf ("The input is not an integer\n");             // Returns for non-integer inputs
			free (inStr);
			return ERROR_INVALID_INPUT;
		}
	}
	inStr[lenIn] = '\0';
	int num = atoi (inStr);
	free (inStr);
	if (num != 0) Call (num);
	else printf ("Input : 0 \nBIN : 00000000\nHEX : 0000\n");            // If the input is 0
	return 0;
}