/**
    Euler Tour on connected graph
 */
#include "header.h"

#define MAXN 262144

int N, M;
vpi adj[MAXN]; // dest, edge id

// euler tour
vi tour;
int cur[MAXN];
bool vis[MAXN];

void dfs(int n) {
	while (cur[n] != sz(adj[n])) {
		if (vis[adj[n][cur[n]].s]) {
			cur[n]++;
			continue;
		}
		auto e = adj[n][cur[n]++];
		vis[e.s] = true;
		dfs(e.f);
	}
	tour.pb(n);
}

void euler_tour() {
	fill(cur, cur+MAXN, 0);
	vi odd;
	for (int i = 1; i <= N; i++)
		if (sz(adj[i])%2 != 0)
			odd.pb(i);
	if (sz(odd) == 2) // tour
		dfs(min(odd[0], odd[1]));
	else if (sz(odd) == 0) // cycle
		dfs(1);
}

int main() {

}
