//+-----------------------------------------------------------------------------
//
//  File:       minmax.cpp
//
//  Synopsis:   https://www.coursera.org/learn/gaoji-shuju-jiegou/home/week/8
//              
//  Author:     Qirong Ma, 11/01/2015
//
//------------------------------------------------------------------------------
#include <set>
#include <cstdio>
using namespace std;

struct client{
	int id;
	int p;
	bool operator<(const client& c) const{
		return p<c.p;
	}
};

int main(){
	int c, K, P;
	set<client> A;
	set<client>::iterator it;
	while(scanf("%d", &c),c){
		if(c==1){
			scanf("%d%d",&K,&P);
			client cl;
			cl.id=K;
			cl.p=P;
			A.insert(cl);
		}
		if(c==2){
			if(A.empty())printf("0\n");
			else{
				it=A.end();
				it--;
				printf("%d\n",it->id);
				A.erase(it);
			}
		}
		if(c==3){
			if(A.empty())printf("0\n");
			else{
				it=A.begin();
				printf("%d\n",it->id);
				A.erase(it);
			}
		}
	}
}
