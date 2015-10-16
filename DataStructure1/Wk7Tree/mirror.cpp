//+-----------------------------------------------------------------------------
//
//  File:       mirror.cpp
//
//  Synopsis:   Input preorder representation of a tree, mirror the tree, and
//              output its width traversal.
//              https://www.coursera.org/learn/shuju-jiegou-suanfa/programming
//               /L0pOe/bian-cheng-zuo-ye-shu-3ti
//
//  Author:     Qirong Ma, 10/16/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <stack>
#include "../../include/tree.h"
using namespace std;

int main() {
	int n;
	char c, leaf;
	Tree<char> tree;
	TreeNode<char>* root = nullptr, *current = nullptr;
	stack<TreeNode<char>*> stk;

	scanf("%d", &n);
	getchar();

	scanf("%c%c", &c, &leaf);
	getchar();
	root = new TreeNode<char>(c);
	current = root;
	if (leaf == '0')
		stk.push(root);

	while (!stk.empty()) {
		scanf("%c%c", &c, &leaf);
		getchar();

		if (c == '$') {
			if (!current)
				stk.pop();
			current = nullptr;
			continue;
		}

		TreeNode<char>* node = new TreeNode<char>(c);

		if (current) {
			current->setChild(node);
		}
		else {
			stk.top()->setSibling(node);
			stk.pop();			
		}

		if (leaf == '0') {
			stk.push(node);
			current = node;
		}
		else
			current = nullptr;
	}

	tree.setRoot(root);
	tree.mirror();
	tree.widthTraverse([](char c){printf("%c ", c);});
	printf("\n");
	return 0;
}
