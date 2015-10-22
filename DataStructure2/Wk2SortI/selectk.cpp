//+-----------------------------------------------------------------------------
//
//  File:       selectk.cpp
//
//  Synopsis:   Sort I, problem 2
//              https://www.coursera.org/learn/gaoji-shuju-jiegou/programming/
//               dYX9U/bian-cheng-zuo-ye-nei-pai-xu-shang-3ti
//
//  Author:     Qirong Ma, 10/22/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include "../../include/sort.h"

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	int *data = new int[n];
	for (int i = 0; i < n; i++)
		scanf("%d", data+i);

	heapSort(data, n);
	printf("%d\n", data[n-k]);
	
	delete[] data;
	return 0;
}
