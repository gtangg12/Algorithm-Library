// Dijkstra's, Bellman Ford, Shortest Path Faster Algorithm

#include "header.h"

#define MAXN 262144

int N, M;
vpi adj[MAXN];
int dis[MAXN], par[MAXN];

void dijkstra(int v) {
	priority_queue<pi, vpi, greater<pi> > pq;
	dis[v] = 0;
	pq.push({0, v});
	while (sz(pq) > 0) {
		int cur_dis = pq.top().f;
		int cur = pq.top().s;
		pq.pop();
		if (cur_dis > dis[cur])
			continue;
		for (auto e: adj[cur]) {
			int nxt = e.f;
			if (dis[cur] + e.s < dis[nxt]) {
				dis[nxt] = dis[cur] + e.s;
				par[nxt] = cur;
				pq.emplace(dis[nxt], nxt);
			}
		}
	}
}

void bellman_ford(int v) {
	dis[v] = 0;
	for (int i = 0; i < N - 1; i++)
		for (int j = 1; j <= N; j++) {
			if (dis[j] == INF) continue;
			for (pi e: adj[j])
				if (dis[j] + e.s < dis[e.f]) {
					dis[e.f] = dis[j] + e.s;
					par[e.f] = j;
				}
		}
	bool cycle = true;
	while (cycle) {
		cycle = false;
		for (int j = 1; j <= N; j++) {
			if (dis[j] == INF) continue;
			for (pi e: adj[j])
				if (dis[e.f] != -INF && dis[j] + e.s < dis[e.f]) {
					dis[e.f] = -INF;
					cycle = true;
				}
		}
	}
}

int cnt[MAXN];
bool inqueue[MAXN];

bool spfa(int v) {
	// O(m) average, O(nm) worst case
	// Can only detect existence of negative cycle
	fill(cnt, cnt + MAXN, 0);
	fill(inqueue, inqueue + MAXN, false);
	queue<int> q;
	dis[v] = 0;
	q.push(v);
	inqueue[v] = true;
	while (sz(q) > 0) {
		int cur = q.front();
		q.pop();
		inqueue[cur] = false;
		for (auto e: adj[cur]) {
			int nxt = e.f;
			if (dis[cur] + e.s < dis[nxt]) {
				dis[nxt] = dis[cur] + e.s;
				par[nxt] = cur;
				if (!inqueue[nxt]) {
					q.push(nxt);
					inqueue[nxt] = true;
					cnt[nxt]++;
					if (cnt[nxt] > N)
						return false;
				}
			}
		}
	}
	return true;
}

int main() {
	fill(dis, dis + MAXN, INF);
	fill(par, par + MAXN, -1);
}
