// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch Test2.
// Program that contains the definiton of functions defined in Header.h.
// ------------------------------------------------------------------------------------------------
#include "Header.h"

Coin Change (int cost, int money) {
   Coin change = { 0,0,0,0 };
   int bal = money - cost;
   if (bal >= 10) {
      change.Ten += bal / 10;
      bal -= 10 * change.Ten;
   }
   if (bal >= 5) {
      change.Five += bal / 5;
      bal -= 5 * change.Five;
   }
   if (bal >= 2) {
      change.Two += bal / 2;
      bal -= 2 * change.Two;
   }
   change.One = bal;

   return change;
}