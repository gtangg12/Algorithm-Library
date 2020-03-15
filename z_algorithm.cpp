// Z-Algorithm

#include "header.h"

#define MAXN 1048576

int Z[MAXN];

void z_function(string &s) {
	int li = 0, ri = 0, n = sz(s);
	for (int i = 1; i < n; i++) {
		if (i <= ri)
			Z[i] = min(ri - i + 1, Z[i - li]);
		while(i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
			Z[i]++;
		if (i + Z[i] - 1 > ri)
			li = i, ri = i + Z[i] - 1;
	}
}

vi z_algorithm(string &s, string &t) {
	vi occ;
	string r = s + '$' + t;
	z_function(r);
	int p = sz(s);
	for (int i = 0; i < sz(t); i++)
		if (Z[i + p + 1] == p)
			occ.pb(i);
	return occ;
}

int main() {

}
