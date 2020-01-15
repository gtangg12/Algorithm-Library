/**
   Segment Tree w/ range sum and point update
 */
#include "header.h"

#define MAXN 262144

int st_sum[4*MAXN];

int range_sum(int l, int r, int li = 0, int ri = MAXN-1, int i = 1) {
	if (ri < l || li > r)
		return 0;
	if (l <= li && ri <= r)
		return st_sum[i];
	int m = (li+ri)/2;
	int ret = range_sum(l, r, li, m, 2*i)+range_sum(l, r, m+1, ri, 2*i+1);
	return ret;
}

void point_upd(int idx, int v, int li = 0, int ri = MAXN-1, int i = 1) {
	if (ri < idx || li > idx)
		return;
	if (li == ri) {
		st_sum[i] = v;
		return;
	}
	int m = (li+ri)/2;
	if (idx <= m)
		point_upd(idx, v, li, m, 2*i);
	else
		point_upd(idx, v, m+1, ri, 2*i+1);
	st_sum[i] = st_sum[2*i]+st_sum[2*i+1];
}

int main() {
	fill(st_sum, st_sum+4*MAXN, 0);
}
