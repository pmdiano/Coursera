//+-----------------------------------------------------------------------------
//
//  File:       foodchain.cpp
//
//  Synopsis:   POJ 1182, copied from http://www.cnblogs.com/woozhi/p/3557063.html
//
//  Author:     Qirong Ma, 10/15/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
const int maxn = 50005;

int F[maxn];
int Set[maxn];

int N, K;
int D, X, Y;

void Init() {
	for (int i = 0; i <= N; i++) {
		F[i] = i;
		Set[i] = 0;
	}
}

int Find(int x) {
	if (F[x] == x)
		return x;
	int tmp = Find(F[x]);
	Set[x] = (Set[x] + Set[F[x]]) % 3; // why?
	return F[x] = tmp;
}

void Union(int x, int y) {
	int fx = Find(x);
	int fy = Find(y);
	if (fx != fy) {
		F[fy] = fx;
		if (D == 1)
			Set[fy] = (Set[x] - Set[y] + 3) % 3; // why?
		else if (D == 2)
			Set[fy] = (Set[x] - Set[y] + 1 + 3) % 3; // why?
	} 
}

int main() {
	scanf("%d %d", &N, &K);
	Init();
	int ans = 0;

	while (K--) {
		scanf("%d %d %d", &D, &X, &Y);
		if (X > N || Y > N) {
			ans++;
			continue;
		}

		int fx = Find(X);
		int fy = Find(Y);
		if (fx == fy) {
			if (D == 1 && Set[X] != Set[Y])
				ans++;
			else if (D == 2 && (Set[X] + 1) % 3 != Set[Y])
				ans++;
		}
		else {
			Union(X, Y);
		}
	}
	printf("%d\n", ans);
	return 0;
}
