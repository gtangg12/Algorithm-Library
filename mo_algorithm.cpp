// Mo's Algorithm for range mode

#include "header.h"

#define MAXN 262144

int A[MAXN], ans[MAXN];
int BLOCK, cans = 0, li = 0, ri = -1;

bool cmp(array<int, 3> a, array<int, 3> b) {
	if (a[0] / BLOCK != b[0] / BLOCK)
		return a[0] < b[0];
	return a[1] < b[1];
}

int occ[MAXN], cnt[MAXN];

void update(int i, int v) {
	int x = A[i];
	cnt[occ[x]]--;
	occ[x] += v;
	cnt[occ[x]]++;
	while (cnt[cans + 1] > 0)
		cans++;
	while (cans > 0 && cnt[cans] == 0)
		cans--;
}

int range_mode(int l, int r) {
	while (li > l)
		update(--li, 1);
	while (ri < r)
		update(++ri, 1);
	while (li < l)
		update(li++, -1);
	while (ri > r)
		update(ri--, -1);
	return cans;
}

void mo(int n, vector<array<int, 3> > &vq) {
	fill(occ, occ + MAXN, 0);
	fill(cnt, cnt + MAXN, 0);
	BLOCK = sqrt(n);
	sort(be(vq), en(vq), cmp);
	for (array<int, 3> q: vq)
		ans[q[0]] = range_mode(q[1], q[2]);
}

int main() {
	int N;
	vector<array<int, 3> > vq; // idx, l, r
	mo(N, vq);
}
