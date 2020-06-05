// Heavy Light Decomposition

#include "header.h"

const int MAXN = 262144;

// Auxiliary Lazy Segment Tree
int st_sum[4 * MAXN];
int lazy[4 * MAXN];

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

void st_build(vi &v, int li, int ri, int i = 1) {
	if (li == ri)
		st_sum[i] = v[li];
	else {
		int m = (li + ri) / 2;
		st_build(v, li, m, 2 * i);
		st_build(v, m + 1, ri, 2 * i + 1);
		pull(i);
	}
}

// Decomposition
int N;
vi val;
vi adj[MAXN];

int par[MAXN];
int dep[MAXN];
int size[MAXN];

int dfs(int n, int p = -1) {
	par[n] = p;
	dep[n] = dep[p] + 1;
	size[n] = 1;
	for (int c: adj[n])
		if (c != p)
			size[n] += dfs(c, n);
	return size[n];
}

int pos[MAXN];
int head[MAXN];
int cur_pos = 0;

void decomp(int v, int h) {
	head[v] = h;
	pos[v] = cur_pos++;
	int m_size = 0;
	int heavy = -1;
	for (int c: adj[v])
		if (c != par[v] && size[c] > m_size) {
			m_size = size[c];
			heavy = c;
		}
	if (heavy != -1)
		decomp(heavy, h);
	for (int c: adj[v])
		if (c != par[v] && c != heavy)
			decomp(c, c);
}

int path_sum(int u, int v) {
	int ret = 0;
	for (; head[u] != head[v]; v = par[head[v]]) {
		if (dep[head[u]] > dep[head[v]])
			swap(u, v);
		ret += range_sum(pos[head[v]], pos[v]);
	}
	if (dep[u] > dep[v])
		swap(u, v);
	ret += range_sum(pos[u], pos[v]);
	return ret;
}

void path_add(int u, int v, int c) {
	for (; head[u] != head[v]; v = par[head[v]]) {
		if (dep[head[u]] > dep[head[v]])
			swap(u, v);
		range_add(pos[head[v]], pos[v], c);
	}
	if (dep[u] > dep[v])
		swap(u, v);
	range_add(pos[u], pos[v], c);
}

void build() {
	memset(st_sum, 0, sizeof st_sum);
	memset(lazy, 0, sizeof lazy);
	memset(head, -1, sizeof head);
	memset(pos, -1, sizeof pos);
	dfs(1);
	decomp(1, 1);
	st_build(val, 0, N - 1);
}

int main() {
	build();
}
