// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// TicTacToe.c
// Program on branch Test3.1
// Program implements TiTacToe with 2 or 1 player mode.
// Program displays the board upon valid moves.
// ------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#define DIA1 6
#define DIA2 7

static int TicTacToe (char* grid, int index, int playerId) {
   // 3 x 3 Grid consists of three rows, three columns and two diagonals(8 possibilities)
   static int sCount[8][2] = {
      {0,0},  // Row 1 { Count of Player 1 symbols in row1 ,Count of Player 2 symbols in row1 }
      {0,0},  // Row 2                  .
      {0,0},  // Row 3                  .
      {0,0},  // Column 1               .
      {0,0},  // Column 2               .
      {0,0},  // Column 3               .
      {0,0},  // Diagonal 1 (Left to right, Box positions 1-5-9)
      {0,0}   // Disgonal 2 (Right to left, Box positions 3-5-7)
   };
   int rowNo = index / 3, colNo = index % 3 + 3;
   int player = playerId - 1;
   sCount[rowNo][player] += 1;
   sCount[colNo][player] += 1;
   if (index ^ 1) {
      switch (index) {
         case 0: sCount[DIA1][player] += 1; break;  // Diagonal 1, index positions 0-4-8
         case 2: sCount[DIA2][player] += 1; break;  // Diagonal 2, index positions 2-4-6
         case 4: sCount[DIA1][player] += 1; sCount[DIA2][player] += 1; break;
         case 6: sCount[DIA2][player] += 1; break;
         case 8: sCount[DIA1][player] += 1; break;
      }
   }
   if (sCount[rowNo][player] >= 3 || sCount[colNo][player] >= 3 ||
       sCount[DIA1][player] >= 3 || sCount[DIA2][player] >= 3) return playerId;
   return 0;
}

// Returns input character obtained from the user.
static char GetInput (wchar_t* prompt) {
   char input[5];
   do {
      wprintf (L"%s ", prompt);
      fgets (input, sizeof (input), stdin);
      // If the input exceeds 5 characters, clear input buffer.
      if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
   } while (isspace (input[0]) || strlen (input) > 2);
   return input[0];
}

// Gets two non-space unique symbols to represent player 1 and 2.
static void GetSymbol (char* s1, char* s2) {
   *s1 = GetInput (L"Enter symbol 1:");
   do *s2 = GetInput (L"Enter symbol 2:");
   while (*s1 == *s2);
}

// Prints 3 x 3 game board.
static void PrintBoard (char* grid) {
   wprintf (L"┏━━━┳━━━┳━━━┓\n┃");
   for (int row = 0, index = 0; row < 3; row++) {
      for (int col = 0; col < 3 && index < 9; index++, col++) wprintf (L" %wc ┃", grid[index]);
      if (row < 2) wprintf (L"\n┣━━━╋━━━╋━━━┫\n┃");
   }
   wprintf (L"\n┗━━━┻━━━┻━━━┛\n");
}

// Returns the index of the box number within the range of 0-8.
static int GetBoxNum (char* grid, bool isAutoPlay) {
   if (isAutoPlay) {
      int num = 4;
      while (grid[num] != L' ') num = rand () % 9;
      return num;
   }
   while (true) {
      char boxNum = GetInput (L"Enter box number (1-9):");
      if (boxNum < L'1' || boxNum > L'9' || grid[boxNum - L'1'] != L' ') {
         wprintf (L"Entered box number is either occupied or invalid\n");
         return -1;
      }
      return boxNum - '1';
   }
}

static bool ModeChoice () {
   char choice = ' ';
   do
      choice = GetInput (L"Enter (1/2):");
   while (choice != '1' && choice != '2');
   return choice == '1';
}

int main () {
   int val = _setmode (_fileno (stdout), _O_U8TEXT), Player = 1, boxNum;
   char P1, P2;
   GetSymbol (&P1, &P2);
   char grid[9] = { L' ',L' ',L' ' ,L' ' ,L' ' ,L' ' ,L' ' ,L' ',L' ' }, symbols[2] = { P1,P2 };
   wprintf (L"Enter 1 to play against the computer. Enter 2 for dual player mode.\n");
   bool isAutoPlay = ModeChoice ();
   for (int turn = 1; turn < 10; turn++, Player = 2) {
      if (turn & 1) Player = 1;        // Player 1 plays odd number of turns.
      wprintf (L"Player %d :\n", Player);
      do
         boxNum = GetBoxNum (grid, isAutoPlay && Player == 2);
      while (boxNum == -1);
      grid[boxNum] = symbols[Player - 1];
      PrintBoard (grid);
      switch (TicTacToe (grid, boxNum, Player)) {
         case 1: wprintf (L"\nPlayer 1 wins\n"); return 0;
         case 2: wprintf (L"\nPlayer 2 wins\n"); return 0;
      }
   }
   wprintf (L"\nDraw\n");
   return 0;
}