// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// intlist.h
// Program on main branch.
// ------------------------------------------------------------------------------------------------

// <summary>
//Aim : To implement a linked list data structure to handle integer elements.
//The implementation consists of three files:
//              intlist.h              -             the header file
//              intlist.c              -             the code.
//              testintlist.c          -             the program that tests the implementation.
//The following functions have been implemented:
//a)	Create : creates a new linked list.
//b)	Delete :  deletes the list and all the linked elements.
//c)	Add :  adds an element to the end of the list.
//d)	Insert :  inserts an element at a particular index (zero based). For example, if the linked list has 4
//elements. Calling Insert with an index of 2 will insert the new element between that at index 1 and that at index 2.
//e)	RemoveAt : removes the element at a particular index (zero based, in the order of inputs by the user).
//f)	Remove : removes the first occurrence of a specific element.
//g)	Count : returns number of elements in the list.
//h)	Get : gets the element at a particular index.
//<\summary>

#ifndef INTLIST_H
#define INTLIST_H

struct Node {
	int value;
	struct Node* link;
};

typedef struct Node* List;

struct Node* Create ();
void Add (List*, int val);
void PrintFunc (List);
void Delete (List* head);
void Count (List* head);
void RemoveAt (List* head, int n);
int Get (List* head, int n);
void Remove (List* head, int n);
void Insert (List* head, int n, int pos);

#endif INTLIST_H


