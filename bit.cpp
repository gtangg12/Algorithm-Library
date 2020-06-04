// Binary Index Tree

#include "header.h"

const int MAXN = 262144;
const int LOGN = 18;

int N;
int bit[MAXN];

void point_upd(int i, int v) {
	for (; i < MAXN; i = i | (i + 1))
		bit[i] += v;
}

int range_sum(int i) {
	int sum = 0;
	for (; i >= 0; i = (i & (i + 1)) - 1)
		sum += bit[i];
	return sum;
}

int lower_bound(int v) {
	int sum = 0;
	int pos = 0;
	for (int i = LOGN; i >= 0; i--) {
		int idx = pos + (1 << i) - 1;
		if (idx + 1 < N && sum + bit[idx] < v) {
			sum += bit[idx];
			pos += (1 << i);
		}
	}
	return pos;
}

int main() {
	memset(bit, 0, sizeof bit);
}
