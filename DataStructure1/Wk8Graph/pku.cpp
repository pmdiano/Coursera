//+-----------------------------------------------------------------------------
//
//  File:       pku.cpp
//
//  Synopsis:   Finding shortest path using Dijkstra and Floyd algorithm
//
//  Author:     Qirong Ma, 10/19/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;

const int NODE = 30;
const int NAMELEN = 20;
const int INFINITE = 88888888;

int P, Q;
char name[NODE][NAMELEN+1];
int G[NODE][NODE];
int visited[NODE];
struct Dist {
	int index;
	int length;
	int pre;
	bool operator<(const Dist& rhs) const {return length > rhs.length;}
} D[NODE], FD[NODE][NODE];

void findidx(char* name1, char* name2, int* id1, int* id2) {
	for (int j = 0; j < P; j++) {
		if (strcmp(name1, name[j]) == 0)
			*id1 = j;
		if (strcmp(name2, name[j]) == 0)
			*id2 = j;
	}
}

void dijkstra(int id1, int id2) {
	for (int i = 0; i < P; i++) {
		visited[i] = 0;
		D[i].index = i; D[i].length = INFINITE; D[i].pre = id1;
	}
	D[id1].length = 0;
	priority_queue<Dist> q;
	q.push(D[id1]);

	Dist d;
	while (!q.empty()) {
		d = q.top(); q.pop();
		if (d.index == id2) break;
		for (int j = 0; j < P; j++) {
			if (G[d.index][j] && d.length + G[d.index][j] < D[j].length) {
				D[j].length = d.length + G[d.index][j];
				D[j].pre = d.index;
				q.push(D[j]);
			}
		}
	}

	stack<int> path;
	int id = id2;
	path.push(id);
	while (id != id1) {
		id = D[id].pre;
		path.push(id);
	}

	while (true) {
		id = path.top();
		path.pop();
		printf("%s", name[id]);
		if (path.empty()) break;
		printf("->(%d)->", G[id][path.top()]);
	}
	printf("\n");
}

void floyd() {
	for (int i = 0; i < P; i++) {
		for (int j = 0; j < P; j++) {
			if (i == j) {
				FD[i][j].length = 0;
				FD[i][j].pre = i;
			}
			else if (G[i][j]) {
				FD[i][j].length = G[i][j];
				FD[i][j].pre = i;
			}
			else {
				FD[i][j].length = INFINITE;
				FD[i][j].pre = -1;
			}
		}
	}

	for (int k = 0; k < P; k++) {
		for (int i = 0; i < P; i++) {
			for (int j = 0; j < P; j++) {
				if (FD[i][k].length + FD[k][j].length < FD[i][j].length) {
					FD[i][j].length = FD[i][k].length + FD[k][j].length;
					FD[i][j].pre = FD[k][j].pre;
				}
			}
		}
	}
}

void floyd_output(int id1, int id2) {
	stack<int> path;
	while (id2 != id1) {
		path.push(id2);
		id2 = FD[id1][id2].pre;
	}
	path.push(id1);

	while (true) {
		id1 = path.top();
		path.pop();
		printf("%s", name[id1]);
		if (path.empty()) break;
		printf("->(%d)->", G[id1][path.top()]);
	}
	printf("\n");
}

int main() {
	int e, id1, id2, ncase;
	char name1[NAMELEN+1], name2[NAMELEN+1];

	memset(G, 0, sizeof(G));
	scanf("%d", &P);
	for (int i = 0; i < P; i++) {
		scanf("%s", name[i]);
	}

	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		scanf("%s %s %d", name1, name2, &e);
		findidx(name1, name2, &id1, &id2);
		if (!G[id1][id2] || G[id1][id2] > e) { // The input is a bit weird
			G[id1][id2] = e;
			G[id2][id1] = e;
		}
	}

	floyd();

	scanf("%d", &ncase);
	for (int i = 0; i < ncase; i++) {
		scanf("%s %s", name1, name2);
		findidx(name1, name2, &id1, &id2);
		//dijkstra(id1, id2);
		floyd_output(id1, id2);
	}
}
