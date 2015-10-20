//+-----------------------------------------------------------------------------
//
//  File:       toposort.cpp
//
//  Synopsis:   Topological sort by DFS
//
//  Author:     Qirong Ma, 10/20/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>

int n;
int **G;
int *visited;
int *order;
int tail = 0;

void dfs(int s) {
	visited[s] = 1;
	for (int j = n-1; j >= 0; j--) {
		if (!visited[j] && G[s][j])
			dfs(j);
	}
	order[tail++] = s;
}

void topo(int **G, int n) {
	visited = new int[n];
	order = new int[n];
	memset(visited, 0, n * sizeof(int));
	memset(order, 0, n * sizeof(int));

	for (int i = n-1; i >= 0; i--) {
		if (!visited[i])
			dfs(i);
	}

	for (int i = n-1; i > 0; i--)
		printf("v%d ", order[i]+1);
	printf("v%d\n", order[0]+1);

	delete[] visited;
	delete[] order;
}

int main() {
	int e, i, j, k;

	scanf("%d %d", &n, &e);
	G = new int*[n];
	for (i = 0; i < n; i++) {
		G[i] = new int[n];
		memset(G[i], 0, n*sizeof(int));
	}

	for (k = 0; k < e; k++) {
		scanf("%d %d", &i, &j);
		G[i-1][j-1] = 1;
	}

	topo(G, n);

	for (int i = 0; i < n; i++)
		delete[] G[i];
	delete[] G;
	return 0;
}
