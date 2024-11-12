// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// ClassicLibrary.c
// Program on branch A5.
// Program that contains the definiton of functions defined in Header.h.
// ------------------------------------------------------------------------------------------------

void Swap (int* a, int* b) {
   if (*a != *b) {
      *a = *a + *b;
      *b = *a - *b;
      *a = *a - *b;
   }
}

void Heapify (int arr[], int length, int head) {
   int maximum = head, left = 2 * head + 1, right = 2 * head + 2;
   if (left < length && arr[left] > arr[maximum]) maximum = left;
   if (right < length && arr[right] > arr[maximum]) maximum = right;
   if (maximum != head) {
      Swap (&arr[head], &arr[maximum]);
      Heapify (arr, length, maximum);
   }
}

void HeapSort (int arr[], int length) {
   // Construct the unsorted array to form a Max-Heap
   for (int start = length / 2 - 1; start >= 0; start--) Heapify (arr, length, start);
   for (int len = length - 1; len > 0; len--) {
      Swap (&arr[0], &arr[len]);
      Heapify (arr, len, 0);      // Change the array to max heap again
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