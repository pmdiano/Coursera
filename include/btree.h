//+-----------------------------------------------------------------------------
//
//  File:       btree.h
//
//  Synopsis:   Implemented a minimal Binary Tree
//
//  Author:     Qirong Ma, 10/12/2015
//
//------------------------------------------------------------------------------
#pragma once
#ifndef nullptr
#define nullptr 0
#endif

template<class T>
class BTree;

template<class T>
class BTreeNode {
friend class BTree<T>;
	T _info;
	BTreeNode<T>* _left;
	BTreeNode<T>* _right;

public:
	// Use with caution
	void release() {
		if (_left) _left->release();
		if (_right) _right->release();
		delete this;
	}

	BTreeNode(): _left(nullptr), _right(nullptr) {}
	BTreeNode(const T& ele): _info(ele), _left(nullptr), _right(nullptr) {}
	BTreeNode(const T& ele, BTreeNode<T> *l, BTreeNode<T> *r):
		_info(ele),
		_left(l),
		_right(r)
	{}
	~BTreeNode() {}

	T value() const {return _info;}
	void setValue(const T& val) {_info = val;}

	BTreeNode<T>* leftChild() const { return _left; }
	BTreeNode<T>* rightChild() const { return _right; }
	void setLeftChild(BTreeNode<T>* l) { _left = l; }
	void setRightChild(BTreeNode<T>* r) { _right = r; }

	int height() {
		int leftHeight = _left ? _left->height() : 0;
		int rightHeight = _right ? _right->height() : 0;
		return leftHeight > rightHeight ? (leftHeight + 1) : (rightHeight + 1);
	}
};

template<class T>
class BTree {
protected:
	BTreeNode<T>* _root;

public:
	BTree(): _root(nullptr) {}
	BTree(const T& rootVal) {
		_root = new BTreeNode<T>(rootVal, nullptr, nullptr);
	}
	virtual ~BTree() {
		if (_root)
			_root->release();
		_root = nullptr;
	}

	BTreeNode<T>* root() {return _root;}
	void setRoot(BTreeNode<T>* r) {_root = r;}
};
