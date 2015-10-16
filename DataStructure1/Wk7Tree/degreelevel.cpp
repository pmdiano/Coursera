#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
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
	string line;
	Tree<char> tree;
	TreeNode<char> *root, *current;
	queue<elem> q;

	tree.createRoot(0);
	root = tree.getRoot();
	current = root;

	cin >> n;
	while (n--) {
		cin >> line;
		istringstream is(line);

		while (is >> c >> d) {
			current->setValue(c);
			if (d)
				q.push(elem(current, d));

		}
	}
	return 0;
}
