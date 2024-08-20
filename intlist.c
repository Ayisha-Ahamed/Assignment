// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// intlist.c
// Program on main branch.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <malloc.h>
#include "intlist.h"

//Defines head pointer as NULL and returns a List pointer
List* Create () {
	List* head = malloc (sizeof (List));
	if (head == NULL) {
		return NULL;
	}
	head->head = NULL;
	return head;
}

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

//Adds element at the end of the list
int Add (List* head, int val) {
	//Adds element to an empty list
	struct Node* store = head->head;
	if ((store) == NULL) {
		struct Node* result = malloc (sizeof (struct Node));
		if (result == NULL) {
			return ERROR_MEM;
		}
		result->value = val;
		result->link = NULL;
		head->head = result;//head pointer is updated to element zero
		return FIN;
	}
	while ((store->link) != NULL) {
		store = store->link;
	}
	struct Node* result = malloc (sizeof (struct Node));
	if (result == NULL) {
		return ERROR_MEM;
	}
	result->value = val;
	result->link = NULL; //The current last element of the list
	store->link = result; //The last element of the list is now linked to the new node ie. result
	return FIN;
}

//Deletes the entire list
int Delete (List* head) {
	struct Node* store = head->head;
	if (store == NULL) {
		return ERROR_NO_LIST;
	} else {
		struct Node* temp;
		struct Node* temp2;
		temp = store;
		while (temp != NULL) {
			temp2 = temp->link;
			free (temp);
			temp = temp2;
		}
		temp = NULL;
		head->head = temp;
		return FIN;
	}
}

//Prints the number of elements in the list
int Count (List* head) {
	struct Node* store = head->head;
	int count = 0;
	while (store != NULL) {
		count++;
		store = store->link;
	}
	return count;
}

//Removes an element at zero based index position from the list
int RemoveAt (List* head, int n) {
	int count = 0;
	int lengthOfList = Count (head);
	if ((head->head) == NULL) {
		return ERROR_NO_LIST;
	}
	if ((n < 0) || (n > (lengthOfList - 1))) {
		return ERROR_OUT_OF_BOUNDS;
	}
	//To remove the last element of the list
	if (n == (lengthOfList - 1)) {
		struct Node* temp = head->head;
		struct Node* prev = head->head;
	 //To remove the zero index element when it's the only element in the list
		if (((head->head)->link) == NULL) {
			free (temp);
			head->head = NULL;
			return FIN;
		}
	 //To remove the last element when it's not the only element in the list
		while ((temp->link) != NULL) {
			prev = temp;
			temp = temp->link;
		}
		prev->link = NULL;
		free (temp);
		return FIN;
	}
	//To remove the first element of the list 
	if (n == 0) {
		struct Node* temp;
		temp = head->head;
		head->head = (head->head)->link;//head pointer is updated to the new zeroth element
		free (temp);
		temp = NULL;
		return FIN;
	}
	struct Node* prev = head->head;
	struct Node* temp = head->head;
	while ((temp != NULL) && (count < n)) {
		prev = temp;
		temp = temp->link;
		count++;
	};
	//tempNext points to the next node from the element to be removed 
	struct Node* tempNext;
	if (n == 0) {
		tempNext = NULL;
	} else {
		tempNext = temp->link;
	}
	prev->link = tempNext;//patches the neighbouring elements
	if (temp != NULL)
		free (temp);
	return FIN;
}

//Gets the element from the given index position
int Get (List* head, int n) {
	struct Node* temp = head->head;
	int lengthOfTheList = Count (head);
	int count = 0;
	if ((n < 0) || (n > (lengthOfTheList - 1))) {
		return ERROR_OUT_OF_BOUNDS;
	}
	while ((count < n) && (temp != NULL)) {
		temp = temp->link;
		count++;
	}
	return temp->value;
}

//Removes the first occurence of an element from the list
int Remove (List* head, int n) {
	int count = 0;
	int indexPosition = -1;
	if ((head->head) == NULL) {
		return ERROR_NO_LIST;
	} else {
		struct Node* temp;
		temp = head->head;
		while (temp != NULL) {
			if ((temp->value) == n) {
				indexPosition = count;
				break;
			}
			temp = temp->link;
			count++;
		}
		if (indexPosition != -1) {
			RemoveAt (head, indexPosition);
			return FIN;
		} else {
			return ERROR_INVALID_INPUT;
		}
	}
}

//Inserts element at the given index position
int Insert (List* head, int n, int pos) {
	int count = Count (head);
	if ((pos > count) || (pos < 0)) {
		return ERROR_OUT_OF_BOUNDS;
	}
	struct Node* current = head->head;
	struct Node* prev = head->head;
	struct Node* newNode = malloc (sizeof (struct Node));
	if ((newNode) == NULL) {
		return ERROR_MEM;
	}
	newNode->value = n;
	newNode->link = NULL;
	//For inserting an element at the beginning of the list
	if (pos == 0) {
		newNode->link = head->head;
		head->head = newNode;//Updates head pointer
		return FIN;
	}
	//For inserting an element at the end of the list
	if (pos == count) {
		while ((current->link) != NULL) {
			current = current->link;
		}
		current->link = newNode;
		return FIN;
	}
	for (int i = 0; (i < pos) && (current != NULL); i++) {
		prev = current;
		current = current->link;
	}
	prev->link = newNode;
	newNode->link = current;
	return FIN;
}
// ------------------------------------------------------------------------------------------------
// END
