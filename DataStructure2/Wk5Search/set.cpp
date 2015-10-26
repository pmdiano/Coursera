//+-----------------------------------------------------------------------------
//
//  File:       set.cpp
//
//  Synopsis:   Weird problem
//              https://www.coursera.org/learn/gaoji-shuju-jiegou/programming
//               /IfU8I/bian-cheng-zuo-ye-jian-suo-3ti
//
//  Author:     Qirong Ma, 10/25/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>

int n, m;
int A[1000000];
int B[1000000];

int main() {
	int i, ia = 0, ib = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", A+i);
	scanf("%d", &m);
	for (i = 0; i < m; i++)
		scanf("%d", B+i);

	while (ia < n && ib < m) {
		if (A[ia] == B[ib]) {
			ia++;
			ib++;
		}
		while (ia < n && ib < m && A[ia] < B[ib])
			printf("%d ", A[ia++]);
		while (ia < n && ib < m && B[ib] < A[ia])
			printf("%d ", B[ib++]);
	}
	while (ia < n)
		printf("%d ", A[ia++]);
	while (ib < m)
		printf("%d ", B[ib++]);
	printf("\n");

	return 0;
}
