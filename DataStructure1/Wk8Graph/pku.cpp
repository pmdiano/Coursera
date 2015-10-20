#include <cstdio>
#include <cstring>
#include <stack>
#include "../../include/minheap.h"
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
	bool operator<(const Dist& rhs) const {return length < rhs.length;}
	bool operator>(const Dist& rhs) const {return length > rhs.length;}
} D[NODE];

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
	MinHeap<Dist> H(Q);
	H.Insert(D[id1]);

	for (int i = 0; i < P; i++) {
		bool found = false;
		Dist d;
		while (H.size()) {
			d = H.RemoveMin();
			if (!visited[d.index]) {
				found = true; break;
			}
		}
		if (!found) {
			break;
		}
		int v = d.index;
		visited[v] = 1;
		for (int j = 0; j < P; j++)
			if (!visited[j] && G[v][j] && D[j].length > (D[v].length + G[v][j])) {
				D[j].length = D[v].length + G[v][j];
				D[j].pre = v;
				H.Insert(D[j]);
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

int main() {
	freopen("in1.txt", "r", stdin);
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
		if (!G[id1][id2] || G[id1][id2] > e) {
			G[id1][id2] = e;
			G[id2][id1] = e;
		}
	}

	scanf("%d", &ncase);
	for (int i = 0; i < ncase; i++) {
		scanf("%s %s", name1, name2);
		findidx(name1, name2, &id1, &id2);
		dijkstra(id1, id2);
	}
}
