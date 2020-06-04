// Persistent Disjoint Set Union

#include "header.h"

const int MAXN = 262144;

pi par[MAXN]; // time, par
vpi size[MAXN];

int find(int v, int t) {
	if (par[v].f > t || par[v].s == -1)
		return v;
	return find(par[v].s, t);
}

void unite(int u, int v, int t) {
	// query in monotonic increasing t
	int ur = find(u, t);
	int vr = find(v, t);
	if (ur == vr)
		return;
	int ur_size = size[ur].back().s;
	int vr_size = size[vr].back().s;
	if (ur_size < vr_size) {
		par[ur] = mp(t, vr);
		size[vr].pb(mp(t, ur_size + vr_size));
	}
	else {
		par[vr] = mp(t, ur);
		size[ur].pb(mp(t, ur_size + vr_size));
	}
}

int size_at(int u, int t) {
	int ur = find(u, t);
	return prev(ub(all(size[ur]), mp(t, INF)))->s;
}

int main() {
	fill(par, par + MAXN, mp(-1, -1));
	fill(size, size + MAXN, vpi(1, mp(-1, 1)));
}
