//+-----------------------------------------------------------------------------
//
//  File:       expression.cpp
//
//  Synopsis:   Construct a binary tree from infix notation, output its postfix
//              notation, output the tree structure, and evaluate its value with
//              some certain variable values.
//              https://www.coursera.org/learn/shuju-jiegou-suanfa/programming
//                /xWDZU/bian-cheng-zuo-ye-er-cha-shu-ying-yong-3ti
//
//  Author:     Qirong Ma, 10/13/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>
#include <stack>
#include <cassert>
#include "../../include/btree.h"
using namespace std;

char precede(char op1, char op2) {
	char res = '#';
	switch (op1) {
		case '+': switch (op2) {
			case '+': res = '>'; break;
			case '-': res = '>'; break;
			case '*': res = '<'; break;
			case '/': res = '<'; break;
			case '(': res = '<'; break;
			case ')': res = '>'; break;
			case '#': res = '>'; break;
			default: break;
		}
		break;

		case '-': switch (op2) {
			case '+': res = '>'; break;
			case '-': res = '>'; break;
			case '*': res = '<'; break;
			case '/': res = '<'; break;
			case '(': res = '<'; break;
			case ')': res = '>'; break;
			case '#': res = '>'; break;
			default: break;
		}
		break;
	
		case '*': switch (op2) {
			case '+': res = '>'; break;
			case '-': res = '>'; break;
			case '*': res = '>'; break;
			case '/': res = '>'; break;
			case '(': res = '<'; break;
			case ')': res = '>'; break;
			case '#': res = '>'; break;
			default: break;
		}
		break;

		case '/': switch (op2) {
			case '+': res = '>'; break;
			case '-': res = '>'; break;
			case '*': res = '>'; break;
			case '/': res = '>'; break;
			case '(': res = '<'; break;
			case ')': res = '>'; break;
			case '#': res = '>'; break;
			default: break;
		}
		break;

		case '(': switch (op2) {
			case '+': res = '<'; break;
			case '-': res = '<'; break;
			case '*': res = '<'; break;
			case '/': res = '<'; break;
			case '(': res = '<'; break;
			case ')': res = '='; break;
			case '#': res = '#'; break;
			default: break;
		}
		break;

		case ')': switch (op2) {
			case '+': res = '>'; break;
			case '-': res = '>'; break;
			case '*': res = '>'; break;
			case '/': res = '>'; break;
			case '(': res = '#'; break;
			case ')': res = '>'; break;
			case '#': res = '>'; break;
			default: break;
		}
		break;

		case '#': switch (op2) {
			case '+': res = '<'; break;
			case '-': res = '<'; break;
			case '*': res = '<'; break;
			case '/': res = '<'; break;
			case '(': res = '<'; break;
			case ')': res = '#'; break;
			case '#': res = '='; break;
			default: break;
		}
		break;

		default: break;
	}

	return res;
}

bool isoptr(char c) {
	if (c == '+' ||
		c == '-' ||
		c == '*' ||
		c == '/' ||
		c == '(' ||
		c == ')' ||
		c == '#')
		return true;
	return false;
}

BTreeNode<char>* operate(BTreeNode<char>* ex1, char op, BTreeNode<char>* ex2) {
	assert (op == '+' || op == '-' || op == '*' || op == '/');
	return new BTreeNode<char>(op, ex1, ex2);	
}

BTreeNode<char>* get_btree(char* expr) {
	char c;
	BTreeNode<char> *ex1, *ex2;
	stack<BTreeNode<char>*> exprStack;
	stack<char> optrStack;
	optrStack.push('#');

	int len = strlen(expr);
	expr[len] = '#';
	expr[len+1] = '\0';

	c = *expr;
	while (c != '#' || optrStack.top() != '#') {
		if (!isoptr(c)) {
			exprStack.push(new BTreeNode<char>(c));
			c = *(++expr);
		}
		else {
			switch (precede(optrStack.top(), c)) {
				case '<':
					optrStack.push(c);
					c = *(++expr);
					break;
				case '=': // remove () pair
					optrStack.pop();
					c = *(++expr);
					break;
				case '>':
					ex2 = exprStack.top();
					exprStack.pop();
					ex1 = exprStack.top();
					exprStack.pop();
					exprStack.push(operate(ex1, optrStack.top(), ex2));
					optrStack.pop();
					// continue compare the same c with operators in stack
					break;
				default:
					printf("Error! %c%c\n", optrStack.top(), c);
					assert(0);
					break;
			}
		}
	}

	return exprStack.top();
}

void post_order(BTreeNode<char>* root) {
	if (root) {
		post_order(root->leftChild());
		post_order(root->rightChild());
		printf("%c", root->value());
	}
}

int exp2n(int n) {
	int res = 1;
	while (n-- > 0) res *= 2;
	return res;
}

const char space = ' ';
void print_tree(BTreeNode<char>* root) {
	int H = root->height();
	BTreeNode<char> **q = new BTreeNode<char>*[exp2n(H)];
	char *line = new char[exp2n(H)];
	int qHead = 0;
	int qTail = 0;

	q[qTail++] = root;
	for (int h = H; h >= 1; h--) {
		int blank = exp2n(h-1)-1;
		int step = exp2n(h);
		int l = 0;

		// print all nodes on current level
		for (int i = 0; i < blank; i++)
			line[l++] = space;
		for (int i = qHead; i < qTail; i++) {
			line[l++] = q[i] ? q[i]->value() : space;
			if (i < qTail-1)
				for (int j = 0; j < step-1; j++)
					line[l++] = space;
		}
		line[l] = '\0';
		printf("%s\n", line);

		// print / and \ for this level's children
		if (h == 1) break;
		l = 0;
		for (int i = 0; i < blank-1; i++)
			line[l++] = space;
		for (int i = qHead; i < qTail; i++) {
			line[l++] = (q[i] && q[i]->leftChild()) ? '/' : space;
			line[l++] = space;
			line[l++] = (q[i] && q[i]->rightChild()) ? '\\' : space;
			if (i < qTail-1)
				for (int j = 0; j < step-3; j++)
					line[l++] = space;
		}
		while (line[l-1] == space)
			l--;
		line[l] = '\0';
		printf("%s\n", line);

		// step to next level
		int qqHead = qTail;
		int qqTail = qTail;
		for (int i = qHead; i < qTail; i++) {
			if (q[i]) {
				q[qqTail++] = q[i]->leftChild();
				q[qqTail++] = q[i]->rightChild();
			}
			else {
				q[qqTail++] = nullptr;
				q[qqTail++] = nullptr;
			}
		}
		while (q[qqTail-1] == nullptr) qqTail--;
		qHead = qqHead;
		qTail = qqTail;
	}

	delete[] q;
	delete[] line;
}

int val[26];
int eval(BTreeNode<char>* root) {
	if (!isoptr(root->value()))
		return val[root->value() - 'a'];
	switch (root->value()) {
		case '+': return eval(root->leftChild()) + eval(root->rightChild());
		case '-': return eval(root->leftChild()) - eval(root->rightChild());
		case '*': return eval(root->leftChild()) * eval(root->rightChild());
		case '/': return eval(root->leftChild()) / eval(root->rightChild());
		default: return 0;
	}
}

int main() {
	char expr[64];
	scanf("%s", expr);
	BTreeNode<char>* exptree = get_btree(expr);

	post_order(exptree);
	printf("\n");

	print_tree(exptree);

	int n, v;
	char c;
	scanf("%d", &n);
	while (n--) {
		getchar();
		c = getchar();
		scanf("%d", &v);
		val[c-'a'] = v;
	}
	printf("%d\n", eval(exptree));

	exptree->release();
}
