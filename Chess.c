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
#include <errno.h>
#include <stdbool.h>
#include <malloc.h>

#define BLACKPAWN L" \u265F "
#define WHITEPAWN L" \u2659 "

// Color codes.
#define CYAN "\033[1;36m"
#define RESET "\033[0m"
#define MAX_LEN 35  // Maximum column length of chess board.

// Error codes for file comparision
#define MEM_ALLOC_ERROR -3
#define INT_OVERFLOW -4

typedef enum {
   start,
   middle,
   end
}Line;

///<summary>Prints and writes a string to a file.</summary>
static void PrintAndWrite (FILE* fp, wchar_t* string, wchar_t* param) {
   wchar_t* input = param == NULL ? L"" : param;
   wchar_t str[MAX_LEN];
   swprintf (str, MAX_LEN, L"%ls%ls", string, input);
   wprintf (L"%ls%ls", string, input);
   fwprintf (fp, str);
}

///<summary>Function to print lines separating.</summary>
static void PrintLines (FILE* fp, Line input) {
   switch (input) {
      case start: PrintAndWrite (fp, L"┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓", NULL); break;
      case middle:PrintAndWrite (fp, L"\n┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫", NULL); break;
      case end: PrintAndWrite (fp, L"\n┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛", NULL); break;
   }
}

///<summary>Repeats the input wide character across 8x8 grid.</summary>
static void RepeatChar (FILE* fp, wchar_t* pawn) {
   PrintAndWrite (fp, L"\n┃", NULL);
   for (int i = 0; i < 8; i++) PrintAndWrite (fp, pawn, L"┃");
}

///<summary>Prints all playable chess characters except pawn.</summary>
static void PrintChars (FILE* fp, bool isBlack) {
   wchar_t White[] = { L'♖',L'♘',L'♗',L'♕',L'♔',L'♗',L'♘',L'♖' };
   wchar_t Black[] = { L'♜',L'♞',L'♝',L'♛',L'♚',L'♝',L'♞',L'♜' };
   wchar_t* arr = isBlack ? Black : White;
   PrintAndWrite (fp, L"\n┃", NULL);
   for (int i = 0; i < 8; i++) {
      wprintf (L" %lc ┃", arr[i]);
      fwprintf (fp, L" %lc ┃", arr[i]);
   };
}

///<summary>Displays the chess board.</summary>
static void DisplayChessBoard (FILE* fp) {
   PrintLines (fp, start);
   for (int i = 0; i < 8; i++) {
      switch (i) {
         case 0: PrintChars (fp, true); PrintLines (fp, middle); break;
         case 1: RepeatChar (fp, BLACKPAWN); PrintLines (fp, middle); break;
         case 6: RepeatChar (fp, WHITEPAWN); PrintLines (fp, middle); break;
         case 7: PrintChars (fp, false); PrintLines (fp, end); break;
         default: RepeatChar (fp, L"   "); PrintLines (fp, middle); break;
      }
   }
   PrintAndWrite (fp, L"\0", NULL);
}

///<summary>Checks if the two files are identical.</summary>
static int FileCompare (FILE* ref, FILE* output, int* row, int* col) {
   fseek (ref, 0, SEEK_END);
   fseek (output, 0, SEEK_END);
   errno = 0;
   int refSize = ftell (ref), outSize = ftell (output);
   fseek (ref, 0, SEEK_SET);
   fseek (output, 0, SEEK_SET);
   if (errno == ERANGE) return INT_OVERFLOW;
 //  if (refSize != outSize) return -1;  // Files are different.
   wchar_t* refStr = malloc (refSize), * outStr = malloc (outSize);
   if (refStr == NULL || outStr == NULL) return MEM_ALLOC_ERROR;
   fread (refStr, 1, refSize, ref);
   fread (outStr, 1, outSize, output);
   *row = 0, * col = 0;
   for (int i = 0; i < refSize / sizeof (wchar_t); i++) {
      *col += 1;
      wchar_t char1 = refStr[i], char2 = outStr[i];
      if (refStr[i] == '\n') *row += 1;
      if (refStr[i] != outStr[i]) {
         free (refStr);
         free (outStr);
         return -2;  // Mismatch
      }
   }
   free (refStr);
   free (outStr);
   return 0; // Size mismatch
}

int main () {
   int setModeStatus = _setmode (_fileno (stdout), _O_U8TEXT);
   if (setModeStatus == -1) {
      printf ("Unable to set console output to U-8 mode\n");
      return -1;
   }
   FILE* output = fopen ("Chess_Out.txt", "w+,ccs=UTF-8"),
      * ref = fopen ("Chess_Ref.txt", "r+,ccs=UTF-8");
   if (output == NULL || ref == NULL) {
      wprintf (L"Failed to open file(s)\n");
      return -1;
   }
   DisplayChessBoard (output);
   PrintAndWrite (output, L"\n", NULL);
   fclose (output);
   output = fopen ("Chess_Out.txt", "r+,ccs=UTF-8");
   int row = 0, col = 0, result = FileCompare (ref, output, &row, &col);
   switch (result) {
      case 0: wprintf (CYAN""L"Test Passed.\n"RESET); break;
      case -1: wprintf (L"Files are different\nTest Failed.\n"); break;
      case -3: wprintf (L"Error allocating memory.\n"); break;
      case -4: wprintf (L"File size is too large.\n"); break;
      default: wprintf (L"Error at row %d, col %d.\nTest Failed.\n", row, col); break;
   }
   fclose (output);
   fclose (ref);

   return 0;
}