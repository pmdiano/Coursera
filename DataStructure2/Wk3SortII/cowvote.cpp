//+-----------------------------------------------------------------------------
//
//  File:       cowvote.cpp
//
//  Synopsis:   Sort II, problem 1
//
//  Author:     Qirong Ma, 10/23/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include "../../include/sort.h"

struct cow {
	int id;
	int vote1;
	int vote2;
	cow(){}
	bool operator< (const cow& c2){return vote1 > c2.vote1;}
	bool operator<=(const cow& c2){return vote1 >= c2.vote1;}
	bool operator>=(const cow& c2){return vote1 <= c2.vote1;}
} R1[50000], R2[50000];

int main() {
	int i, N, K;
	scanf("%d %d", &N, &K);
	for (i = 0; i < N; i++) {
		R1[i].id = i;
		scanf("%d %d", &R1[i].vote1, &R1[i].vote2);
	}
	quickSort(R1, N);

	for (i = 0; i < K; i++) {
		R2[i].id = R1[i].id;
		R2[i].vote1 = R1[i].vote2;
	}
	quickSort(R2, K);
	printf("%d\n", R2[0].id + 1);

	return 0;
}
