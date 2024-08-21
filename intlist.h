// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// intlist.h
// Program on Linked List header file.
// -------------------------------------------------------------------------------------------------
// <summary>
// Aim : To implement a linked list data structure to handle integer elements.
// The implementation consists of three files:
//              intlist.h              -             the header file
//              intlist.c              -             the code.
//              testintlist.c          -             the program that tests the implementation.
// The following functions have been implemented:
// a)	Create : creates a new linked list.
// b)	Delete :  deletes all the linked elements.
// c)	Add :  adds an element to the end of the list.
// d)	Insert :  inserts an element at a particular index (zero based).
// e)	RemoveAt : removes the element at a particular index (zero based).
// f)	Remove : removes the first occurrence of a specific element.
// g)	Count : returns number of elements in the list.
// h)	Get : gets the element at a particular index.
// <\summary>
// --------------------------------------------------------------------------------------------------

#ifndef INTLIST_H
#define INTLIST_H
#define FIN 0
#define ERROR_MEM -1                  //Memory Allocation Error
#define ERROR_OUT_OF_BOUNDS -2        //Input index position in Insert()/RemoveAt() is Invalid
#define ERROR_NO_LIST -3              //The list is empty
#define ERROR_INVALID_INPUT -4        //The input element in Remove() is invalid

struct Node {
	int value;
	struct Node* link;
};

typedef struct LinkedList {
	struct Node* head;
}List;

List* Create ();
int Add (List* head, int val);
int Delete (List* head);
int Count (List* head);
int RemoveAt (List* head, int n);
int Get (List* head, int n);
int Remove (List* head, int n);
int Insert (List* head, int n, int pos);

#endif INTLIST_H


