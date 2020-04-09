// Maxflow via Ford-Fulkerson implemented using Edmonds-Karp: O(VE^2)

#include "header.h"

#define MAXN 1024

int N, M;
vpi adj[MAXN]; // (des, cap)
int res[MAXN][MAXN];
int par[MAXN];

int bfs(int s, int t) {
	fill(par, par + MAXN, -1);

}

int maxflow(int s, int t) {

}

int main() {

}
