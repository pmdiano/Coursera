//+-----------------------------------------------------------------------------
//
//  File:       huffman.cpp
//
//  Synopsis:   Simple Huffman tree to calculate min weighted sum of code length
//              https://www.coursera.org/learn/shuju-jiegou-suanfa/programming
//                /xWDZU/bian-cheng-zuo-ye-er-cha-shu-ying-yong-3ti
//
//  Author:     Qirong Ma, 10/12/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include "../../include/huffmantree.h"

int total;
void pre_traverse(BTreeNode<int>* node, int depth) {
	if (!node->leftChild() && !node->rightChild()) {
		total += depth * node->value();
	}
	else {
		pre_traverse(node->leftChild(), depth+1);
		pre_traverse(node->rightChild(), depth+1);
	}
}

int main() {
	int N;
	scanf("%d", &N);
	int *weight = new int[N];
	for (int i = 0; i < N; i++)
		scanf("%d", weight+i);

	total = 0;
	HuffmanTree<int> ht(weight, N);
	pre_traverse(ht.root(), 0);
	printf("%d\n", total);

	delete[] weight;
	return 0;
}
