//+-----------------------------------------------------------------------------
//
//  File:       degreelevel.h
//
//  Synopsis:   Input degree-width representation of a forest, output its
//              root last traversal.
//              https://www.coursera.org/learn/shuju-jiegou-suanfa/programming
//               /L0pOe/bian-cheng-zuo-ye-shu-3ti
//
//  Author:     Qirong Ma, 10/15/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <iostream>
#include "../../include/tree.h"
using namespace std;

struct elem{
	TreeNode<char>* node;
	int degree;
	elem(TreeNode<char>* p, int d): node(p), degree(d) {}
	elem() {}
};

int main() {
	int n, d;
	char c;
	TreeNode<char> *root, *current = nullptr;
	Tree<char> tree;
	elem father;
	queue<elem> q;

	(cin >> n).get();
	cin >> c >> d;

	tree.createRoot(c);
	root = tree.getRoot();
	if (d) q.push(elem(root, d));

	while (true) {
		while (!q.empty() || current) {
			cin >> c >> d;
			TreeNode<char>* node = new TreeNode<char>(c);
			if (d) q.push(elem(node, d));
			if (!current) {
				father = q.front();
				q.pop();
				father.node->setChild(node);
			}
			else {
				current->setSibling(node);
			}

			if (--father.degree)
				current = node;
			else
				current = nullptr;
		}

		if (--n) {
			cin.get();
			cin >> c >> d;
			TreeNode<char>* node = new TreeNode<char>(c);
			if (d) q.push(elem(node, d));
			root->setSibling(node);
			root = node;
		}
		else
			break;
	}

	tree.rootLastTraverse([](char c){printf("%c ", c);});
	printf("\n");

	return 0;
}
