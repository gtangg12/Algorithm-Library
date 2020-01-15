/**
   Dijkstra's with path reconstruction

   Bellman-Ford with path reconstruction. Distances to nodes in negative cycles
   are set to -INF.
 */
#include "header.h"

#define MAXN 262144

int N, M;
vpi adj[MAXN];
int dis[MAXN], par[MAXN];

void dijkstra(int v) {
	fill(dis, dis+MAXN, INF);
	fill(par, par+MAXN, -1);
	vb vis(N+1, false);
	priority_queue<pi, vpi, greater<pi> > pq;
	dis[v] = 0;
	pq.push({0, v});
	int cur, nxt, new_dis;
	while(sz(pq) > 0) {
		cur = pq.top().s;
		pq.pop();
		vis[cur] = true;
		for (pi e: adj[cur]) {
			nxt = e.f;
			new_dis = dis[cur]+e.s;
			if (!vis[nxt] && new_dis < dis[nxt]) {
				dis[nxt] = new_dis;
				pq.emplace(new_dis, nxt);
				par[nxt] = cur;
			}
		}
	}
}

void bellman_ford(int v) {
	fill(dis, dis+MAXN, INF);
	fill(par, par+MAXN, -1);
	dis[v] = 0;
	for (int i = 0; i < N-1; i++)
		for (int j = 1; j <= N; j++) {
			if (dis[j] == INF) continue;
			for (pi e: adj[j])
				if (dis[j]+e.s < dis[e.f]) {
					dis[e.f] = dis[j]+e.s;
					par[e.f] = j;
				}
		}
	bool cycle = true; // negative cycles
	while(cycle) {
		cycle = false;
		for (int j = 1; j <= N; j++) {
			if (dis[j] == INF) continue;
			for (pi e: adj[j])
				if (dis[e.f] != -INF && dis[j]+e.s < dis[e.f]) {
					dis[e.f] = -INF;
					cycle = true;
				}
		}
	}
}

int main() {

}
