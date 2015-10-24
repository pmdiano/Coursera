//+-----------------------------------------------------------------------------
//
//  File:       dna.cpp
//
//  Synopsis:   Sort II, problem 3. Should use index sorting.
//
//  Author:     Qirong Ma, 10/23/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include "../../include/sort.h"

int n, m;
char seq[100][51];

struct elem {
	int id;
	int inv;
	bool operator<(const elem& e) {return inv < e.inv;}
} data[100], temp[100];

int getInv(char* dna) {
	int ans = 0;
	for (int i = 0; i < n-1; i++) {
		if (dna[i] == 'A') continue;
		for (int j = i+1; j < n; j++)
			if (dna[i] > dna[j])
				ans++;
	}
	return ans;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%s", seq[i]);
		data[i].id = i;
		data[i].inv = getInv(seq[i]);
	}

	mergeSort(data, temp, m);
	for (int i = 0; i < m; i++) {
		printf("%s\n", seq[data[i].id]);
	}
}
