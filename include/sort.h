//+-----------------------------------------------------------------------------
//
//  File:       sort.h
//
//  Synopsis:   Basic sorting algorithms
//
//  Author:     Qirong Ma, 10/22/2015
//
//------------------------------------------------------------------------------
#pragma once
#include "minheap.h"

template<class T>
inline void _swap(T& v1, T& v2) {
	T temp = v1;
	v1 = v2;
	v2 = temp;
}

// Assuming data is non-increasingly sorted
// Return: one index where data[index] equal to val, -1 if not found
template<class T>
int binarySearch(T* data, int n, const T& val) {
	int l, r, mid;
	l = 0, r = n-1, mid = (l+r)/2;
	while (l <= r) {
		if (val == data[mid])
			return mid;
		else if (val < data[mid]) {
			r = mid-1;
			mid = (l+r)/2;
		}
		else {
			l = mid+1;
			mid = (l+r)/2;
		}
	}
	return -1;
}

// Stable
template<class T>
void insertionSort(T* data, int n) {
	for (int i = 1; i < n; i++) {
		T temp = data[i];
		int j = i-1;
		while (j >= 0 && temp < data[j]) {
			data[j+1] = data[j];
			j--;
		}
		data[j+1] = temp;
	}
}

// Non-stable
template<class T>
void selectionSort(T* data, int n) {
	for (int i = 0; i < n-1; i++) {
		int smallest = i;
		for (int j = i+1; j < n; j++)
			if (data[j] < data[smallest])
				smallest = j;
		_swap(data[i], data[smallest]);
	}
}

// Stable
template<class T>
void bubbleSort(T* data, int n) {
	for (int i = 0; i < n-1; i++)
		for (int j = n-1; j > i; j--)
			if (data[j] < data[j-1])
				_swap(data[j], data[j-1]);
}

template<class T>
int partition(T* data, int n) {
	int pivot = n/2;
	_swap(data[pivot], data[n-1]);
	T temp = data[n-1];
	int l = 0, r = n-1;
	while (l < r) {
		while (l < r && data[l] <= temp)
			l++;
		if (l < r)
			data[r--] = data[l];
		while (l < r && data[r] >= temp)
			r--;
		if (l < r)
			data[l++] = data[r];
	}
	data[l] = temp;
	return l;
}

// Non-stable
template<class T>
void quickSort(T* data, int n) {
	if (n <= 1) return;
	int pivot = partition(data, n);
	quickSort(data, pivot);
	quickSort(data+pivot+1, n-pivot-1);
}

// From large to small
template<class T>
void heapSort(T* data, int n) {
	MinHeap<T> heap(data, n);
	for (int i = 0; i < n-1; i++)
		(void)heap.RemoveMin();
}
