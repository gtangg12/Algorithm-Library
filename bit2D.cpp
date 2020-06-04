// 2D Binary Index Tree

#include "header.h"

const int MAXN = 1024;

int bit[MAXN][MAXN];

void point_upd(int r, int c, int v) {
	for (int i = r; i < MAXN; i = i | (i + 1))
		for (int j = c; j < MAXN; j = j | (j + 1))
			bit[i][j] += v;
}

int range_sum(int r, int c) {
	int sum = 0;
	for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
		for (int j = c; j >= 0; j = (j & (j + 1)) - 1)
			sum += bit[i][j];
	return sum;
}

int main() {
	memset(bit, 0, sizeof bit);
}
