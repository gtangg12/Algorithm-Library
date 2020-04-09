// Heavy Light Decomposition

#include "header.h"

#define MAXN 262144

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

int N;
vi val, adj[MAXN];
int par[MAXN], dep[MAXN], sz[MAXN];

int dfs(int n, int p = -1) {
	par[n] = p;
	dep[n] = dep[p] + 1;
	sz[n] = 1;
	for (int c: adj[n])
		if (c != p)
			sz[n] += dfs(c, n);
	return sz[n];
}

int head[MAXN], pos[MAXN];
int cur_pos = 0;

void decomp(int v, int h) {
	head[v] = h;
	pos[v] = cur_pos++;
	int m_sz = 0, heavy = -1;
	for (int c: adj[v])
		if (c != par[v] && sz[c] > m_sz) {
			m_sz = sz[c];
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

void hld_build() {
	fill(st_sum, st_sum + 4 * MAXN, 0);
	fill(lazy, lazy + 4 * MAXN, 0);
	fill(head, head + MAXN, -1);
	fill(pos, pos + MAXN, -1);
	dfs(1);
	decomp(1, 1);
	st_build(val, 0, N - 1);
}

int main() {
	hld_build();
}
