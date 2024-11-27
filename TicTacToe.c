// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// TicTacToe.c
// Program on branch main.
// Program that stores the number of player symbols (dual player) in the 3 x 3 grid 
// Program stores the count of symbols in the order of rows, columns, and diagonals
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include "TicTacToe.h"

#define DIA1 6
#define DIA2 7

int TicTacToe (wchar_t* grid, int index, bool isPlayer1) {
   // 3 x 3 Grid consists of three rows, three columns and two diagonals(8 possibilities)
   static int Count[8][2] = {
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
   int player = isPlayer1 ? 0 : 1;
   Count[rowNo][player] += 1;
   Count[colNo][player] += 1;
   if (index == 4) Count[DIA2][player] += 1;
   if (index % 2 == 0) {
      if (index % 4 == 0) Count[DIA1][player] += 1;  // Diagonal 1, index positions 0-4-8
      else Count[DIA2][player] += 1;                 // Diagonal 2, index positions 2-4-8
   }
   if (Count[rowNo][player] >= 3 || Count[colNo][player] >= 3 || Count[DIA1][player] >= 3 || Count[DIA2][player] >= 3)
      return isPlayer1 ? 1 : 2;
   return 0;
}