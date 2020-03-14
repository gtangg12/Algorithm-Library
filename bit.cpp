// Binary Index Tree

#include "header.h"

#define MAXN 262144

int bit[MAXN];

int range_sum(int i) {
	int sum = 0;
	for (; i >= 0; i = (i & (i + 1)) - 1)
		sum += bit[i];
	return sum;
}

void point_upd(int i, int v) {
	for (; i < MAXN; i = i | (i + 1))
		bit[i] += v;
}

int main() {
	fill(bit, bit + MAXN, 0);
}
