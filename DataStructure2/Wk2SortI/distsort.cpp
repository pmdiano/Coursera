//+-----------------------------------------------------------------------------
//
//  File:       distsort.cpp
//
//  Synopsis:   Sort I, problem 1
//              https://www.coursera.org/learn/gaoji-shuju-jiegou/programming/
//               dYX9U/bian-cheng-zuo-ye-nei-pai-xu-shang-3ti
//
//  Author:     Qirong Ma, 10/22/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cmath>
#include "../../include/sort.h"

struct point {
	int x, y, z;
	point(){}
	point(int i1, int i2, int i3):x(i1), y(i2), z(i3){}
};

struct elem {
	point p1;
	point p2;
	float dist;

	elem(){}
	elem(const point& pa, const point& pb){
		p1 = pa;
		p2 = pb;
		dist = sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
	}

	bool operator<(const elem& e2) const {return dist > e2.dist;}
	void print() {
		printf("(%d,%d,%d)-(%d,%d,%d)=%.2f\n", p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, dist);
	}
};

int main() {
	int n;
	scanf("%d", &n);
	if (n <= 1) return 0;

	point* points = new point[n];
	elem* array = new elem[n*(n-1)/2];

	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].z);
	}
	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++)
			array[k++] = elem(points[i], points[j]);
	}

	bubbleSort(array, k);
	for (int i = 0; i < k; i++)
		array[i].print();

	delete[] points;
	delete[] array;
	return 0;
}
