// Centroid Decomposition

#include "header.h"

#define MAXN 262144

int N;
vi adj[MAXN];
int sz[MAXN];
bool vis[MAXN];

int dfs(int n, int p = -1) {
	sz[n] = 1;
	for (int c: adj[n])
		if (c != p && !vis[n])
			sz[n] += dfs(c, n);
	return sz[n];
}

int cpar[MAXN];

int centroid(int n, int s, int p = -1) {
	for (int c: adj[n])
		if (c != p && !vis[c] && sz[c] > s / 2)
			return centroid(c, s, n);
	return n;
}

void decomp(int n, int p = -1) {
	dfs(n);
	int cent = centroid(n, sz[n]);
	vis[cent] = true;
	cpar[cent] = p;
	for (int c: adj[cent])
		if (!vis[c]) decomp(c, cent);
}

void cent_build() {
	fill(vis, vis + MAXN, false);
	fill(cpar, cpar + MAXN, -1);
	decomp(1);
}

int main() {
	cent_build();
}
