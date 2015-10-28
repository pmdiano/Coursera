//+-----------------------------------------------------------------------------
//
//  File:       InvertIndex.cpp
//
//  Synopsis:   Inverted Index
//              https://www.coursera.org/learn/gaoji-shuju-jiegou/programming
//               /JFMM4/bian-cheng-zuo-ye-suo-yin-2ti
//
//  Author:     Qirong Ma, 10/27/2015
//
//------------------------------------------------------------------------------
#include <map>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

typedef map<string, vector<int> > InvertIndex;

int main() {
	int N, M, c, fid = 1;
	char word[260];
	InvertIndex iidx;

	scanf("%d", &N);
	while (N--) {
		scanf("%d", &c);
		while (c--) {
			scanf("%s", word);
			if (iidx[string(word)].empty()
				|| *(iidx[string(word)].end() - 1) != fid)
				iidx[string(word)].push_back(fid);
		}
		fid++;
	}

	scanf("%d", &M);
	while (M--) {
		scanf("%s", word);
		if (iidx.find(string(word)) == iidx.end())
			printf("NOT FOUND\n");
		else {
			vector<int>& vec = iidx[string(word)];
			vector<int>::iterator it = vec.begin();
			while (it != vec.end())
				printf("%d ", *it++);
			printf("\n");
		}
	}

	return 0;
}
