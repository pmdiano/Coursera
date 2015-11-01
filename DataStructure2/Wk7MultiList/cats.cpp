//+-----------------------------------------------------------------------------
//
//  File:       cats.cpp
//
//  Synopsis:   POJ 3735, quick power of matrix
//              
//  Author:     Qirong Ma, 11/01/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
struct matrix {
	ll m[105][105];
}a;

int n,k;
ll m;

matrix multiply(matrix x, matrix y){
	matrix ans;
	memset(ans.m,0,sizeof(ans.m));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(x.m[i][j])
				for(int k=1;k<=n;k++)
					ans.m[i][k]+=x.m[i][j]*y.m[j][k];
	return ans;
}

matrix quickmod(int p){
	matrix ans;
	memset(ans.m,0,sizeof(ans.m));
	for(int i=1;i<=n;i++)
		ans.m[i][i]=1;
	while(p){
		if(p&1)
			ans=multiply(ans,a);
		p>>=1;
		a=multiply(a,a);
	}
	return ans;
}

int main(){
	char s[10];
	int i,j;
	while(scanf("%d %lld %d",&n,&m,&k)!=EOF && (n+m+k)) {
		n++;
		memset(a.m,0,sizeof(a.m));
		for(i=1;i<=n;i++)
			a.m[i][i]=1;

		while(k--){
			scanf("%s",s);
			if(s[0]=='g'){
				scanf("%d",&i);
				a.m[i][n]++;
			}
			if(s[0]=='e'){
				scanf("%d",&i);
				for(j=1;j<=n;j++)
					a.m[i][j]=0;
			}
			if(s[0]=='s'){
				scanf("%d%d",&i,&j);
				for(int t=1;t<=n;t++)
					swap(a.m[i][t], a.m[j][t]);
			}
		}

		matrix ans=quickmod(m);
		for(i=1;i<n;i++)
			printf("%lld ",ans.m[i][n]);
		printf("\n");
	}
	return 0;
}
