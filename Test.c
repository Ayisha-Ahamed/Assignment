// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch A6.
// Program to print chess board.
// ------------------------------------------------------------------------------------------------
#pragma warning (disable:4996)
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>

#define BLACKPAWN L" \u265F"
#define WHITEPAWN L" \u2659 "
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

// Function that prints and writes a string to a file
static void Print (FILE* fp, wchar_t* string, wchar_t* param) {
   wchar_t* input = param == NULL ? L"" : param;
   wchar_t str[45];
   swprintf (str, 21, L"%ls%ls", string, input);
   wprintf (L"%ls%ls", string, input);
   fwprintf (fp, str);
}

static void PrintLines (FILE* fp, wchar_t* a, wchar_t* b, wchar_t* c) {
   Print (fp, L"\n", a);
   for (int i = 0; i < 7; i++)
      Print (fp, L"\u2501\u2501\u2501", b);
   Print (fp, L"\u2501\u2501\u2501", c);
}

static void PrintPawn (FILE* fp, wchar_t* pawn) {
   Print (fp, L"\n\u2503", NULL);
   for (int i = 0; i < 8; i++)
      Print (fp, pawn, L"\u2503");
}

static void PrintChars (FILE* fp, bool isBlack) {
   wchar_t White[5] = { L'\u2656',L'\u2658',L'\u2657',L'\u2655',L'\u2654' };
   wchar_t Black[5] = { L'\u265C',L'\u265E',L'\u265D',L'\u265B',L'\u265A' };
   wchar_t* arr = isBlack ? Black : White;
   Print (fp, L"\n\u2503", NULL);
   for (int i = 0; i < 8; i++) {
      wprintf (L" %lc \u2503", arr[i % 5]);
      fwprintf (fp, L" %lc \u2503", arr[i % 5]);
   };
}

static void Chess (FILE* fp) {
   PrintLines (fp, L"\u250F", L"\u2533", L"\u2513");
   for (int i = 0; i < 8; i++) {
      switch (i) {
         case 0: PrintChars (fp, true); PrintLines (fp, L"\u2523", L"\u254B", L"\u252B"); break;
         case 1: PrintPawn (fp, BLACKPAWN); PrintLines (fp, L"\u2523", L"\u254B", L"\u252B"); break;
         case 6: PrintPawn (fp, WHITEPAWN); PrintLines (fp, L"\u2523", L"\u254B", L"\u252B"); break;
         case 7: PrintChars (fp, false); PrintLines (fp, L"\u2517", L"\u253B", L"\u251B"); break;
         default: PrintPawn (fp, L"   "); PrintLines (fp, L"\u2523", L"\u254B", L"\u252B"); break;
      }
   }
}

// Checks if the two files are of same length.
static int FileCompare (FILE* ref, FILE* output, int* row, int* col) {
   wchar_t refChar = getwc (ref), outChar = getwc (output);
   *row = 1, * col = 0;
   while ((refChar != WEOF) && (outChar != WEOF)) {
      *col += 1;
      if (refChar != outChar) return -3;
      if (refChar == '\n') {
         *row += 1;
         *col = 0;
      }
      refChar = getwc (ref);
      outChar = getwc (output);
   }
   // To check if both the output and the reference files reached EOF
   if (refChar != outChar)
      return refChar != WEOF ? -1 : -2;
   return 0;
}

int main () {
   int k = _setmode (_fileno (stdout), _O_U8TEXT);
   FILE* output = fopen ("Chess.txt", "w+,ccs=UTF-8"), * ref = fopen ("Chess_Ref.txt", "r+,ccs=UTF-8");
   if (output == NULL || ref == NULL) {
      wprintf (L"Failed to open file(s)\n");
      return -1;
   }
   Chess (output);
   fclose (output);
   wprintf (L"\n\nDo you want to run test case? (y/n) ");
   int c = getchar ();
   if (tolower (c) == 'y') {
      output = fopen ("Chess.txt", "r+,ccs=UTF-8");
      int row, col, result = FileCompare (ref, output, &row, &col);
      switch (result) {
         case 0: wprintf (CYAN""L"Test Passed\n"RESET); break;
         case -1: wprintf (L"Error at row %d, col %d. Output file reached EOF\n", row, col); break;
         case -2: wprintf (L"Error at row %d, col %d. Reference file reached EOF\n",
                           row, col); break;
         default: wprintf (L"Error at row %d, col %d\n", row, col); break;
      }
      fclose (output);
      fclose (ref);
   }
   return 0;
}