// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Coins.c
// Program on branch Test2.2
// Program returns the minimum number of 10, 5, 2 and 1 rupee coins to be handed to the customer.
// ------------------------------------------------------------------------------------------------

#include "Coins.h"

Coins Change (int balance) {
   Coins change = { 0,0,0,0 };
   change.Ten += balance / 10;
   balance %= 10;
   change.Five += balance / 5;
   balance %= 5;
   change.Two += balance / 2;
   balance %= 2;
   change.One = balance;
   return change;
}