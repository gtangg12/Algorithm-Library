// Strongly Connected Components and Condensation DAG

#include "header.h"

const int MAXN = 262144;

int N, M;
vi adj[MAXN];

int ent[MAXN];
int low[MAXN];
int t = 0;
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
	memset(ent, -1, sizeof ent);
	memset(low, -1, sizeof low);
	for (int i = 1; i <= N; i++) {
		if (ent[i] == -1)
			dfs(i);
	}
}

vi dag[MAXN];
int size[MAXN];

void condense() {
	fill(size, size + scc_num, 0);
	for (int i = 1; i <= N; i++)
		size[scc[i]]++;
	for (int i = 1; i <= N; i++) {
		for (int c: adj[i])
			if (scc[i] != scc[c])
				dag[scc[i]].pb(scc[c]);
	}
}

int main() {
	tarjan_scc();
	condense();
}
