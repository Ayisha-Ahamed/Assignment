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

//Defines head pointer and fixes it to null
List Create () {
   struct Node* head ;
   head = NULL;
   return head;
}

//Prints elements of the list starting from the last element that was added to the list
void PrintFunc (List s) {
   List temp = s;
   if (temp != NULL) {
      printf ("\nThe list elements are : \n");
      while (temp != NULL) {
         printf ("%d -> ", temp->value);
         temp = temp->link;
      }
      printf ("\n");
   } else  
      printf ("\nNo elements in the list\n"); 
}

//Adds element at the end of the list
void Add (List* head, int val) {
   //Adds element to an empty list
   if (((*head)) == NULL) {
      struct Node* temp = malloc (sizeof (struct Node));
      temp->value = val;
      temp->link = NULL;
      *head = temp;
      return;
   }
   List result = malloc (sizeof (struct Node));
   result->value = val;
   result->link = *head; //current struct head pointer is linked to the new element
   *head = result;// struct head pointer now points to the added element 
   List store = *head;
   printf ("\n%d is added to the list\n", (*head)->value);
   PrintFunc (store);
   return;
}

//Deletes the entire list
void Delete (List* head) {
   List store = *head;
   if (store == NULL) {
      printf ("\nThere are no elements to delete \n");
      return;
   } else {
      List temp;
      List temp2;
      temp = store;
      while (temp != NULL) {
         printf ("\n%d is deleted from the list\n", temp->value);
         temp2 = temp->link;
         free (temp);
         temp = temp2;
      }
      printf ("\nList deleted... \n");
      *head = NULL;
      return;
   }
}

//Prints the number of elements in the list
void Count (List* head) {
   List store = *head;
   int count = 0;
   while (store != NULL) {
      store = store->link;
      count++;
   }
   printf ("\nThe number of elements in the list is %d\n", count);
}

//Returns the number of elements in the list
int CountNum (List* head) {
   List store = *head;
   int count = 0;
   while (store != NULL) {
      store = store->link;
      count++;
   }
   return count;
}

//Removes the element at a zero based index position from the list
void RemoveAt (List* head, int n) {
   int count = 0;
   int lengthOfList = CountNum (head);
   //Comparision variable that stores the number of times the loop is needed to iterate from the head 
   // to the required zero based index position  
   int cmp = lengthOfList - n - 1;
   if (*head == NULL) {
      printf ("\nThe list is empty \n");
      return;
   }
   if (n < 0) {
      printf ("\nInvalid index \n");
   }
   if (n > (lengthOfList - 1)) {
      printf ("\nThe index exceeds the length of the list (zero based) \n");
      return;
   }
   //To remove the first element of the list
   if (n == 0) {
      List temp = *head;
      List prev = *head;
    //To remove the zero index element when it's the only element in the list
      if (((*head)->link) == NULL) {
         printf ("%d is removed from the list\n", temp->value);
         free (temp);
         *head = NULL;
         return;
      }
    //To remove the first element when it's not the only element in the list
      while ((temp->link) != NULL) {
         prev = temp;
         temp = temp->link;
      }
      printf ("\n%d is removed from the list\n", temp->value);
      prev->link = NULL;
      free (temp);
      PrintFunc (*head);
      return;
   }
   //To remove the last element of the list 
   if (n == (lengthOfList - 1)) {
      List temp;
      temp = *head;
      printf ("\n%d is removed from the list\n", temp->value);
      *head = (*head)->link;
      PrintFunc (*head);
      free (temp);
      temp = NULL;
      return;
   }
   struct Node* prev = *head;
   struct Node* temp = *head;
   while ((temp != NULL) && (count < (cmp))) {
      prev = temp;
      temp = temp->link;
      count++;

   };
   //tempNext points to the next node from the element to be removed 
   List tempNext = NULL;
   if (n == 0) {
      tempNext = NULL;
   } else {
      tempNext = temp->link;
   }
   prev->link = tempNext;
   printf ("\n%d is removed from the list\n", temp->value);
   free (temp);
   PrintFunc (*head);
}

//Gets the element from the given index position
int Get (List* head, int n) {
   int lengthOfTheList = CountNum (head);
   int count = 0;
   int cmp = lengthOfTheList - n - 1;
   struct Node* temp = *head;
   if (n < 0) {
      printf ("\nInvalid index , did you mean n = 0? \n");
      return -1;
   }
   if (n > (lengthOfTheList - 1)) {
      printf ("\nExceeded length of the list \n");
      return -1;
   }
   while ((count < cmp) && (temp != NULL)) {
      temp = temp->link;
      count++;
   }
   printf ("\nThe element at index position %d is %d \n", n, temp->value);
   return temp->value;
}

//Removes the first occurence of an element from the list
void Remove (List* head, int n) {
   int count = (CountNum (head)) - 1;
   int indexPosition = -1;
   if (*head == NULL) {
      printf ("\nThere are no elements to remove \n");
      return;
   } else {
      struct Node* temp;
      temp = *head;
      while (temp != NULL) {
         if ((temp->value) == n) {
            indexPosition = count;
         }
         temp = temp->link;
         count--;
      }
      if (indexPosition != -1) {
         printf ("\nThe earliest occurence of %d is in index position %d \n", n, indexPosition);
         RemoveAt (head, indexPosition);
         return;
      } else {
         printf ("The given element does not exist in the list \n");
         return;
      }
   }
}

//Inserts element at the given index position
void Insert (List* head, int n, int pos) {
   int count = CountNum (head);
   if ((pos > count) || (pos < 0)) {
      printf ("\nInvalid insertion \n");
      return;
   }
   int cmp = count - pos;
   List current = *head;
   List prev = *head;
   List newNode = malloc (sizeof (struct Node));
   newNode->value = n;
   newNode->link = NULL;
   //For inserting an element at the end of the list
   if (pos == count) {
      newNode->link = *head;
      *head = newNode;
      printf ("\n%d is inserted at index position %d\n", (*head)->value, pos);
      PrintFunc (*head);
      return;
   }
   //For inserting an element in zero index position
   if (pos == 0) {
      while ((current->link) != NULL) {
         current = current->link;
      }
      current->link = newNode;
      printf ("\n%d is inserted at index position %d\n", n, pos);
      PrintFunc (*head);
      return;
   }
   for (int i = 0; (i < cmp) && (current != NULL); i++) {
      prev = current;
      current = current->link;
   }
   prev->link = newNode;
   newNode->link = current;
   printf ("\n%d is inserted at index position %d\n", n, pos);
   PrintFunc (*head);
   return;
}
// ------------------------------------------------------------------------------------------------
// END
