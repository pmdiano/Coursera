//+-----------------------------------------------------------------------------
//
//  File:       huffmantree.h
//
//  Synopsis:   Implemented a Huffman Tree, each node with weight
//              while each node should have both value and weight
//
//  Author:     Qirong Ma, 10/12/2015
//
//------------------------------------------------------------------------------
#pragma once
#include "minheap.h"
#include "btree.h"

template<class T>
class HuffmanTree {
	struct Elem{
		T weight;
		BTreeNode<T>* node;
		Elem():weight(T()), node(nullptr) {}
		Elem(T w, BTreeNode<T>* p):weight(w), node(p) {}

		bool operator<(const Elem& rhs) const {return weight < rhs.weight;}
		bool operator>(const Elem& rhs) const {return weight > rhs.weight;}
	};
public:
	HuffmanTree(T weight[], int n) {
		MinHeap<Elem> heap(n);
		Elem left, right;
		BTreeNode<T> *parent;
		BTreeNode<T> **nodeList = new BTreeNode<T>*[n];

		for (int i = 0; i < n; i++) {
			nodeList[i] = new BTreeNode<T>(weight[i]);
			heap.Insert(Elem(weight[i], nodeList[i]));
		}

		for (int i = 0; i < n-1; i++) {
			heap.Remove(0, left);
			heap.Remove(0, right);
			parent = new BTreeNode<T>(
				left.node->value() + right.node->value(),
				left.node,
				right.node);
			heap.Insert(Elem(left.weight+right.weight, parent));
		}

		_root = parent;
		delete[] nodeList;
	}

	BTreeNode<T>* root() {return _root;}
	virtual ~HuffmanTree() {if (_root) _root->release();}

private:
	BTreeNode<T>* _root;
};
