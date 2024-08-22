#ifndef INTLIST_H
#define INTLIST_H
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// intlist.h
// Program on Linked List header file.
// -------------------------------------------------------------------------------------------------
/// <summary>
/// Aim : To implement a linked list data structure to handle integer elements.
/// The implementation consists of three files:
///              intlist.h              -             the header file
///              intlist.c              -             the code.
///              testintlist.c          -             the program that tests the implementation.
/// The following functions have been implemented:
/// a)	Create : creates a new linked list.
/// b)	Delete :  deletes all the linked elements.
/// c)	Add :  adds an element to the end of the list.
/// d)	Insert :  inserts an element at a particular index (zero based).
/// e)	RemoveAt : removes the element at a particular index (zero based).
/// f)	Remove : removes the first occurrence of a specific element.
/// g)	Count : returns number of elements in the list.
/// h)	Get : gets the element at a particular index.
/// <\summary>
// --------------------------------------------------------------------------------------------------
#define FIN 0
#define ERROR_MEM -1                  //Memory Allocation Error
#define ERROR_OUT_OF_BOUNDS -2        //Input index position in Insert()/RemoveAt() is Invalid
#define ERROR_NO_LIST -3              //The list is empty
#define ERROR_INVALID_INPUT -4        //The input element in Remove() is invalid

struct Node {
	int value;
	struct Node* link;
};

typedef struct LinkedList {           //Structure to store head pointer
	struct Node* head;
}List;

typedef struct GetError {
	int error;                         //error
	int value;                         //value
}GetType;

/// <summary> Returns a List pointer with its head fixed to null </summary>
List* Create ();

/// <summary> Adds an integer at the end of the list </summary>
int Add (List* head, int val);

/// <summary> Deletes the entire list </summary>
int Delete (List* head);

/// <summary> Returns the number of elements in the list </summary>
int Count (List* head);

/// <summary> Removes the integer at a particular index position </summary>
int RemoveAt (List* head, int n);

/// <summary> Returns the integer at a particular index position </summary>
GetType Get (List* head, int n);

/// <summary> Removes the first occurence of an integer </summary>
int Remove (List* head, int n);

/// <summary> Inserts an integer at a particular index position </summary>
int Insert (List* head, int n, int pos);

#endif INTLIST_H


