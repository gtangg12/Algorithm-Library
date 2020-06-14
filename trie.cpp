// Trie

#include "header.h"

const int MAXN = 262144;

int cur = 0;
int val[MAXN];
vector<int> adj[MAXN];

void insert(string &s, int n = 0, int d = 0) {
	if (d == sz(s))
		return;
	for (int c : adj[n])
		if (val[c] == s[d]) {
			insert(s, c, d + 1);
			return;
		}
	adj[n].pb(++cur);
	val[cur] = s[d];
	insert(s, cur, d + 1);
}

bool search(string &s, int n = 0, int d = 0) {
	if (d == sz(s))
		return true;
	for (int c : adj[n])
		if (val[c] == s[d])
			return search(s, c, d + 1);
	return false;
}

int main() {
	memset(val, -1, sizeof val);

}
