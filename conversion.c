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
#pragma warning (disable:4996)
#define ERROR_MEM_ALLOC_FAILURE -1
#define ERROR_EXCEEDED_LENGTH -2
#define ERROR_INVALID_INPUT -3

char Arr[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };    // Array of hexadecimal equivalent characters

/// <summary>Returns the nearest byte length</summary>
int NearestByte (int digit, bool isLargestNum) {
	int bitLen = 8;
	for (int i = 1; i <= digit; i++) {
		if (bitLen >= digit) return bitLen;
		bitLen *= 2;                                                        // Bits are of length 8,16 or 32 
	}
	if (isLargestNum == true) bitLen *= 2;
	return bitLen;
}

/// <summary>Returns the binary equivalent of input to string</summary>
char* BinaryString (bool isNegative, int len, int num) {
	int strLen = 0, cmp = 1, bit, sIndex = len - 1;
	char fillStr = '0';                                               // Default value that fills the string                                    
	if (isNegative == 1) {
		fillStr = '1';
		cmp = 0;
	}
	char* revBin = malloc (sizeof (char) * (len + 1));
	if (revBin == NULL) return NULL;
	for (; strLen < len; strLen++) revBin[strLen] = fillStr;          // Fills all the elements of the array to '1' as default for n<0, representing sign bits 
	revBin[strLen] = '\0';
	for (int i = 0; (num > 0 && i < len); i++) {
		bit = num % 2;
		if (bit == cmp) revBin[i] = cmp + '0';
		num /= 2;
	}
	char* bin = malloc (sizeof (char) * (len + 1));
	if (bin == NULL) return NULL;
	bin[len] = '\0';
	for (int i = 0; i < len; i++) {
		bin[i] = revBin[sIndex--];
	}
	free (revBin);
	return bin;
}

/// <summary>Converts the given input to binary</summary>
char* Binary (int num) {
	int digit = 0, numCpy = num;
	int power = 1;
	bool largestNum = 0, isNegative = 0;                              // Variable largestNum sets if the number is of order (2**(8n)-1)                
	if (num < 0) {
		num = -num, numCpy = num, isNegative = 1;
		long int newNum;
		for (digit = 0; numCpy > 0; digit++) numCpy = numCpy >> 1;
		if (digit >= 32) return NULL;                                  // Negative number with 32 bit length require 64 bit representation hence omitted
		for (int i = 0; i < digit + 1; i++) power = power << 1;
		if (num == (power - 1)) {
			largestNum = 1;
			newNum = (num ^ ((2 * power) - 1));         // 1's complement using EXOR bitwise operator 
		} else newNum = (num ^ (power - 1));
		newNum++;                                      // 2's complement i.e incrementing 1's complement
		num = newNum, numCpy = num;
	}
	for (digit = 0; numCpy > 0; digit++) numCpy = numCpy >> 1;
	if (digit > 32) return NULL;
	if (digit < 0) return NULL;
	for (int i = 0; i < digit + 1; i++) power = power << 1;
	if (num == (power - 1)) largestNum = 1;
	char* bin = BinaryString (isNegative, NearestByte (digit, largestNum), num);
	if (bin == NULL) exit (ERROR_MEM_ALLOC_FAILURE);
	return bin;
}

/// <summary>Converts the given input to hexadecimal</summary>
char* Hexadecimal (char* bin) {
	int binLen = 0, hexLen = 0, length = 0, sum = 0, bit = 1;
	if (bin == NULL) return NULL;
	for (int i = 0; bin[i] != '\0'; i++) length++;
	char* hexStr = malloc (sizeof (char) * ((length / 4) + 1));
	if (hexStr == NULL) exit (ERROR_MEM_ALLOC_FAILURE);
	while (binLen < length && hexLen < (length / 4)) {
		sum = 0;
		for (int i = 3; i >= 0; i--, binLen++) sum += (bin[binLen] - '0') * (bit << i);
		hexStr[hexLen++] = Arr[sum];
	}
	hexStr[hexLen] = '\0';
	return hexStr;
}

/// <summary>Method to print hexadecimal values using type specifier</summary>
void Hex (int num) {
	printf ("HEX: %X\n", num);
}

/// <summary>Prints the output of the program</summary>
int Call (int num) {
	char* bin;
	bin = Binary (num);
	if (bin == NULL) {
		printf ("The input exceeds the maximum length (32 bit)\n");
		return ERROR_EXCEEDED_LENGTH;
	}
	char* hex = Hexadecimal (bin);
	printf ("BIN : %s\nHEX : %s\n", bin, hex);
	free (bin);
	free (hex);
	return 0;
}

int main () {
	int c, lenIn = 0;
	char* inStr = malloc (sizeof (char) * 11);
	if (inStr == NULL) return ERROR_MEM_ALLOC_FAILURE;
	printf ("Enter an integer : ");
	while ((c = getchar ()) != '\n') {
		if ((lenIn == 0 && c == '-') || (c >= '0' && c <= '9' && lenIn <= 10)) {        // First character can be negative, others within 0-9
			inStr[lenIn++] = c;
		} else if (lenIn > 10) {                                                        // Exceeds maximum bit length (32 bit)
			printf ("The input exceeded maximum length\n");
			free (inStr);
			return ERROR_EXCEEDED_LENGTH;
		} else {
			printf ("The input is not an integer\n");                       // Returns for non-integer inputs
			free (inStr);
			return ERROR_INVALID_INPUT;
		}
	}
	inStr[lenIn] = '\0';
	int num = atoi (inStr);
	free (inStr);
	if (num != 0) Call (num);
	else printf ("BIN : 00000000\nHEX : 0000\n");                         // For input = 0
	return 0;
}