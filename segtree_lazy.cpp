// Lazy Segment Tree

#include "header.h"

const int MAXN = 262144;

int st_sum[4 * MAXN], lazy[4 * MAXN];

void pull(int i) {
	st_sum[i] = st_sum[2 * i] + st_sum[2 * i + 1];
}

void push(int i, int li, int ri) {
	st_sum[i] += (ri - li + 1) * lazy[i];
	if (li != ri) {
		lazy[2 * i] += lazy[i];
		lazy[2 * i + 1] += lazy[i];
	}
	lazy[i] = 0;
}

int range_sum(int l, int r, int li = 0, int ri = MAXN - 1, int i = 1) {
	push(i, li, ri);
	if (ri < l || li > r)
		return 0;
	if (l <= li && ri <= r)
		return st_sum[i];
	int m = (li + ri) / 2;
	int ret = range_sum(l, r, li, m, 2 * i) + range_sum(l, r, m + 1, ri, 2 * i + 1);
	pull(i);
	return ret;
}

void range_add(int l, int r, int v, int li = 0, int ri = MAXN - 1, int i = 1) {
	push(i, li, ri);
	if (ri < l || li > r)
		return;
	if (l <= li && ri <= r) {
		lazy[i] += v;
		push(i, li, ri);
		return;
	}
	int m = (li + ri) / 2;
	range_add(l, r, v, li, m, 2 * i);
	range_add(l, r, v, m + 1, ri, 2 * i + 1);
	pull(i);
}

int main() {
	memset(st_sum, 0, sizeof st_sum);
	memset(lazy, 0, sizeof lazy);
}
