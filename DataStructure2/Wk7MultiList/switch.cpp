//+-----------------------------------------------------------------------------
//
//  File:       switch.cpp
//
//  Synopsis:   POJ 1830, Gaussian elimination
//              
//  Author:     Qirong Ma, 11/01/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>

const int maxn = 32;
int m, n;
int A[maxn][maxn];

void _swap(int& a,int& b){
	int tmp=a;
	a=b;
	b=tmp;
}

int Gauss() {
	int row, col, max_r, i, j;
	for (row=0,col=0;row<m&&col<n;row++,col++){
		max_r = row;
		for(i=row+1;i<m;i++){
			if(A[i][col]>A[max_r][col])
				max_r=i;
		}
		if(max_r!=row){
			for(j=row;j<n+1;j++)
				_swap(A[row][j],A[max_r][j]);
		}
		if(A[row][col]==0){
			row--;
			continue;
		}
		for(i=row+1;i<m;i++){
			if(A[i][col]==0)
				continue;
			for(j=col;j<n+1;j++)
				A[i][j]^=A[row][j];
		}
	}
	for(i=row;i<m;i++){
		if(A[i][col])
			return -1;
	}
	return 1 << (n-row);
}

int main() {
	int K, N, i, j, t;
	scanf("%d", &K);

	while (K--) {
		memset(A, 0, sizeof(A));
		scanf("%d", &N);
		for (i = 0; i < N; i++)
			scanf("%d", &A[i][N]);
		for (i = 0; i < N; i++) {
			scanf("%d", &t);
			A[i][N] ^= t;
			A[i][i] = 1;
		}
		while (scanf("%d%d", &i, &j), i || j)
			A[j-1][i-1] = 1;

		m = n = N;
		int ans = Gauss();

		if (ans != -1) printf("%d\n", ans);
		else printf("Oh,it's impossible~!!\n");
	}

	return 0;
}
