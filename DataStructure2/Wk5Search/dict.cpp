//+-----------------------------------------------------------------------------
//
//  File:       dict.h
//
//  Synopsis:   Simple dictionary using ELF hash function (a.k.a. PJW hash)
//              https://www.coursera.org/learn/gaoji-shuju-jiegou/programming
//               /IfU8I/bian-cheng-zuo-ye-jian-suo-3ti
//
//  Author:     Qirong Ma, 10/25/2015
//
//------------------------------------------------------------------------------
#include <cstdio>
#include <cstring>

const int HSIZE = 300001;
const int EMPTY = -1;
int htable[HSIZE];
char English[100000][11];
char Foreign[100000][11];

int hash(char *key) {
	unsigned long h = 0;
	while (*key) {
		h = (h << 4) + *key++;
		unsigned long g = h & 0xF0000000L;
		if (g) h ^= g >> 24;
		h &= ~g;
	}
	return h % HSIZE;
}

void init() {
	for (int i = 0; i < HSIZE; i++)
		htable[i] = EMPTY;
}

void insert(int n) {
	int h0 = hash(Foreign[n]);
	int i = 1, h = h0;
	while (htable[h%HSIZE] != EMPTY) {
		if (i%2)
			h = h0 + (i+1)*(i+1)/4;
		else
			h = h0 - i*i/4;
		i++;
	}
	htable[h%HSIZE] = n;
}

int search(char* key) {
	int h0 = hash(key);
	int i = 1, h = h0;
	while (htable[h%HSIZE] != EMPTY) {
		if (!strcmp(key, Foreign[htable[h%HSIZE]]))
			return htable[h%HSIZE];
		if (i%2)
			h = h0 + (i+1)*(i+1)/4;
		else
			h = h0 - i*i/4;
		i++;
	}
	return -1;
}

int main() {
	char c, word[11];
	int n = 0, id;
	init();

	while (true) {
		c = getchar();
		if (c == '\n') break;
		English[n][0] = c;
		scanf("%s %s", English[n]+1, Foreign[n]);
		insert(n);
		getchar();
		n++;
	}

	while (scanf("%s", word) != EOF) {
		id = search(word);
		if (id != -1)
			printf("%s\n", English[id]);
		else
			printf("eh\n"); 
	}

	return 0;
}
