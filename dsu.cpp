// Disjoint Set Union

#include "header.h"

const int MAXN = 262144;

int par[MAXN], size[MAXN];

int find(int v) {
	return par[v] == -1 ? v : par[v] = find(par[v]);
}

bool unite(int u, int v) {
	int ur = find(u);
	int vr = find(v);
	if (ur == vr) return false;
	if (size[ur] < size[vr]) swap(ur, vr);
	par[vr] = ur;
	size[ur] += size[vr];
	return true;
}

int main() {
	fill(par, par + MAXN, -1);
	fill(size, size + MAXN, 1);
}
