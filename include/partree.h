//+-----------------------------------------------------------------------------
//
//  File:       partree.h
//
//  Synopsis:   Implemented a ParTree class for equivalence problems
//
//  Author:     Qirong Ma, 10/15/2015
//
//------------------------------------------------------------------------------
#pragma once
#ifndef nullptr
#define nullptr 0
#endif

template<class T>
class ParTreeNode {
private:
	T _value;
	ParTreeNode<T>* _parent;
	int _count;

public:
	ParTreeNode(): _value(0), _parent(nullptr), _count(1) {}
	virtual ~ParTreeNode() {}

	T value() {return _value;}
	void setValue(const T& val) {_value = val;}

	ParTreeNode<T>* parent() {return _parent;}
	void setParent(ParTreeNode<T>* par) {_parent = par;}

	int count() {return _count;}
	void setCount(const int count) {_count = count;}
};

template<class T>
class ParTree {
public:
	ParTreeNode<T>* array;
	int size;

	ParTree(const int s): size(s), array(new ParTreeNode<T>[s]) {}
	virtual ~ParTree() {delete[] array;}

	ParTreeNode<T>* Find(ParTreeNode<T>* node) const {
		ParTreeNode<T>* pointer = node;
		while (pointer->parent())
			pointer = pointer->parent();
		while (node != pointer) {
			node->setParent(pointer);
			node = node->parent();
		}
		return pointer;
	}

	void Union(int i, int j) {
		ParTreeNode<T>* pointeri = Find(&array[i]);
		ParTreeNode<T>* pointerj = Find(&array[j]);
		if (pointeri != pointerj) {
			if (pointeri->count() >= pointerj->count()) {
				pointerj->setParent(pointeri);
				pointeri->setCount(pointeri->count() + pointerj->count());
			}
			else {
				pointeri->setParent(pointerj);
				pointerj->setCount(pointeri->count() + pointerj->count());
			}
		}
	}

	bool Equivalent(int i, int j) {
		return Find(&array[i]) == Find(&array[j]);
	}
};
