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

char Arr[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

int NearestByte (int digit, bool flag, int base) {
	int k = 8, p = 2;
	for (int i = 1; i <= digit; i++) {
		if (k >= digit) return k;
		k *= p;                               //Bits are of length 8,16,32 
	}
	if ((flag == true) && (digit != 0))k *= 2;
	return k;
}

//Returns the number of bits that will be present in the binary output
int Digits (long long int n, int base, int flag) {
	int digit;
	for (digit = 0; n > 0; digit++) n = n / base;
	digit += (digit % 4);                   //To make bit length to be multipliers of 4 for hex conversion
	if (digit > 32) return ERROR_EXCEEDED_LENGTH;
	if ((digit == 32) && (flag == 1))return ERROR_EXCEEDED_LENGTH;
	return digit;
}

//Returns the number higher than the MSB of the expected binary output
long long int Power (int digit, int base) {
	long long int power = 1;
	while (digit > 0) {
		power = power * base;
		digit--;
	}
	return power;
}

//Returns the power of input by raising it to its degree
int Exponent (int base, int degree) {
	int x = 1; int y = base;
	while (degree > 0) {
		x *= y;
		degree--;
	}
	return x;
}

//Returns the binary equivalent of input to string
char* BinaryString (bool y, int len, long long int n) {
	int i = 0;
	char c, d;
	int e;
	if (y == 1) {
		c = '1';
		d = '0';
		e = 0;
	} else {
		c = '0';
		d = '1';
		e = 1;
	}
	char* s = malloc ((sizeof (char)) * (len + 1));
	if (s == NULL) return NULL;
	for (; i < len; i++) s[i] = c;          //Fills all the elements of the array to '1' for n<0, '0' otherwise 
	s[i] = '\0';
	int k;
	for (int i = 0; ((n > 0) && (i < len)); i++) {
		k = n % 2;
		if (k == e) s[i] = d;
		n = n / 2;
	}
	char* t = malloc ((sizeof (char)) * (len + 1));
	if (t == NULL)return NULL;
	t[len] = '\0';
	int sIndex = len - 1;
	for (int i = 0; i < len; i++) {
		t[i] = s[sIndex];
		sIndex--;
	}
	free (s);
	return t;
}

//Converts the given input to hexadecimal
char* Binary (long long int n) {
	int digit;
	long long int power;
	bool flag = 0;                         //Flag sets if the number is of order (2**(8n)-1)
	bool signOfDigit = 0;                  //positive value of n
	if (n < 0) {
		n = -n;
		signOfDigit = 1;
		digit = Digits (n, 2, signOfDigit);
		if (digit < 0) return NULL;
		power = Power (digit, 2);
		long long int b;
		if (n == (power - 1)) {
			flag = 1;
			b = (n ^ ((2 * power) - 1));      //1's complement using EXOR bitwise operator 
		} else b = (n ^ (power - 1));
		b++;                                 //2's complement i.e Incrementing 1's complement
		n = b;
	}
	digit = Digits (n, 2, signOfDigit);
	if (digit < 0) return NULL;
	power = Power (digit, 2);
	if (n == (power - 1)) {
		flag = 1;
	}
	char* s = BinaryString (signOfDigit, NearestByte (digit, flag, 2), n);
	if (s == NULL)exit (ERROR_MEM_ALLOC_FAILURE);
	return s;
}

//Converts the given input to hexadecimal 
char* Hexadecimal (long long int n) {
	char* s = Binary (n);
	if (s == NULL) return NULL;
	int length = 0, sum = 0;
	for (int i = 0; s[i] != '\0'; i++)length++;
	char* h = malloc (sizeof (char) * ((length / 4) + 1));
	if (h == NULL)exit (ERROR_MEM_ALLOC_FAILURE);
	int k = 0;
	int strLen = 0;
	while ((k < length) && (strLen < (length / 4))) {
		sum = 0;
		for (int i = 3; i >= 0; i--, k++) {
			sum += (s[k] - '0') * Exponent (2, i);
		}
		h[strLen] = Arr[sum];
		strLen++;
	}
	h[strLen] = '\0';
	return h;
}

//Calling function
void Call (long long int n) {
	char* bin = Binary (n);
	char* hex = Hexadecimal (n);
	if (bin == NULL) { 
		printf ("The input exceeds the maximum length (32 bit)");
		return;
	}
	printf ("INPUT : %lld\n", n);
	printf ("BIN : %s \n", bin);
	printf ("HEX : %s \n", hex);
	printf ("\n");
	return;
}

int main () {

	int c;
	char* s = malloc (sizeof (char) * 11);
	if (s == NULL) return ERROR_MEM_ALLOC_FAILURE;
	int i = 0;
	printf ("Enter an integer : \n");
	while ((c = getchar ()) != '\n') {
		if ((i == 0) && (c == '-')) {
			s[i] = c;
			i++;
		} else if ((c >= '0') && (c <= '9') && (i <= 10)) {
			s[i] = c;
			i++;
		} else if (i > 10) {
			printf ("The input exceeded maximum length\n");
			free (s);
			return ERROR_EXCEEDED_LENGTH;
		} else {
			printf ("The input is not an integer\n");
			free (s);
			return ERROR_INVALID_INPUT;
		}

	}
	s[i] = '\0';
	int num = atoi (s);
	free (s);
	Call (num);

	//Call (-1024);
	//Call (-255);
	//Call (-8094);
	//Call (1023);
	//Call (-123445);
	//Call (-5676768790);                      //Binary value exceeds 32 bit , returns NULL

	return 0;
}