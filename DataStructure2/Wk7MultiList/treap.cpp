//+-----------------------------------------------------------------------------
//
//  File:       treap.cpp
//
//  Synopsis:   POJ 1785, treap construction
//              
//  Author:     Qirong Ma, 11/01/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct node{
	int val;
	int lson, rson, fa;
	char s[100];
	bool operator<(const node& n) const {
		return strcmp(s, n.s) < 0;
	}
} a[50005];

void insert(int n){
	int j=n-1;
	while (a[j].val<a[n].val) j=a[j].fa;
	a[n].lson = a[j].rson;
	a[j].rson = n;
	a[n].fa = j;
}

void travel(int n){
	if(n==0) return;
	printf("(");
	travel(a[n].lson);
	printf("%s/%d",a[n].s,a[n].val);
	travel(a[n].rson);
	printf(")");
}

int main() {
	int n;
	while (scanf("%d", &n), n){
		for(int i=1;i<=n;i++){
			scanf(" %[a-z]/%d",a[i].s,&a[i].val);
			a[i].lson=a[i].rson=a[i].fa=0;
		}
		sort(a+1,a+n+1);
		a[0].val=0x3f3f3f3f;
		a[0].lson=a[0].rson=a[0].fa=0;

		for(int i=1;i<=n;i++)
			insert(i);

		travel(a[0].rson);
		printf("\n");
	}
}
