//+-----------------------------------------------------------------------------
//
//  File:       loserTree.cpp
//
//  Synopsis:   External sorting, problem 2, loser tree algorithm
//              http://dsalgo.openjudge.cn/201409week11/2
//
//  Author:     Qirong Ma, 10/25/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cassert>

int n, treeSize, lowExt;
int *tree, *data;

int getMsb(int n) {
	int b = 0;
	while (n >>= 1)
		b++;
	return b;
}

void _swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void build(int p, int winner) {
	while (true) {
		assert(p >= 0);
		if (tree[p] <= 0 || p == 0) {
			tree[p] = winner;
			break;
		}
		if (data[tree[p]] < data[winner])
			_swap(tree[p], winner);
		p /= 2;
	}
}

void leftBuild(int i) {
	assert(i % 2 == 0 && i+1 < lowExt);

	int p = (i+treeSize) / 2;
	int winner, loser;

	if (data[i] < data[i+1]) {
		winner = i;
		loser = i+1;
	}
	else {
		winner = i+1;
		loser = i;
	}
	tree[p] = loser;
	p /= 2;

	build(p, winner);	
}

void middleBuild(int i) {
	assert(n % 2 && i == lowExt);
	int p = (i - lowExt/2 + treeSize/2) / 2;
	build(p, i);
}

void rightBuild(int i) {
	int p = (i - lowExt/2 + treeSize/2) / 2;
	int winner, loser;
	if (data[i] < data[i+1]) {
		winner = i;
		loser = i+1;
	}
	else {
		winner = i+1;
		loser = i;
	}
	tree[p] = loser;
	p /= 2;
	build(p, winner);
}

void print() {
	for (int i = 0; i < n; i++)
		printf("%d ", data[tree[i]]);
	printf("\n");
}

int main() {
	int msb, i, m, id, p, d;
	scanf("%d%d", &n, &m);

	tree = new int[n];
	data = new int[n];

	msb = getMsb(n);
	if (1 << msb == n) {
		treeSize = n;
		lowExt = n;
	}
	else {
		treeSize = 1 << (msb+1);
		lowExt = n - (treeSize - n);
	}

	for (i = 0; i < n; i++) {
		scanf("%d", data+i);
		tree[i] = -1;
	}

	for (i = 0; i < lowExt; i+=2) {
		leftBuild(i);
	}
	if (n % 2)
		middleBuild(i++);
	for (; i < n; i+=2) {
		rightBuild(i);
	}

	print();

	for (i = 0; i < m; i++) {
		scanf("%d %d", &id, &d);
		data[id] = d;
		if (id <= lowExt)
			p = (id+treeSize) / 2;
		else
			p = (id-lowExt/2+treeSize/2) / 2;
		build(p, id);
		print();
	}

	delete[] tree;
	delete[] data;
	return 0;
}
