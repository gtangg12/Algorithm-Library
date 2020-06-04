// Centroid Decomposition

#include "header.h"

const int MAXN = 262144;

vi adj[MAXN];

int size[MAXN];
int cpar[MAXN];
bool done[MAXN];

int dfs(int n, int p = -1) {
	size[n] = 1;
	for (int c : adj[n])
		if (c != p && !done[n])
			size[n] += dfs(c, n);
	return size[n];
}

int centroid(int n, int s, int p = -1) {
	for (int c : adj[n])
		if (c != p && !done[c] && size[c] > s / 2)
			return centroid(c, s, n);
	return n;
}

void decomp(int n, int p = -1) {
	dfs(n);
	int cent = centroid(n, size[n]);
	done[cent] = true;
	cpar[cent] = p;
	for (int c : adj[cent])
		if (!done[c])
			decomp(c, cent);
}

void build() {
	memset(done, 0, sizeof done);
	memset(cpar, -1, sizeof cpar);
	decomp(1);
}

int main() {
	build();
}
