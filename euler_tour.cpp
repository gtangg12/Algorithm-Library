// Euler Tour on connected graph

#include "header.h"

const int MAXN = 262144;

int N, M;
vpi adj[MAXN]; // dest, edge id

vi tour;
int cur[MAXN];
bool done[MAXN];

void dfs(int n) {
	while (cur[n] != sz(adj[n])) {
		if (done[adj[n][cur[n]].s]) {
			cur[n]++;
			continue;
		}
		auto e = adj[n][cur[n]++];
		done[e.s] = true;
		dfs(e.f);
	}
	tour.pb(n);
}

void euler_tour() {
	vi odd;
	for (int i = 1; i <= N; i++)
		if (sz(adj[i]) % 2 != 0)
			odd.pb(i);
	if (sz(odd) == 2)  // tour w/o cycle
		dfs(min(odd[0], odd[1]));
	else if (sz(odd) == 0)  // cycle
		dfs(1);
}

int main() {
	memset(cur, 0, sizeof cur);
}
