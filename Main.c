// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch Test3.1
// Program that implements TicTacToe.c.
// ------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include "TicTacToe.h"

static wchar_t Get_Input (wchar_t* prompt) {
   wchar_t inChar = L' ';
   while (inChar == L' ' || inChar == '\n') {
      wprintf (L"%s ", prompt);
      inChar = getwchar ();
      if (inChar == '\n') continue;
      while (getchar () != '\n');
   };
   return inChar;
}
static void Get_Symbol (wchar_t* s1, wchar_t* s2) {
   *s1 = Get_Input (L"Enter symbol 1 :");
   *s2 = Get_Input (L"Enter symbol 2 :");
   while (*s1 == *s2) *s2 = Get_Input (L"Please enter a unique symbol. Enter symbol 2 :");
}

static void PrintBoard (wchar_t* arr) {
   wprintf (L"\u250F\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2513\n\u2503");
   for (int i = 0, l = 0; i < 3; i++) {
      for (int k = 0; k < 3; l++, k++) wprintf (L" %wc \u2503", arr[l]);
      if (l == 9) break;
      wprintf (L"\n\u2523\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u252B\n\u2503");
   }
   wprintf (L"\n\u2517\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u251B\n");
}

static int Get_Box_Num (wchar_t* arr, bool isAutoPlay) {
   if (isAutoPlay) {
      int num = 4;
      while (arr[num] != L' ') num = rand () % 9;
      return num;
   }
   while (true) {
      wprintf (L"Enter box number (1-9): ");
      wchar_t c = getwchar ();
      while (getwchar () != L'\n');
      if (c < L'1' || c > L'9' || arr[c - L'1'] != ' ') continue;
      return c - '1';
   }
}

int main () {
   int k = _setmode (_fileno (stdout), _O_U8TEXT);
   wchar_t P1, P2,
      grid[9] = { L' ',L' ',L' ' ,L' ' ,L' ' ,L' ' ,L' ' ,L' ',L' ' };
   Get_Symbol (&P1, &P2);
   bool isPlayer1 = true, isAutoPlay = false;
   wprintf (L"Enter 1 to play against the computer."
            " Enter any non-space character for dual player mode\n");
   if (Get_Input (L"Enter your response :") == L'1') isAutoPlay = true;
   for (int i = 0; i < 9; i++) {
      wprintf (L"%ls :\n", isPlayer1 ? L"Player 1" : L"Player 2");
      int index = Get_Box_Num (grid, isAutoPlay && !isPlayer1);
      grid[index] = isPlayer1 ? P1 : P2;
      PrintBoard (grid);
      switch (TicTacToe (grid, index, isPlayer1)) {
         case 0: break;
         case 1: wprintf (L"\nPlayer 1 wins\n"); return 0;
         case 2: wprintf (L"\nPlayer 2 wins\n"); return 0;
      }
      isPlayer1 = !isPlayer1;
   }
   wprintf (L"\nDraw\n");
   return 0;
}