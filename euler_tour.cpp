/*
   ID: gtangg11
   LANG: C++11
   TASK: fence
 */

/**
    Euler Tour on connected graph
 */
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<pi> vpi;
typedef vector<pd> vpd;

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define be(x) x.begin()
#define en(x) x.end()
#define sz(x) (int)x.size()

#define INF INT_MAX
#define MAXN 262144

int N, M;
vpi adj[MAXN]; // dest, edge id

// euler tour
vi tour;
int cur[MAXN];
bool vis[MAXN];

void dfs(int n) {
	while (cur[n] != sz(adj[n])) {
		if (vis[adj[n][cur[n]].s]) {
			cur[n]++;
			continue;
		}
		auto e = adj[n][cur[n]++];
		vis[e.s] = true;
		dfs(e.f);
	}
	tour.pb(n);
}

void euler_tour(int s) {
	fill(cur, cur+MAXN, 0);
	vi odd;
	for (int i = 1; i <= 500; i++)
		if (sz(adj[i])%2 != 0)
			odd.pb(i);
	if (sz(odd) == 2)     // tour
		dfs(min(odd[0], odd[1]));
	else if (sz(odd) == 0)     // cycle
		dfs(s);
}

int main() {

}
