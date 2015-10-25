//+-----------------------------------------------------------------------------
//
//  File:       replaceSelection.cpp
//
//  Synopsis:   External sorting, problem 1, replacement selection algorithm (heap)
//              http://dsalgo.openjudge.cn/201409week11/1
//
//  Author:     Qirong Ma, 10/24/2015
//
//------------------------------------------------------------------------------
#include <cstdio>

int main() {
	int m, n, i, j, k, temp;
	scanf("%d%d", &m, &n);

	int *file = new int[m];
	int *heap = new int[n];
	for (i = 0; i < m; i++)
		scanf("%d", file+i);
	for (i = 0; i < n; i++)
		scanf("%d", heap+i);

	for (i = 0; i < m && n; i++) {
		printf("%d ", heap[0]);
		if (file[m] < heap[0]) {
			heap[0] = heap[n-1];
			heap[n-1] = file[m];
			n--;
		}
		else {
			heap[0] = file[m];
		}

		// SiftDown(0)
		j = 0;
		temp = heap[0];
		while (2*j+1 < n) {
			k = 2*j+1;
			if (2*j+2 < n && heap[2*j+2] < heap[2*j+1])
				k = 2*j+2;
			if (temp > heap[k]) {
				heap[j] = heap[k];
				j = k;
			}
			else
				break;
		}
		heap[j] = temp;
	}
	printf("\n");

	delete[] file;
	delete[] heap;
}
