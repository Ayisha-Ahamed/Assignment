// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// intlist.c
// Program on Linked List function definitions.
// ------------------------------------------------------------------------------------------------

#include <malloc.h>
#include "intlist.h"

List* Create () {
	List* head = malloc (sizeof (List));
	if (head == NULL) return NULL;
	head->head = NULL;
	return head;
}

int Add (List* head, int val) {
	struct Node* store = head->head;
	if ((store) == NULL) {                      //Adds element to an empty list
		struct Node* result = malloc (sizeof (struct Node));
		if (result == NULL) return ERROR_MEM;
		result->value = val;
		result->link = NULL;
		head->head = result;                     //head pointer is updated to the new integer at zero index
		return FIN;
	}
	while ((store->link) != NULL) store = store->link;
	struct Node* result = malloc (sizeof (struct Node));
	if (result == NULL) return ERROR_MEM;
	result->value = val;
	result->link = NULL;
	store->link = result;                       //The last element of the list is now linked to the new node ie. result
	return FIN;
}

int Delete (List* head) {
	struct Node* store = head->head;
	if (store == NULL) return ERROR_NO_LIST;                                            //List is empty
	else {
		struct Node* temp;
		struct Node* temp2;
		temp = store;
		while (temp != NULL) {
			temp2 = temp->link;
			free (temp);
			temp = temp2;
		}
		temp = NULL;
		head->head = NULL;
		return FIN;
	}
}

int Count (List* head) {
	struct Node* store = head->head;
	int count = 0;                             //Default value set to zero ie. empty list
	while (store != NULL) {
		count++;
		store = store->link;
	}
	return count;
}

int RemoveAt (List* head, int n) {
	int count = 0;
	int lengthOfList = Count (head);
	if ((head->head) == NULL) return ERROR_NO_LIST;
	if ((n < 0) || (n > (lengthOfList - 1))) return ERROR_OUT_OF_BOUNDS;
	if (n == (lengthOfList - 1)) {            //To remove the last element of the list
		struct Node* temp = head->head;
		struct Node* prev = head->head;
		if (((head->head)->link) == NULL) {    //To remove the zero index element when it's the only element in the list
			free (temp);
			head->head = NULL;
			return FIN;
		}
		while ((temp->link) != NULL) {         //To remove the last element when it's not the only element in the list
			prev = temp;
			temp = temp->link;
		}
		prev->link = NULL;
		free (temp);
		return FIN;
	}
	if (n == 0) {                             //To remove the first element of the list 
		struct Node* temp;
		temp = head->head;
		head->head = (head->head)->link;       //head pointer is updated to the new zero index integer
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
	struct Node* tempNext;                    //tempNext points to the next node from the element to be removed 
	if (n == 0) tempNext = NULL;
	else
		if (temp != NULL) tempNext = temp->link;
		else tempNext = NULL;
	prev->link = tempNext;                    //patches the neighbouring elements
	if (temp != NULL) free (temp);
	return FIN;
}

int Get (List* head, int n) {
	struct Node* temp = head->head;
	int lengthOfTheList = Count (head);
	int count = 0;
	if ((n < 0) || (n > (lengthOfTheList - 1))) return ERROR_OUT_OF_BOUNDS;              //invalid index position
	while ((count < n) && (temp != NULL)) {
		temp = temp->link;
		count++;
	}
	if (temp != NULL) return temp->value;
	else return NULL;
}

int Remove (List* head, int n) {
	int count = 0;
	int indexPosition = -1;                   //Default value is set to -1 to indicate if the given integer exists in the list
	if ((head->head) == NULL) return ERROR_NO_LIST;
	else {
		struct Node* temp;
		temp = head->head;
		while (temp != NULL) {
			if ((temp->value) == n) {
				indexPosition = count;           //Gets the index position of the first occurence of the integer in the list
				break;
			}
			temp = temp->link;
			count++;
		}
		if (indexPosition != -1) {
			RemoveAt (head, indexPosition);
			return FIN;
		} else return ERROR_INVALID_INPUT;       //Given integer does not exist in the list
	}
}

int Insert (List* head, int n, int pos) {
	int count = Count (head);
	if ((pos > count) || (pos < 0)) return ERROR_OUT_OF_BOUNDS;
	struct Node* current = head->head;
	struct Node* prev = head->head;
	struct Node* newNode = malloc (sizeof (struct Node));
	if ((newNode) == NULL) return ERROR_MEM;
	newNode->value = n;
	newNode->link = NULL;
	if (pos == 0) {                          //For inserting an element at the beginning of the list
		newNode->link = head->head;
		head->head = newNode;                 //Updates head pointer
		return FIN;
	}
	if (pos == count) {                      //For inserting an element at the end of the list
		while ((current->link) != NULL) current = current->link;
		current->link = newNode;
		return FIN;
	}
	for (int i = 0; (i < pos) && (current != NULL); i++) {
		prev = current;
		current = current->link;
	}
	if (prev != NULL) prev->link = newNode;
	newNode->link = current;
	return FIN;
}
// ------------------------------------------------------------------------------------------------
// END
