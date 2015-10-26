//+-----------------------------------------------------------------------------
//
//  File:       findcatch.cpp
//
//  Synopsis:   POJ 1703, find union
//              see http://blog.csdn.net/super_chris/article/details/4568241
//
//  Author:     Qirong Ma, 10/26/2015
//
//------------------------------------------------------------------------------
#include <cstdio>

const int maxn = 100005;
int F[maxn];
int Set[maxn];
int N, M;

void init() {
	for (int i = 1; i <= N; i++) {
		F[i] = i;
		Set[i] = 0;
	}
}

int find(int x) {
	if (F[x] == x)
		return x;
	int tmp = find(F[x]);
	Set[x] = (Set[x] + Set[F[x]]) % 2;
	return F[x] = tmp;
}

void Union(int x, int y) {
	int fx = find(x);
	int fy = find(y);
	if (fx != fy) {
		F[fy] = fx;
		Set[fy] = (Set[x] - Set[y] + 1) % 2;
	}
}

int main() {
	int ncase;
	scanf("%d", &ncase);

	while (ncase--) {
		scanf("%d %d", &N, &M);
		getchar();
		init();

		char c;
		int x, y, fx, fy;
		while (M--) {
			c = getchar();
			scanf("%d %d", &x, &y);
			getchar();

			if (c == 'D') {
				Union(x, y);
 			}
 			else if (c == 'A') {
 				fx = find(x);
 				fy = find(y);
 				if (fx != fy) {
 					printf("Not sure yet.\n");
 				}
 				else {
 					if (Set[x] == Set[y])
 						printf("In the same gang.\n");
 					else
 						printf("In different gangs.\n");
 				}
 			}
		}
	}

	return 0;
}
