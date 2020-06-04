// Disjoint Set Union

#include "header.h"

const int MAXN = 262144;

int par[MAXN];
int size[MAXN];

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
	if (size[ur] < size[vr]) {
		par[ur] = vr;
		size[vr] += size[ur];
	}
	else {
		par[vr] = ur;
		size[ur] += size[vr];
	}
}

int main() {
	fill(par, par + MAXN, -1);
	fill(size, size + MAXN, 1);
}
