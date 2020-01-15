/**
   Disjoint Set Union via union by rank and path compression
 */
#include "header.h"

#define MAXN 262144

int par[MAXN], sz[MAXN];

int find(int v) {
	if (par[v] == -1)
		return v;
	return par[v] = find(par[v]);
}

void unite(int u, int v) {
	int ur = find(u);
	int vr = find(v);
	if (ur == vr)
		return;
	if (sz[ur] < sz[vr]) {
		par[ur] = vr;
		sz[vr] += sz[ur];
	}
	else {
		par[vr] = ur;
		sz[ur] += sz[vr];
	}
}

int main() {
	fill(par, par+MAXN, -1);
	fill(sz, sz+MAXN, 1);
}
