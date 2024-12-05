#ifndef COINS_H
#define COINS_H
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Coins.h
// Program on branch Test 2.2
// Program returns the minimum number of 10, 5, 2 and 1 rupee coins to be handed to the customer
// ------------------------------------------------------------------------------------------------

typedef struct {
   int Ten;
   int Five;
   int Two;
   int One;
}Coins;

/// <summary>Returns the minimum number of coins to be handed to the customer.</summary>
Coins Change (int balance);

#endif COINS_H