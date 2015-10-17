#include <cstdio>
#include "..\..\include\partree.h"

int main() {
	int N, K, D, x, y, total = 0;
	scanf("%d%d", &N, &K);
	ParTree<char> tree(N+1);
	ParTreeNode<char> *px, *py;

	for (int i = 0; i < K; i++) {
		scanf("%d%d%d", &D, &x, &y);
		if (x > N || y > N) {
			total++;
			continue;
		}
		if (D == 2 && x == y) {
			total++;
			continue;
		}

		px = tree.Find(&tree.array[x]);
		py = tree.Find(&tree.array[y]);
		if (D == 1) {
			if (px->value() != py->value()) {
				total++;
				continue;
			}
			tree.Union(x, y);
		}
		else {
			if (px->value() && py->value()) {
				if (px->value() == 'A' && py->value() != 'B' ||
					px->value() == 'B' && py->value() != 'C' ||
					px->value() == 'C' && py->value() != 'A') {
					total++;
					continue;
				}
			}
			else if (px->value()) {
				if (px->value() == 'C')
					py->setValue('A');
				else
					py->setValue(px->value()+1);
			}
			else if (py->value()) {
				if (py->value() == 'A')
					px->setValue('C');
				else
					px->setValue(py->value()-1);
			}
			else {
				px->setValue('A');
				py->setValue('B');
			}
		}
	}

	printf("%d\n", total);
	return 0;
}
