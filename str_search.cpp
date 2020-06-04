// String Searching

#include "header.h"

const int MAXN = 1048576;

int A[MAXN];

// Z-Algorithm
void z_function(string &s) {
	int li = 0, ri = 0, n = sz(s);
	for (int i = 1; i < n; i++) {
		if (i <= ri)
			A[i] = min(ri - i + 1, A[i - li]);
		while(i + A[i] < n && s[A[i]] == s[i + A[i]])
			A[i]++;
		if (i + A[i] - 1 > ri)
			li = i, ri = i + A[i] - 1;
	}
}

vi z_algorithm(string &s, string &t) {
	vi occ;
	string r = s + '$' + t;
	z_function(r);
	int p = sz(s);
	for (int i = 0; i < sz(t); i++)
		if (A[i + p + 1] == p)
			occ.pb(i);
	return occ;
}

// Knuth Morris Pratt
void p_function(string &s) {
	int n = sz(s), j;
	A[0] = 0;
	for (int i = 1; i < n; i++) {
		j = A[i - 1];
		while (j > 0 && s[i] != s[j])
			j = A[j - 1];
		if (s[i] == s[j])
			j++;
		A[i] = j;
	}
}

vi kmp(string &s, string &t) {
	vi occ;
	string r = s + '$' + t;
	p_function(r);
	int p = sz(s);
	for (int i = p + 1; i < sz(r); i++)
		if (A[i] == p)
			occ.pb(i - 2 * p);
	return occ;
}

int main() {

}
