// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// conversion.c
// Program to convert the given input decimal number to Binary and Hexadecimal
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#pragma warning (disable:4996)
#define ERROR_MEM_ALLOC_FAILURE -1
#define NO_ARGS -2

char Arr[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

int NearestByte (int n, bool flag, int base) {
	int k = 8,p = 2;
	for (int i = 1; i <= n; i++) {
		if (k >= n) return k;
		k *=p;                                  //Bits are of length 8,16,32 or 64
	}
	if ((flag == true) && (n != 0))	return k * 2;
	else return k;
}

//Returns the number of bits that will be present in the binary output
int Digits (int n, int base) {
	int digit;
	for (digit = 0; n > 0; digit++) n = n / base;
	if (base == 2)digit += (digit % 4);        //To make bit length to be multipliers of 4 for hex conversion
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
char* BinaryString (bool y, int len, int n) {
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
char* Binary (int n) {
	int digit;
	long long int power;
	bool flag = 0;                         //Flag sets if the number is of order (2**(8n)-1)
	bool signOfDigit = 0;                  //positive value of n
	if (n < 0) {
		n = -n;
		signOfDigit = 1;
		digit = Digits (n, 2);
		power = Power (digit, 2);
		long long int b;
		if (n == (power - 1)) {
			flag = 1;
			b = (n ^ ((2 * power) - 1));      //1's complement using EXOR bitwise operator 
		} else b = (n ^ (power - 1));        
		b++;                                 //2's complement i.e Incrementing 1's complement
		n = b;
	}
	digit = Digits (n, 2);
	power = Power (digit, 2);
	if (n == (power - 1)) {
		flag = 1;
	}
	char* s = BinaryString (signOfDigit, NearestByte (digit, flag, 2), n);
	if (s == NULL)exit (ERROR_MEM_ALLOC_FAILURE);
	return s;
}

//Converts the given input to hexadecimal 
char* Hexadecimal (int n) {
	char* s = Binary (n);
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
int Call (int n) {
	printf ("INPUT : %d\n", n);
	printf ("BIN : %s \n", Binary (n));
	printf ("HEX : %s \n", Hexadecimal (n));
	printf ("\n");
	return 0;
}

int main (int argc, char* argv[]) {
	Call (-1024);
	Call (-255);
	Call (-8094);
	Call (1023);
	Call (-123445);
}