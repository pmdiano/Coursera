//+-----------------------------------------------------------------------------
//
//  File:       Retrieve.cpp
//
//  Synopsis:   Set operations
//              https://www.coursera.org/learn/gaoji-shuju-jiegou/programming
//               /JFMM4/bian-cheng-zuo-ye-suo-yin-2ti
//
//  Author:     Qirong Ma, 10/27/2015
//
//------------------------------------------------------------------------------
#include <cstdio>

template<int CN>
class MySet {
	typedef unsigned int _uint;
	static const int _size = CN / sizeof(_uint) + 1;
	_uint _a[_size];

public:
	MySet(bool full = false) {
		for (int i = 0; i < _size; i++)
			_a[i] = 0;
		if (full) {
			for (int i = 0; i < CN; i++)
				set(i, true);
		}
	}

	bool none() {
		for (int i = 0; i < _size-1; i++)
			if (_a[i] != 0)
				return false;
		for (int i = (_size-1)*sizeof(_uint); i < CN; i++)
			if (at(i))
				return false;
		return true;
	}

	void set(int i, bool f) {
		int id = i / sizeof(_uint);
		i = i % sizeof(_uint);
		if (f)
			_a[id] |= (1 << i);
		else
			_a[id] &= ~(1 << i);
	}

	bool at(int i) {
		int id = i / sizeof(_uint);
		i = i % sizeof(_uint);
		return !!(_a[id] & (1 << i));
	}

	MySet<CN> intersect(const MySet<CN>& s2) {
		MySet<CN> res;
		for (int i = 0; i < _size; i++)
			res._a[i] = _a[i] & s2._a[i];
		return res;
	}

	MySet<CN> inverse() {
		MySet<CN> res;
		for (int i = 0; i < _size; i++)
			res._a[i] = ~_a[i];
		return res;
	}
};

#define FI 10000

int main() {
	//freopen("in.txt", "r", stdin);
	MySet<FI> Inverts[100];
	int N, M, c, ci;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &c);
		while (c--) {
			scanf("%d", &ci);
			Inverts[i].set(ci-1, true);
		}
	}

	scanf("%d", &M);
	while (M--) {
		MySet<FI> res(true);
		for (int i = 0; i < N; i++) {
			int j;
			scanf("%d", &j);
			if (j == 1)
				res = res.intersect(Inverts[i]);
			else if (j == -1)
				res = res.intersect(Inverts[i].inverse());
		}

		if (res.none())
			printf("NOT FOUND\n");
		else {
			for (int i = 0; i < FI; i++)
				if (res.at(i))
					printf("%d ", i+1);
			printf("\n");
		}
	}
	return 0;
}
