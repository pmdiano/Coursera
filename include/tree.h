//+-----------------------------------------------------------------------------
//
//  File:       tree.h
//
//  Synopsis:   Implemented a minimal tree with leftChild/nextSibling
//
//  Author:     Qirong Ma, 10/15/2015
//
//------------------------------------------------------------------------------
#pragma once
#include <queue>
#include <stack>
#ifndef nullptr
#define nullptr 0
#endif

template<class T>
class TreeNode {
private:
	T _info;
	TreeNode<T>* _child;
	TreeNode<T>* _sibling;

public:
	TreeNode(): _child(nullptr), _sibling(nullptr) {}
	TreeNode(const T& value): _info(value), _child(nullptr), _sibling(nullptr) {}
	~TreeNode() {}

	T value() const {return _info;}
	TreeNode<T>* leftChild() const {return _child;}
	TreeNode<T>* nextSibling() const {return _sibling;}
	void setValue(const T& value) {_info = value;}
	void setChild(TreeNode<T>* node) {_child = node;}
	void setSibling(TreeNode<T>* node) {_sibling = node;}
};

template<class T>
class Tree {
private:
	TreeNode<T>* _root;

	void _destroyNodes(TreeNode<T>* root) {
		if (root) {
			_destroyNodes(root->leftChild());
			_destroyNodes(root->nextSibling());
			delete root;
		}
	}

	template<class VF>
	void _rootFirstTraverse(TreeNode<T>* root, VF visit) {
		while (root) {
			visit(root->value());
			_rootFirstTraverse(root->leftChild(), visit);
			root = root->nextSibling();
		}
	}

	template<class VF>
	void _rootLastTraverse(TreeNode<T>* root, VF visit) {
		while (root) {
			_rootLastTraverse(root->leftChild(), visit);
			visit(root->value());
			root = root->nextSibling();
		}
	}

public:
	Tree() : _root(nullptr) {}
	virtual ~Tree() {_destroyNodes(_root);}

	TreeNode<T>* getRoot() {return _root;}
	void setRoot(TreeNode<T>* node) {
		_destroyNodes(_root);
		_root = node;
	}
	void createRoot(const T& value) {setRoot(new TreeNode<T>(value));}
	void destroy() {setRoot(nullptr);}

	template<class VF>
	void rootFirstTraverse(VF visit) {_rootFirstTraverse(_root, visit);}

	template<class VF>
	void rootLastTraverse(VF visit) {_rootLastTraverse(_root, visit);}

	template<class VF>
	void widthTraverse(VF visit) {
		std::queue<TreeNode<T>*> q;
		TreeNode<T>* node = _root;
		while (node) {
			q.push(node);
			node = node->nextSibling();
		}

		while (!q.empty()) {
			node = q.front();
			q.pop();
			visit(node->value());
			node = node->leftChild();
			while (node) {
				q.push(node);
				node = node->nextSibling();
			}
		}
	}

	void mirror() {
		TreeNode<T> *father, *node, *child, *sibling;
		std::stack<TreeNode<T>*> stk;
		std::queue<TreeNode<T>*> q;

		// virtual father
		father = new TreeNode<T>(_root->value());
		father->setChild(_root);
		q.push(father);

		while (!q.empty()) {
			node = q.front();
			q.pop();

			child = node->leftChild();
			if (!child)
				continue;
			while (child) {
				q.push(child);
				stk.push(child);
				child = child->nextSibling();
			}

			child = stk.top();
			stk.pop();
			node->setChild(child);
			while (!stk.empty()) {
				child->setSibling(stk.top());
				child = stk.top();
				stk.pop();
			}
			child->setSibling(nullptr);
		}

		_root = father->leftChild();
		delete father;
	}
};
