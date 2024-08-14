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


struct node {
   int value;
   struct node* link;
};
//Defines head pointer and fixes it to null
struct node* Create () {
   struct node* head = malloc (sizeof (struct node));
   printf ("An empty linked list is created \n");
   head = NULL;
   return head;
}

//-------------------------------------------------------------------------------------------------
//Prints elements of the list starting from the last element that was added to the list
void PrintFunc (struct node* s) {
   struct node* temp = s;
   if (temp != NULL) {
      printf ("The list elements are : \n");
      while (temp != NULL) {
         printf ("%d -> ", temp->value);
         temp = temp->link;
      }
      printf ("\n");
   } else { printf ("No elements in the list\n"); }
}

// ------------------------------------------------------------------------------------------------
//Adds element at the end of the list
void Add (struct node** head, int val) {
   //Adds element to an empty list
   if (head == NULL) {
      struct node* temp = malloc (sizeof (struct node));
      temp->value = val;
      temp->link = NULL;
      *head = temp;
   }
   struct node* result = malloc (sizeof (struct node));
   result->value = val;
   result->link = *head; //current struct head pointer is linked to the new element
   *head = result;// struct head pointer now points to the added element 
   struct node* store = *head;
   printf ("%d is added to the list\n", (*head)->value);
   PrintFunc (store);
   return;
}

// ------------------------------------------------------------------------------------------------
//Deletes the entire list
void Delete (struct node** head) {
   struct node* store = *head;
   if (store == NULL) {
      printf ("There are no elements to delete \n");
      return;
   } else {
      struct node* temp;
      struct node* temp2;
      temp = store;
      while (temp != NULL) {
         printf ("%d is deleted from the list\n", temp->value);
         temp2 = temp->link;
         free (temp);
         temp = NULL;
         temp = temp2;
      }
      printf ("List deleted... \n");
      *head = NULL;
      return;
   }
}

//-------------------------------------------------------------------------------------------------
//Prints the number of elements in the list
void Count(struct node** head) {
   struct node* store = *head;
   int count = 0;
   while (store != NULL) {
      store = store->link;
      count++;
   }
   printf ("The number of elements in the list is %d\n", count);
}

// ------------------------------------------------------------------------------------------------
//Returns the number of elements in the list
int CountNum (struct node** head) {
   struct node* store = *head;
   int count = 0;
   while (store != NULL) {
      store = store->link;
      count++;
   }
   return count;
}

// ------------------------------------------------------------------------------------------------
//Removes the element at a zero based index position from the list
void RemoveAt (struct node** head, int n) {
   int count = 0;
   int lengthOfList = CountNum (head);
   //Comparision variable that stores the number of times the loop is needed to iterate from the head 
   // to the required zero based index position  
   int cmp = lengthOfList - n - 1;
   if (*head == NULL) {
      printf ("The list is empty \n");
      return;
   }
   if (n < 0) {
      printf ("Invalid index \n");
   }
   if (n > (lengthOfList - 1)) {
      printf ("The index exceeds the length of the list (zero based) \n");
      return;
   }
//To remove the first element of the list
   if (n == 0) {
      struct node* temp = *head;
      struct node* prev = *head;
    //To remove the zero index element when it's the only element in the list
      if (((*head)->link) == NULL) { 
         printf ("%d is removed from the list\n",temp->value );
         free (temp);
         *head = NULL;  
         return;
      }
    //To remove the first element when it's not the only element in the list
      while ((temp->link) != NULL) {
         prev = temp;
         temp = temp->link;
      }
      printf ("%d is removed from the list\n", temp->value);
      prev->link = NULL;
      free (temp);
      PrintFunc (*head);
      return;
   }
   //To remove the last element of the list 
   if (n == (lengthOfList - 1)) {
      struct node* temp;
      temp = *head;
      printf ("%d is removed from the list\n", temp->value);
      *head = (*head)->link;
      PrintFunc (*head);
      free (temp);
      temp = NULL;
      return;
   }
   struct node* prev = *head;
   struct node* temp = *head;
   while ((temp != NULL) && (count < (cmp))) {
      prev = temp;
      temp = temp->link;
      count++;

   };
   //tempNext points to the next node from the element to be removed 
   struct node* tempNext = NULL;
   if (n == 0) {
      tempNext = NULL;
   } else {
      tempNext = temp->link;
   }
   prev->link = tempNext;
   printf ("%d is removed from the list\n", temp->value);
   free (temp);
   PrintFunc (*head);
}
// ------------------------------------------------------------------------------------------------
//Gets the element from the given index position
void Get (struct node** head, int n) {
   int lengthOfTheList = CountNum (head);
   int count = 0;
   int cmp = lengthOfTheList - n - 1;
   struct node* temp = *head;
   if (n < 0) {
      printf ("Invalid index , did you mean n = 0? \n");
      return;
   }
   if (n > (lengthOfTheList - 1)) {
      printf ("Exceeded length of the list \n");
      return;
   }
   while ((count < cmp) && (temp != NULL)) {
      temp = temp->link;
      count++;
   }
   printf ("The element at index position %d is %d \n", n, temp->value);
}
// ------------------------------------------------------------------------------------------------
//Removes the first occurence of an element from the list
void Remove (struct node** head, int n) {
   int count = (CountNum (head)) - 1;
   int indexPosition = -1;
   if (*head == NULL) {
      printf ("There are no elements to remove \n");
      return;
   }
   else {
      struct node* temp;
      temp = *head;
      while (temp != NULL) {
         if ((temp->value) == n) {
            indexPosition = count;
         }
         temp = temp->link;
         count--;
      }
      if (indexPosition != -1) {
         printf ("The earliest occurence of %d is in index position %d \n", n, indexPosition);
         RemoveAt (head,indexPosition); 
         return;
      } else {
         printf ("The given element does not exist in the list \n");
         return;
      }
   }
}
// ------------------------------------------------------------------------------------------------
//Inserts element at the given index position
void Insert (struct node** head, int n, int pos) {
   int count = CountNum (head);
   int cmp = count - pos;
   struct node* current = *head;
   struct node* prev = *head;
   struct node* newNode = malloc (sizeof (struct node));
   newNode->value = n;
   newNode->link = NULL;
   if ((pos > count) || (pos < 0)) {
      printf ("Invalid insertion \n");
      return;
   }
   //For inserting an element at the end of the list
   if (pos == count) {
      newNode->link = *head;
      *head = newNode;
      printf ("%d is inserted at index position %d\n", (*head)->value, pos);
      PrintFunc (*head);
      return;
   }
   //For inserting an element in zero index position
   if (pos == 0) {
      while ((current->link) != NULL) {
         current = current->link;
      }
      current->link = newNode;
      printf ("%d is inserted at index position %d\n", n, pos);
      PrintFunc (*head);
      return;
   }
   for (int i = 0; (i < cmp) && (current != NULL); i++) {
      prev = current;
      current = current->link;
   }
   printf ("Prev value = %d\n", prev->value);
   printf ("Current value = %d\n", current->value);
   prev->link = newNode;
   newNode->link = current;
   printf ("%d is inserted at index position %d\n", n, pos);
   PrintFunc (*head);
   return;
}

// ------------------------------------------------------------------------------------------------
// END
