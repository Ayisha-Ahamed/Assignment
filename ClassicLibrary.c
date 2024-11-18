// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch A5.
// Program that contains the definiton of functions defined in Header.h.
// ------------------------------------------------------------------------------------------------

// Heap Sort inserts elements from an unsorted array into a max heap.A Max Heap is a complete 
// binary tree,where value of each node is greater than or equal to the values of its children. 
// The same property must be recursively true for all nodes in the binary tree i.e Max Heap stores 
// the maximum value at the root of the heap. An array is first constructed to form a max heap, 
// then the root of the max heap is swapped with the last element of the unsorted array recursively.
// This swap breaks the max heap property so we "heapify" it again. 
// We continue until heap size becomes one.


/// <summary>
/// Swaps the largest element (root of max heap) with the last element of the unsorted array
/// </summary>
void Swap (int* a, int* b) {
   if (*a != *b) {
      *a = *a + *b;
      *b = *a - *b;
      *a = *a - *b;
   }
}
/// <summary>
/// Checks the max-heap property by recursively comparing a node with its children and swapping 
/// if necessary. It continues this process until the subtree rooted at the node is a valid max-heap
/// </summary>
void Heapify (int arr[], int length, int head) {
   int maximum = head, left = 2 * head + 1, right = 2 * head + 2;
   if (left < length && arr[left] > arr[maximum]) maximum = left;
   if (right < length && arr[right] > arr[maximum]) maximum = right;
   if (maximum != head) {
      Swap (&arr[head], &arr[maximum]);
      Heapify (arr, length, maximum);
   }
}

/// <summary>
/// Constructs the array into a max heap and recursively swaps the root with the last position of 
/// the unsorted array
/// </summary>
void HeapSort (int arr[], int length) {
   // The unsorted array is constructed to max heap by running heapify from the lowest node towards 
   // the root of the heap. Number of nodes is of order O(log n).
   for (int start = length / 2 - 1; start >= 0; start--) Heapify (arr, length, start);
   for (int len = length - 1; len > 0; len--) {
      // Swap the root of the heap with the last element of the array.
      Swap (&arr[0], &arr[len]);
      // Heapify the zeroth index since the swap disrupted the max heap property.
      Heapify (arr, len, 0);
   }
}

int BinarySearch (int arr[], int high, int num) {
   int index = -1, low = 0;
   while (low <= high) {
      int mid = low + (high - low) / 2;
      if (num == arr[mid]) {
         index = mid;
         high = mid - 1;
      } else if (arr[mid] > num) high = mid - 1;
      else low = mid + 1;
   }
   return index;
};