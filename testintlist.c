// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// testintlist.c
// Program on Linked List testing.
// ------------------------------------------------------------------------------------------------

#include "intlist.h"
#include <stdio.h>

//Prints the elements of the list 
void PrintFunc (List* s) {
	struct Node* temp = s->head;
	if (temp != NULL) {
		printf ("The list elements are : \n");
		while (temp != NULL) {
			printf ("%d -> ", temp->value);
			temp = temp->link;
		}
		printf ("\n");
	} else printf ("No elements in the list\n");
}

//Prints Return value
void PrintReturn (int k) {
	if (k == -1)printf ("Memory allocation error\n");
	else if (k == -2)printf ("The given index position is invalid\n");
	else if (k == -3)printf ("List is empty\n");
	else if (k == -4)printf ("The input is invalid\n");
	else printf ("The output is %d\n", k);
}

void PrintCount (int k) {
	printf ("The length of the list is %d\n", k);
}

//Prints the value returned by Get() function
void PrintGet (GetType k) {
	if (k.error == 0)
		printf ("The integer returned by Get() is %d \n", k.value);
	else {
		PrintReturn (k.value);
	}
}

int main () {
	List* head = Create ();

	//Adding integers to head 
	Add (head, -1);
	Add (head, -2);
	Add (head, -3);
	Add (head, -4);

	//Prints head
	PrintFunc (head);

	//Prints the length of the list 'head'
	PrintCount (Count (head));

	//Prints the integer/Error Code returned by Get()
	PrintGet (Get (head, 1));
	PrintGet (Get (head, 7));

	//Inserts -2 at index position 4
	Insert (head, -2, 4);
	PrintFunc (head);

	//Removes the first occurence of -2
	Remove (head, -2);
	PrintFunc (head);
	PrintCount (Count (head));

	//Removes the integer at index position 2
	RemoveAt (head, 2);
	PrintFunc (head);
	PrintCount (Count (head));

	//Deletes the entire list
	Delete (head);
	PrintFunc (head);
	PrintCount (Count (head));



}

