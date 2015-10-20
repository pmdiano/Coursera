//+-----------------------------------------------------------------------------
//
//  File:       nemo.cpp
//
//  Synopsis:   POJ 2049 using Dijkstra's algorithm
//
//  Author:     Qirong Ma, 10/20/2015
//
//------------------------------------------------------------------------------
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXS = 205;
const int inf = 0x3f3f3f3f;
int l[MAXS][MAXS];
int h[MAXS][MAXS];
int dis[MAXS][MAXS];
int sx, sy;
int xmax, ymax;

struct node {
	int x;
	int y;
	int len;
	bool operator<(const node& rhs) const {
		return len > rhs.len;
	}
};

priority_queue<node> q;

void bfs() {
	int x, y;
	for (x = 0; x <= xmax; x++)
		for (y = 0; y <= ymax; y++)
			dis[x][y] = inf;

	while (!q.empty()) q.pop();
	node pn;
	pn.x = 0; pn.y = 0; pn.len = 0;
	q.push(pn);
	dis[0][0] = 0;

	while (!q.empty()) {
		pn = q.top();
		q.pop();
		x = pn.x;
		y = pn.y;
		if (x == sx && y == sy) {
			return;
		}

		// up
		if (y+1 <= ymax && dis[x][y] + h[x][y+1] < dis[x][y+1]) {
			dis[x][y+1] = dis[x][y] + h[x][y+1];
			pn.x = x; pn.y = y+1; pn.len = dis[x][y+1];
			q.push(pn);
		}
		// down
		if (y-1 >= 0 && dis[x][y] + h[x][y] < dis[x][y-1]) {
			dis[x][y-1] = dis[x][y] + h[x][y];
			pn.x = x; pn.y = y-1; pn.len = dis[x][y-1];
			q.push(pn);
		}
		// left
		if (x-1 >= 0 && dis[x][y] + l[x][y] < dis[x-1][y]) {
			dis[x-1][y] = dis[x][y] + l[x][y];
			pn.x = x-1; pn.y = y; pn.len=dis[x-1][y];
			q.push(pn);
		}
		// right
		if (x+1 <= xmax && dis[x][y] + l[x+1][y] < dis[x+1][y]) {
			dis[x+1][y] = dis[x][y] + l[x+1][y];
			pn.x = x+1; pn.y = y; pn.len = dis[x+1][y];
			q.push(pn);
		}
	}

	dis[sx][sy] = -1;
}

int main() {
	int x, y, d, t, m, n;
	while (scanf("%d %d", &m, &n)) {
		if (m == -1 && n == -1) break;
		xmax = ymax = -1;
		memset(l, 0, sizeof(l));
		memset(h, 0, sizeof(h));

		while (m--) {
			scanf("%d %d %d %d", &x, &y, &d, &t);
			if (d == 0) {
				for (int i = 0; i < t; i++)
					h[x+i][y] = inf;
				xmax = max(xmax, x+t);
				ymax = max(ymax, y);
			}
			else {
				for (int i = 0; i < t; i++)
					l[x][y+i] = inf;
				xmax = max(xmax, x);
				ymax = max(ymax, y+t);
			}
		}

		while (n--) {
			scanf("%d %d %d", &x, &y, &d);
			if (d == 0)
				h[x][y] = 1;
			else
				l[x][y] = 1;
		}

		float f1, f2;
		scanf("%f %f", &f1, &f2);
		sx = (int)f1;
		sy = (int)f2;
		if (sx < 0 || sx > xmax || sy < 0 || sy > ymax) {
			printf("0\n");
			continue;
		}

		bfs();
		printf("%d\n", dis[sx][sy]);
	}
}
