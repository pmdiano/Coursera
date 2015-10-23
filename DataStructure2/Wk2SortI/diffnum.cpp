//+-----------------------------------------------------------------------------
//
//  File:       diffnum.cpp
//
//  Synopsis:   Sort I, problem 3
//              https://www.coursera.org/learn/gaoji-shuju-jiegou/programming/
//               dYX9U/bian-cheng-zuo-ye-nei-pai-xu-shang-3ti
//
//  Author:     Qirong Ma, 10/22/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include "../../include/sort.h"

int main() {
	int N, T, last, ans=0, i;
	scanf("%d%d", &N, &T);
	int *A = new int[N];
	for (i = 0; i < N; i++)
		scanf("%d", A+i);

	quickSort(A, N);
	last = A[0]-1, i = 0;
	while (i < N) {
		while (last == A[i])
			i++;
		last = A[i];

		// Special case if the difference is 0 and there is only one T[i]
		if (!((T == 0 && i == N-1) || (T == 0 && i < N-1 && A[i+1] != A[i])))
			if (binarySearch(A, N, A[i]+T) != -1)
				ans++;

		i++;
	}
	printf("%d\n", ans);

	delete[] A;
	return 0;
}
