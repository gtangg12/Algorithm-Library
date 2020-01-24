/**
   Articulation Points, Bridges, and Biconnected Components
 */
#include "header.h"

#define MAXN 262144

int N, M;
vi adj[MAXN];

// bcc
int ent[MAXN], low[MAXN], t = 0;
stack<pi> stk;

int bcc_num = 0;
vi art; vpi bri;
vi bcc[MAXN];

void dfs(int n, int p = -1) {
	ent[n] = low[n] = t++;
	bool ap = false;
	int num_c = 0;
	for (int c: adj[n]) {
		if (c == p) continue;
		if (ent[c] == -1) {
			stk.emplace(n, c);
			num_c++;
			dfs(c, n);
			low[n] = min(low[n], low[c]);
			if (low[c] >= ent[n]) {
				if (p != -1 || p == -1 && num_c > 1)
					ap = true;
				if (low[c] > ent[n])
					bri.pb({n, c});
				int a, b;
				do {
					auto e = stk.top();
					stk.pop();
					a = e.f, b = e.s;
					if (bcc[a].empty() || bcc[a].back() != bcc_num)
						bcc[a].pb(bcc_num);
					if (bcc[b].empty() || bcc[b].back() != bcc_num)
						bcc[b].pb(bcc_num);
				} while(a != n && b != c);
				bcc_num++;
			}
		}
		else if (ent[c] < low[n]) {
			stk.emplace(n, c);
			low[n] = ent[c];
		}
	}
	if (ap) art.pb(n);
}

void tarjan_bcc() {
	fill(ent, ent+MAXN, -1);
	fill(low, low+MAXN, -1);
	for (int i = 1; i <= N; i++)
		if (ent[i] == -1) dfs(i);
}

bool biconnected(int u, int v) {
	for (int c: bcc[u])
		if (binary_search(be(bcc[v]), en(bcc[v]), c))
			return true;
	return false;
}

int main() {
	tarjan_bcc();
}
