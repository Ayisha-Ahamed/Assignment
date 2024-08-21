// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// testintlist.c
// Program on Linked List testing.
// ------------------------------------------------------------------------------------------------

#include "intlist.h"
#include <stdio.h>

//Prints elements of the list 
void PrintFunc (List* s) {
	struct Node* temp = s->head;
	if (temp != NULL) {
		printf ("The list elements are : \n");
		while (temp != NULL) {
			printf ("%d -> ", temp->value);
			temp = temp->link;
		}
		printf ("\n");
	} else
		printf ("No elements in the list\n");
}

int main () {
	List* head = Create ();
	List* head2 = Create ();
	int num;
	Add (head, 1);
	Add (head, 2);
	Add (head, 3);
	Add (head, 4);
	PrintFunc (head);
	Add (head2, 11);
	Add (head2, 12);
	PrintFunc (head2);
	num = Get (head, 0);
	printf ("From get func : %d\n", num);
	num = Count (head);
	printf ("From count func : %d\n", num);
	Remove (head, 4);
	PrintFunc (head);
	RemoveAt (head, 1);
	PrintFunc (head);
	Insert (head2, 13, 2);
	PrintFunc (head2);


}
