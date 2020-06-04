// Lowest Common Ancestor via binary lifting

#include "header.h"

const int MAXN = 262144;
const int LOGN = 18;

int N;
vi adj[MAXN];
int par[MAXN];
int dep[MAXN];
int stb[MAXN][LOGN];

void dfs(int n, int p = -1) {
	par[n] = p;
	dep[n] = dep[p] + 1;
	for (int c: adj[n]) if (c != p)
		dfs(c, n);
}

int lca(int u, int v) {
	if (dep[u] < dep[v])
		swap(u, v);
	int dis = dep[u] - dep[v];
	while(dis > 0) {
		int inc = log2(dis);
		u = stb[u][inc];
		dis -= (1 << inc);
	}
	if (u == v)
		return u;
	for (int i = LOGN - 1; i >= 0; i--)
		if (stb[u][i] != -1 && stb[u][i] != stb[v][i]) {
			u = stb[u][i];
			v = stb[v][i];
		}
	return par[u];
}

void build() {
	memset(stb, -1, sizeof stb);
	dep[1] = 0;
	dfs(1);
	for (int i = 1; i < MAXN; i++)
		stb[i][0] = par[i];
	for (int j = 1; (1 << j) < MAXN; j++)
		for (int i = 1; i < MAXN; i++)
			if (stb[i][j - 1] != -1)
				stb[i][j] = stb[stb[i][j - 1]][j - 1];
}

int main() {
	build();
}
