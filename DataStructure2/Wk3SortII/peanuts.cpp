//+-----------------------------------------------------------------------------
//
//  File:       peanuts.cpp
//
//  Synopsis:   Sort II, problem 2. Also POJ 1928
//
//  Author:     Qirong Ma, 10/23/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include "../../include/sort.h"

inline int abs(int x) {
	return x > 0 ? x : -x;
}

struct peanut {
	int i;
	int j;
	int num;
	peanut(){}
	bool operator<(const peanut& p2) const {return num > p2.num;}
	bool operator>=(const peanut& p2) const {return num <= p2.num;}
	bool operator<=(const peanut& p2) const {return num >= p2.num;}
} field[2500];
int cost[2500], count[2500];

int solve() {
	int M, N, K, l, i, j;
	scanf("%d%d%d", &M, &N, &K);
	for (i = 1, l=0; i <= M; i++)
		for (j = 1; j <= N; j++) {
			scanf("%d", &field[l].num);
			field[l].i = i;
			field[l].j = j;
			l++;
		}

	quickSort(field, l);
	cost[0] = 1 + (field[0].i-1) + 1;
	count[0] = field[0].num;
	for (i = 1; i < l; i++) {
		cost[i] = cost[i-1] + 1
					+ abs(field[i].i - field[i-1].i)
					+ abs(field[i].j - field[i-1].j);
		count[i] = count[i-1] + field[i].num;
	}
	for (i = 0; i < l; i++)
		cost[i] = cost[i] + (field[i].i - 1)  + 1;

	// for (i = 0; i < l; i++)
	// 	printf("count[%d]=%d, cost[%d]=%d\n", i, count[i], i, cost[i]);

	int left, right, mid;
	left = 0; right = l-1;
	while (left <= right) {
		mid = (left+right)/2;
		if (K == cost[mid])
			return count[mid];
		else if (K < cost[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return count[right];
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		printf("%d\n", solve());
	return 0;
}
