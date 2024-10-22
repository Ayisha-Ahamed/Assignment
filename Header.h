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
#define YELLOW "\033[1;33m"        // Color codes
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

/// <summary>Changes the array to max heap format.</summary>
void Heapify (int arr[], int length, int head);

/// <summary>Recursively deletes the max element from max heap.</summary>
void HeapSort (int arr[], int length);

/// <summary>Finds the index position of an element in the sorted array.</summary>
int BinarySearch (int arr[], int high, int num);

/// <summary>Swaps two integers.</summary>
void Swap (int* a, int* b);