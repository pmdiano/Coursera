//+-----------------------------------------------------------------------------
//
//  File:       bst.cpp
//
//  Synopsis:   Simple BST, only inserting at leaf node
//              https://www.coursera.org/learn/shuju-jiegou-suanfa/programming
//                /xWDZU/bian-cheng-zuo-ye-er-cha-shu-ying-yong-3ti
//
//  Author:     Qirong Ma, 10/12/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cassert>
#include "../../include/btree.h"

template<class T>
class BST : public BTree<T> {
public:
	void Insert(T val) {
		if (!BTree<T>::_root) {
			BTree<T>::_root = new BTreeNode<T>(val, nullptr, nullptr);
			return;
		}

		BTreeNode<T> *parent, *node = BTree<T>::_root;
		while (node && node->value() != val) {
			if (val < node->value()) {
				parent = node;
				node = node->leftChild();
			}
			else {
				parent = node;
				node = node->rightChild();
			}
		}

		if (node && node->value() == val)
			return;
		else
			assert(!node);

		if (val < parent->value())
			parent->setLeftChild(new BTreeNode<T>(val));
		else
			parent->setRightChild(new BTreeNode<T>(val));
	}
};

void pre_traverse(BTreeNode<int> *root) {
	if (root) {
		printf("%d ", root->value());
		pre_traverse(root->leftChild());
		pre_traverse(root->rightChild());
	}
}

int main() {
	BST<int> bst;
	int v;
	while (1 == scanf("%d", &v))
		bst.Insert(v);

	pre_traverse(bst.root());
	printf("\n");
	return 0;
}
