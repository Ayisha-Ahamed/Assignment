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

#define BLACKPAWN L"\u265F"
#define WHITEPAWN L"\u2659 "
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

// Function that prints and writes a string to a file
static void Print (FILE* fp, wchar_t* string) {
   wprintf (L"%ls", string);
   fwprintf (fp, string);
}

static void PrintLines (FILE* fp, wchar_t* a, wchar_t* b, wchar_t* c) {
   wprintf (L"\n%ls", a);
   fwprintf (fp, L"\n%s", a);
   for (int i = 0; i < 7; i++) {
      wprintf (L"\u2501\u2501\u2501%ls", b);
      fwprintf (fp, L"\u2501\u2501\u2501%ls", b);
   }
   wprintf (L"\u2501\u2501\u2501%ls", c);
   fwprintf (fp, L"\u2501\u2501\u2501%ls", c);
}

// First row of the chess board grid
static void Start (FILE* fp) {
   PrintLines (fp, L"\u250F", L"\u2533", L"\u2513");
}

// Middle row of chess board grid in between the boxes above and below
static void Middle (FILE* fp) {
   PrintLines (fp, L"\u2523", L"\u254B", L"\u252B");
}

// Last row of the chess board grid
static void End (FILE* fp) {
   PrintLines (fp, L"\u2517", L"\u253B", L"\u251B");
}

// Middle column of chess board grid in between two boxes in the grid
static void Lines (FILE* fp) {
   Print (fp, L"\n\u2503");
   for (int i = 0; i < 8; i++)
      Print (fp, L"   \u2503");
}

static void PrintPawn (FILE* fp, wchar_t* pawn) {
   Print (fp, L"\n\u2503");
   for (int i = 0; i < 8; i++) {
      wprintf (L" %ls\u2503", pawn);
      fwprintf (fp, L" %ls\u2503", pawn);
   }
}

static void WhitePawn (FILE* fp) {
   PrintPawn (fp, WHITEPAWN);
}

static void BlackPawn (FILE* fp) {
   PrintPawn (fp, BLACKPAWN);
}

static void PrintChars (FILE* fp, wchar_t arr[5]) {
   Print (fp, L"\n\u2503");
   for (int i = 0; i < 8; i++) {
      wprintf (L" %lc \u2503", arr[i % 5]);
      fwprintf (fp, L" %lc \u2503", arr[i % 5]);
   }
}

static void WhiteChars (FILE* fp) {
   wchar_t White[5] = { L'\u2656',L'\u2658',L'\u2657',L'\u2655',L'\u2654' };
   PrintChars (fp, White);
}

static void BlackChars (FILE* fp) {
   wchar_t Black[5] = { L'\u265C',L'\u265E',L'\u265D',L'\u265B',L'\u265A' };
   PrintChars (fp, Black);
}

static void Chess (FILE* fp) {
   for (int i = 0; i < 8; i++) {
      switch (i) {
         case 0: Start (fp); BlackChars (fp); Middle (fp); break;
         case 1: BlackPawn (fp); Middle (fp); break;
         case 6: WhitePawn (fp); Middle (fp); break;
         case 7: WhiteChars (fp); End (fp); break;
         default: Lines (fp); Middle (fp); break;
      }
   }
}

// Returns the row and column number in which a file was last read.
// Checks if the two files are of same length.
static int FileCompare (FILE* ref, FILE* output, int* row, int* col) {
   wchar_t refChar = getwc (ref), outChar = getwc (output);
   *row = 1, * col = 0;
   while ((refChar != WEOF) && (outChar != WEOF)) {
      *col += 1;
      if (refChar != outChar) return -3;  // Return reference character
      if (refChar == '\n') {
         *row += 1;
         *col = 0;
      }
      refChar = getwc (ref);
      outChar = getwc (output);
   }
   // To check if both the output and the reference files are of same length
   if (refChar != outChar)
      return refChar != WEOF ? -1 : -2;
   return 2; // Successful comparision of files
}

int main () {
   int k = _setmode (_fileno (stdout), _O_U8TEXT);
   FILE* output = fopen ("Chess.txt", "w+,ccs=UTF-8");
   if (output == NULL) {
      wprintf (L"Failed to open Chess.txt\n");
      return -1;
   }
   Chess (output);
   fclose (output);
   wprintf (L"\n\nDo you want to run test case? (y/n) ");
   int c = getchar ();
   if (tolower (c) == 'y') {
      output = fopen ("Chess.txt", "r+,ccs=UTF-8");
      FILE* ref = fopen ("Chess_Ref.txt", "r+,ccs=UTF-8");
      if (ref == NULL) {
         wprintf (L"Failed to open reference file\n");
         return -1;
      }
      int row, col, result = FileCompare (ref, output, &row, &col);
      switch (result) {
         case -1: wprintf (L"Error at row %d, col %d. Output file reached EOF\n", row, col); break;
         case -2: wprintf (L"Error at row %d, col %d. "
                           "Reference file reached EOF\n", row, col); break;
         case 2: wprintf (CYAN""L"Test Passed\n"RESET); break;
         default: wprintf (L"Error at row %d, col %d\n", row, col); break;
      }
      fclose (output);
      fclose (ref);
   }
   return 0;
}