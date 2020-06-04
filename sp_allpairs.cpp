// Floyd-Warshall

#include "header.h"

const int MAXN = 256;

int N, M;
vpi adj[MAXN];
int dis[MAXN][MAXN];
int par[MAXN][MAXN];

void floyd_warshall() {
	for (int i = 0; i < MAXN; i++) {
		fill(dis[i], dis[i] + MAXN, INF);
		fill(par[i], par[i] + MAXN, i);
	}
	for (int i = 1; i <= N; i++) {
		for (pi e: adj[i])
			dis[i][e.f] = min(e.s, dis[i][e.f]);
		dis[i][i] = 0;
	}
	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (dis[i][k] != INF && dis[k][j] != INF && dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
					par[i][j] = par[k][j];
				}
	for (int i = 1; i <= N; i++) // negative cycles
		for (int j = 1; j <= N; j++)
			for (int k = 1; k <= N; k++)
				if (dis[i][k] != INF && dis[k][j] != INF && dis[k][k] < 0)
					dis[i][j] = -INF;
}

int main() {

}
