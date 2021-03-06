// Polynomial Rolling Hash and Robin-Karp

#include "header.h"

const int BASE = 31;
const int MOD = 10e9 + 7;

ll get_hash(string &s) {
	ll v = 0, p = 1;
	for (char c: s) {
		v = (v + (c - 'a' + 1) * p) % MOD;
		p = (p * BASE) % MOD;
	}
	return v;
}

struct s_hash {
	int n;
	vector<ll> A, P;

	s_hash(string &s) {
		n = sz(s);
		A.resize(n + 1);
		P.resize(n + 1);
		A[0] = 0, P[0] = 1;
		for (int i = 0; i < n; i++) {
			A[i + 1] = (A[i] + (s[i] - 'a' + 1) * P[i]) % MOD;
			P[i + 1] = (P[i] * BASE) % MOD;
		}
	}

	ll get_hash(int l, int r) {
		return (A[r + 1] - A[l] + MOD) % MOD;
	}
};

bool compare(s_hash &s1, s_hash &s2, int a, int b, int c, int d) {
	// Returns if s1[a, b] equals s2[c, d]
	vector<ll> &P = s1.n > s2.n ? s1.P : s2.P;
	ll v1 = s1.get_hash(a, b);
	ll v2 = s2.get_hash(c, d);
	if (a > c)
		v2 *= P[a - c];
	else
		v1 *= P[c - a];
	v1 %= MOD;
	v2 %= MOD;
	return v1 == v2;
}

vi robin_karp(string &s, string &t) {
	vi occ;
	int S = sz(s), T = sz(t);
	s_hash sh(s);
	ll h = get_hash(t), ch;
	for (int i = 0; i + T - 1 < S; i++) {
		ch = sh.get_hash(i, i + T - 1);
		if (ch == h * sh.P[i] % MOD)
			occ.pb(i);
	}
	return occ;
}

int main() {

}
