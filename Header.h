#pragma once
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Header.h
// Program on branch A5.
// Assignment 5 : Implementation of heap sort and binary search
// ------------------------------------------------------------------------------------------------

///<summary>
/// Heap Sort is a comparison-based sorting algorithm that utilizes a binary heap data structure. 
/// Heap Sort algorithm inserts all elements from an unsorted array into a max heap then swap the 
/// first element (head of the max heap) with the last element. This swap bring the largest element at 
/// the end of the array to its correct position. Then we heapify the first element as swapping has 
/// broken the max heap property. We continue this process until heap size remains one.
/// The functions used for implementing heap sort are: 
/// a) Heapify() : 
/// Constructs the elements of the unsorted array into a max heap by checking if the 
/// child nodes are smaller than the head node. 
/// Consider the example    
///                                        5
///									           /   \
///                                     15   20 
/// The variable 'maximum' stores the index of the largest element of the heap. By default we assume 
/// that maximum = head of the heap and check if the left and right nodes(child nodes) are smaller 
/// than array[maximum]. By the end of Heapify() the heap's head will be 20. 
/// 5 will occupy the position of 20 prior swapping.
///                                       20
///                                      /   \
///                                     15    5 
/// The assumption is that the array is in max heap format(refer HeapSort()). Hence the swapping of 
/// 20 and 5 has now disrupted the max heap that used to have 20 as it's head. This is solved by calling 
/// Heapify() with head at 5. This process is repeated until the heap size is one.
/// b) HeapSort() : 
/// Heapify() can operate only on an array that is in max heap(the subtree under each
/// node contains values less or equal than its root node). The unsorted array is constructed to max 
/// heap by running heapify from the lowest node towards the root of the heap. As heap is a Complete 
/// Binary Tree, the minimum possible height of the tree is O(log(n)). Once heap sort is in max heap, 
/// swap the largest element with the last element of the array, reduce the size of the array by 1 and 
/// run Heapify() on index position 0 to get the second largest element. 	
/// c) Swap() : 
/// Swaps the largest element (head of binary max heap) with the last element of 
/// the unsorted array.
/// </summary>

#define YELLOW "\033[1;33m"        // Color codes
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

/// <summary>Changes the array to max heap format.</summary>
void Heapify (int arr[], int length, int head);

/// <summary>Recursively deletes the max element from max heap.</summary>
void HeapSort (int arr[], int length);

/// <summary>Finds the index position of an element in the sorted array.</summary>
int BinarySearch (int arr[], int high, int num);

/// <summary>Swaps two integers.</summary>
void Swap (int* a, int* b);