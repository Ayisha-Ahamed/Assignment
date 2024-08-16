// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// testintlist.c
// Program on main branch.
// ------------------------------------------------------------------------------------------------

#include "intlist.h"


int main () {
   struct node* head = Create ();
   struct node* head2 = Create ();
   Add (&head, 3);
   Add (&head, 4);
   Add (&head2, 6);
   Add (&head2, 4);
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
   Get (&head, 1);
}
