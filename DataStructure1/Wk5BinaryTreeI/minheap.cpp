//+-----------------------------------------------------------------------------
//
//  File:       minheap.cpp
//
//  Synopsis:   Using minheap as a priority queue
//              https://www.coursera.org/learn/shuju-jiegou-suanfa/programming
//                /BMRWH/bian-cheng-zuo-ye-er-cha-shu-ji-chu-3ti
//
//  Author:     Qirong Ma, 10/12/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include "../../include/minheap.h"

int main() {
	int t, n, type, node;
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		MinHeap<int> heap(n);

		while (n--) {
			scanf("%d", &type);
			if (type == 1) {
				scanf("%d", &node);
				heap.Insert(node);
			}
			else if (type == 2) {
				heap.Remove(0, node);
				printf("%d\n", node);
			}
		}
	}

	return 0;
}
