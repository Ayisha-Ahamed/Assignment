// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// conversion.c
// Functions to convert a decimal number to binary and hexadecimal.
// ------------------------------------------------------------------------------------------------
#pragma warning (disable:4996)
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define ERROR_MEM_ALLOC_FAILURE -1
#define MAX_BIT 32   

/// <summary>Returns the nearest bit length</summary>
int NearestBitLen (int digit) {
	int bitLen = 8;
	while (bitLen < digit) bitLen *= 2;
	return bitLen;
}

/// <summary>Returns the binary equivalent of input to string</summary>
char* BinaryString (bool isNegative, int len, long int num, bool isThirtyTwo) {
	int strLen = 0, cmp = 1, bit, sIndex = len - 1;
	char fillStr = '0';                                               // Default value that fills the string                                    
	if (isNegative == 1) {
		fillStr = '1';
		cmp = 0;
	}
	char* revBin = malloc (sizeof (char) * (len + 1));
	if (revBin == NULL) exit (ERROR_MEM_ALLOC_FAILURE);
	for (; strLen < len; strLen++) revBin[strLen] = fillStr;          // Fills all the elements of the array to '1' as default for n<0, representing sign bits 
	revBin[strLen] = '\0';
	for (int i = 0; (num > 0 && i < len); i++) {
		bit = num & 1;
		if (bit == cmp) revBin[i] = cmp + '0';
		num >>= 1;
	}
	char* bin = malloc (sizeof (char) * (len + 1));
	if (bin == NULL) exit (ERROR_MEM_ALLOC_FAILURE);
	bin[len] = '\0';
	for (int i = 0; i < len; i++) bin[i] = revBin[sIndex--];
	free (revBin);
	if (isThirtyTwo == 1)bin[0] = '1';
	return bin;
}

/// <summary>Converts the given input to binary</summary>
char* Binary (long int num) {
	long int numCpy = num, power = 1, newNum;
	int digit = 0;
	bool isNegative = 0;
	char* bin = "10000000000000000000000000000000";                                       //Default value corresponding to binary equivalent of INT_MIN
	if (num < 0) {
		num = -num, numCpy = num, isNegative = 1;
		for (digit = 0; numCpy > 0; digit++) numCpy = numCpy >> 1;
		if (digit == 0) return bin;                                                        // Digit = 0 only when input is INT_MIN due to integer overflow
		if (digit >= 31) {                                                                 // 32 bit numbers are handled differently to avoid overflow
			num = num - INT_MIN;
			bin = BinaryString (0, MAX_BIT, -num, 1);
			return bin;
		}
		power = power << digit;
		if (!(power << 1 <= 0)) power <<= 1;
		if (num == (power - 1)) newNum = num ^ ((2 * power) - 1);                          // 1's complement using EXOR bitwise operator 
		else newNum = (num ^ (power - 1));                                                 // 2's complement i.e incrementing 1's complement
		num = ++newNum, numCpy = num;
	}
	for (digit = 0; numCpy > 0; digit++) numCpy = numCpy >> 1;
	if (digit > 32) return NULL;
	bin = BinaryString (isNegative, NearestBitLen (digit), num, 0);
	if (bin == NULL) exit (ERROR_MEM_ALLOC_FAILURE);
	return bin;
}

/// <summary>Converts the binary input string to hexadecimal</summary>
char* Hexadecimal (char* bin) {
	char arr[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };   // Array of hexadecimal equivalent characters
	int binLen = 0, hexLen = 0, length = strlen (bin), sum = 0, bit = 1, len = length / 4;
	if (bin == NULL) return NULL;
	char* hexStr = malloc (sizeof (char) * (len + 1));
	if (hexStr == NULL) exit (ERROR_MEM_ALLOC_FAILURE);
	while (binLen < length && hexLen < len) {
		sum = 0;
		for (int i = 3; i >= 0; i--, binLen++) sum += (bin[binLen] - '0') << i;
		hexStr[hexLen++] = arr[sum];
	}
	hexStr[hexLen] = '\0';
	return hexStr;
}

