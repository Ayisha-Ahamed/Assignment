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
#include <limits.h>
#include "conversion.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Returns the nearest bit length.
int NearestBitLen (int digit) {
   if (digit <= 8) return 8;               // 1 byte
   else if (digit <= 16) return 16;        // 2 byte
   else return 32;                         // 4 bytes, maximum value 
}

// Converts the given input to binary.
char* Binary (char* input) {
   long int num = 0, numCpy = num, power = 1;
   int digit = 1, len, inInd = 0, lenIn = strlen (input);
   while (inInd < (lenIn - 1)) {
      if ((inInd == 0 && input[inInd] == '-') || (input[inInd] >= '0' && input[inInd] <= '9' && inInd <= 10)) inInd++; // First character can be negative, others within 0-9
      else return ERROR_INVALID_INPUT;
   }
   num = atol (input);
   char* bin;
   if (num < 0) {
      if (num == INT_MIN) return "10000000000000000000000000000000";                    //Default value corresponding to binary equivalent of INT_MIN
      int lenCpy;
      numCpy = -num;
      digit = (log (numCpy) / log (2)) + 1;                                             // To find the number of bits required to represent the input in binary
      len = NearestBitLen (digit) * 2;
      if (len > 32) len = 32;
      lenCpy = len;
      bin = malloc ((len + 1) * sizeof (char));
      if (bin == NULL) return NULL;
      for (int i = 0; (--lenCpy) >= 0; i++) bin[i] = ((num >> lenCpy) & 1) + '0';
      bin[len] = '\0';
      return bin;
   }
   digit = (log (num) / log (2)) + 1, len = NearestBitLen (digit);                      // To find the number of bits required to represent the number  
   int strLen = 0, bit, sIndex = len - 1;
   sIndex = len - 1;
   bin = malloc (sizeof (char) * (len + 1));
   if (bin == NULL) return ERROR_MEM_ALLOC;
   bin[strLen] = '\0';
   for (int i = 0; i < len; i++) {
      bit = num & 1;
      if (bit == 1 && num > 0) bin[sIndex--] = '1';
      else bin[sIndex--] = '0';
      num >>= 1;
   }
   bin[len] = '\0';
   return bin;
}

// Converts the binary input string to hexadecimal.
char* Hexadecimal (char* input) {
   long int num = 0, numCpy, power = 1;
   num = atol (input);
   int digit, bitLen, last = 0, inInd = 0, lenIn = strlen (input);                          // Variable last stores the decimal value of the last hex bit for numbers above 28 bit 
   bool isNegative = 0, isThirtyTwo = 0, isLastBit = 0;
   char arr[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };   // Array of hexadecimal equivalent characters
   while (inInd < (lenIn - 1)) {
      if ((inInd == 0 && input[inInd] == '-') || (input[inInd] >= '0' && input[inInd] <= '9' && inInd <= 10)) inInd++; // First character can be negative, others within 0-9
      else return ERROR_INVALID_INPUT;
   }
   if (num < 0) {
      isNegative = 1;
      num = -num, numCpy = num;
      for (digit = 0; numCpy > 0; digit++)  numCpy >>= 1;                                // Since log function cannot be used on negated INT_MIN due to integer overflow , a loop is used 
      if (digit == 0) return "80000000";                                                 // Digit = 0 only when input is INT_MIN due to integer overflow
      if (digit >= 31) {                                                                 // 32 bit numbers are handled differently to avoid int overflow
         num = num - INT_MIN;
         isThirtyTwo = 1;
         num = -num;
      } else {
         num = -num;
         int lastBit = 31; int expo = 3, bit = 1;
         while (lastBit > 27) {
            last += (bit << expo) * ((num >> lastBit) & 1);
            expo--; lastBit--;
         }
         num = -num;
         power <<= digit;
         if (!(power << 4 <= 0)) power <<= 3;
         if (!(power << 3 <= 0)) power <<= 2;
         if (!(power << 2 <= 0)) power <<= 1;
         if (num == (power - 1)) num = num ^ ((2 * power) - 1);                          // 1's complement using EXOR bitwise operator 
         else num = (num ^ (power - 1));                                                 // 2's complement i.e incrementing 1's complement
         num++;
      }
   }
   digit = (log (num) / log (2)) + 1, bitLen = NearestBitLen (digit) / 4;                // To find the number of bits required to represent the number  
   int strLen = 0, cmp = 1, bit, sIndex;
   char fillStr = '0';
   if (isThirtyTwo) fillStr = '0', cmp = 1, isNegative = 0, bitLen = 8;
   if (isNegative && isThirtyTwo != 1) fillStr = 'F', cmp = 0;                           // For negative numbers, bits exceeding 2's complement of num is set to 'F'
   char* hexStr = malloc (sizeof (char) * (bitLen + 1));
   sIndex = bitLen - 1;
   if (hexStr == NULL) return "Memory Allocation Error";
   for (int i = 0; i < bitLen; i++) {
      bit = num & 0xF;
      if (num > 0) hexStr[sIndex--] = arr[bit];
      else hexStr[sIndex--] = fillStr;
      num >>= 4;
   }
   hexStr[bitLen] = '\0';
   if (isThirtyTwo) hexStr[0] = '8';
   if (isNegative) hexStr[0] = arr[last];
   return hexStr;
}


