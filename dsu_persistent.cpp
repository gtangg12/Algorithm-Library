/**
   Persistent Disjoint Set Union via union by rank
 */
#include "header.h"

#define MAXN 262144

pi par[MAXN]; // (time, par)
vpi sz[MAXN];

int find(int v, int t) {
    if (par[v].f > t || par[v].s == -1)
        return v;
    return find(par[v].s, t);
}

void unite(int u, int v, int t) { // monotonic increasing t
    int ur = find(u, t);
    int vr = find(v, t);
    if (ur == vr)
		return;
    int ur_sz = sz[ur].back().s;
    int vr_sz = sz[vr].back().s;
    if (ur_sz < vr_sz) {
        par[ur] = mp(t, vr);
        sz[vr].pb(mp(t, ur_sz+vr_sz));
    }
    else {
        par[vr] = mp(t, ur);
        sz[ur].pb(mp(t, ur_sz+vr_sz));
    }
}

int size_at(int u, int t) {
    int ur = find(u, t);
    return prev(ub(be(sz[ur]), en(sz[ur]), mp(t, INF)))->s;
}

int main() {
    fill(par, par+MAXN, mp(-1, -1));
    fill(sz, sz+MAXN, vpi(1, mp(-1, 1)));
}
