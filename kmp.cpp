// Knuth Morris Pratt

#include "header.h"

#define MAXN 1048576

int P[MAXN];

void p_function(string &s) {
	int n = sz(s), j;
	P[0] = 0;
	for (int i = 1; i < n; i++) {
		j = P[i - 1];
		while (j > 0 && s[i] != s[j])
			j = P[j - 1];
		if (s[i] == s[j])
			j++;
		P[i] = j;
	}
}

vi kmp(string &s, string &t) {
	vi occ;
	string r = s + '$' + t;
	p_function(r);
	int p = sz(s);
	for (int i = p + 1; i < sz(r); i++)
		if (P[i] == p)
			occ.pb(i - 2 * p);
	return occ;
}

int main() {

}
