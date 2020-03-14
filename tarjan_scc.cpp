// Strongly Connected Components and Condensation DAG

#include "header.h"

#define MAXN 262144

int N, M;
vi adj[MAXN];

int ent[MAXN], low[MAXN], t = 0;
bool on_stk[MAXN];
stack<int> stk;

int scc_num = 0;
int scc[MAXN];

void dfs(int n) {
	ent[n] = low[n] = t++;
	stk.push(n);
	on_stk[n] = true;
	for (int c: adj[n]) {
		if (ent[c] == -1) {
			dfs(c);
			low[n] = min(low[n], low[c]);
		}
		else if (on_stk[c])
			low[n] = min(low[n], ent[c]);
	}
	if (low[n] == ent[n]) {
		int v;
		do {
			v = stk.top();
			stk.pop();
			scc[v] = scc_num;
			on_stk[v] = false;
		} while (v != n);
		scc_num++;
	}
}

void tarjan_scc() {
	fill(ent, ent + MAXN, -1);
	fill(low, low + MAXN, -1);
	for (int i = 1; i <= N; i++)
		if (ent[i] == -1) dfs(i);
}

vi dag[MAXN];
int scc_sz[MAXN];

void dag_scc() {
	fill(scc_sz, scc_sz + scc_num, 0);
	for (int i = 1; i <= N; i++)
		scc_sz[scc[i]]++;
	for (int i = 1; i <= N; i++)
		for (int c: adj[i])
			if (scc[i] != scc[c])
				dag[scc[i]].pb(scc[c]);
}

int main() {
	tarjan_scc();
	dag_scc();
}
