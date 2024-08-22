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
	} 
	else printf ("No elements in the list\n");
}

void ReturnFunc (int k) {
	if (k == -1)printf ("Memory allocation error\n");
	else if (k == -2)printf ("The given index position is invalid\n");
	else if (k == -3)printf ("List is empty\n");
	else if (k == -4)printf ("The input is invalid\n");
	else printf ("The output is %d\n", k);     //Could be count or get
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
	printf ("From Get func : %d\n", num);
	ReturnFunc (num);
	num = Count (head);
	printf ("From Count func : %d\n", num);
	ReturnFunc (num);
	num = Remove (head, 7); 	    //Invalid Input
	printf ("From Remove func : %d\n", num);
	ReturnFunc (num);
	Delete (head2);                //Deletes head 2
	num = Remove (head2, 2);       //Operation on empty list
	ReturnFunc (num);              //Returns list is empty
	PrintFunc (head);
	RemoveAt (head, 1);
	PrintFunc (head);
	Insert (head2, 13, 0);
	PrintFunc (head2);
}
