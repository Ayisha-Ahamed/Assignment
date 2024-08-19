// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// testintlist.c
// Program on main branch.
// ------------------------------------------------------------------------------------------------

#include "intlist.h"


int main () {
   List head = Create ();
   List head2 = Create ();
   int k;
   Add (&head, 3);
   Add (&head, 3);
   Add (&head, 4);
   Add (&head2, 6);
   Add (&head2, 4);
   k = Get (&head, 1);
   printf ("From get func : %d\n", k);
   Delete (&head);
   Delete (&head2);
   Insert (&head, 2, 0);
   Add (&head, 4);
   Insert (&head, 6, 2);
   Count (&head);
   Remove (&head, 6);
   RemoveAt (&head, 0);
   Remove (&head, 4);
   Count (&head);
}
