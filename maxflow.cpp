// Maxflow via Ford-Fulkerson implemented using Edmonds-Karp: O(VE^2)

#include "header.h"

const int MAXN = 1024;

int N, M;
vpi adj[MAXN]; // (des, cap)
int par[MAXN];
int res[MAXN][MAXN];

int bfs(int s, int t) {
	fill(par, par + MAXN, -1);
	par[s] = -2;
	queue<pi> q;
	q.push({s, INF}); // (node, flow)
	while(!q.empty()) {
		int n = q.front().f;
		int f = q.front().s;
		q.pop();
		for (auto e: adj[n]) {
			int c = e.f;
			if (par[c] == -1 && res[n][c] > 0) {
				par[c] = n;
				int nf = min(f, res[n][c]);
				if (c == t)
					return nf;
				q.push({c, nf});
			}
		}
	}
	return 0;
}

int maxflow(int s, int t) {
	int f = 0;
	int nf;
	while (nf = bfs(s, t)) {
		f += nf;
		int n = t;
		while (n != s) {
			int p = par[n];
			res[p][n] -= nf;
			res[n][p] += nf;
			n = p;
		}
	}
	return f;
}

void addEdge(int u, int v, int c) {
	adj[u].pb({v, c});
	adj[u].pb({u, 0});
	res[u][v] = c;
	res[v][u] = 0;
}

int main() {

}
