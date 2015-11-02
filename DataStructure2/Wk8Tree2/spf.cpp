//+-----------------------------------------------------------------------------
//
//  File:       spf.cpp (Shortest Prefix)
//
//  Synopsis:   POJ 2001, Trie tree
//              
//  Author:     Qirong Ma, 11/01/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>

struct node{
	node* child[26];
	int nchild;
	node():nchild(0){
		memset(child, 0, sizeof(child));
	}
} *root;

void insert(char* s){
	node* p=root;
	while(*s && p->child[*s-'a'])
		p=p->child[(*s++)-'a'];
	while(*s){
		p->child[*s-'a']=new node();
		p->nchild++;
		p=p->child[(*s++)-'a'];
	}
	p->nchild++;
}

int query(char* s){
	node* p=root;
	int n=0,ans=0;
	while(*s){
		if (p->nchild>1)
			ans=n+1;
		p=p->child[(*s++)-'a'];
		n++;
	}
	if (p->nchild>1)
		ans=n;
	return ans?ans:n;
}

void clear(node* p){
	for (int i=0;i<26;i++)
		if (p->child[i])
			clear(p->child[i]);
	delete p;
}

char a[1000][24];

int main() {
	// freopen("in.txt", "r", stdin);
	memset(a, 0, sizeof(a));
	int n=0;
	root=new node();
	while(scanf("%s", a[n]) != EOF) {
		insert(a[n]);
		n++;
	}

	for(int i=0;i<n;i++){
		printf("%s ",a[i]);
		int len=query(a[i]);
		a[i][len]='\0';
		printf("%s\n",a[i]);
	}

	clear(root);
	return 0;
}
