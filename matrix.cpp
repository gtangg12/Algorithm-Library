// Matrix Operations

#include "header.h"

typedef vector<vd> mat;

const double ERROR = 1e-9;

mat zeros(int n, int m) {
	return mat(n, vd(m));
}

mat id(int n) {
	mat ret = zeros(n, n);
	for (int i = 0; i < n; i++)
		ret[i][i] = 1;
	return ret;
}

mat add(mat &a, mat &b) {
	int n = sz(a), m = sz(a[0]);
	mat ret = zeros(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ret[i][j] = a[i][j] + b[i][j];
	return ret;
}

mat mult(mat &a, mat &b) {
	int n = sz(a), m = sz(a[0]), l = sz(b[0]);
	mat ret = zeros(n, l);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < l; j++)
			for (int k = 0; k < m; k++)
				ret[i][j] += a[i][k] * b[k][j];
	return ret;
}

mat pow(mat &a, int p) {
	int n = sz(a);
	if (p == 0)
		return id(n);
	mat tmp = mult(a, a);
	mat ret = pow(tmp, p >> 1);
	if (p % 2)
		ret = mult(ret, a);
	return ret;
}

int rref(mat &a, vd &sol) {
	// Returns number of solutions
	int n = sz(a), m = sz(a[0]) - 1;
	vi pivot(m, -1);
	for (int r = 0, c = 0; r < n && c < m; c++) {
		int sel = r;
		for (int i = r; i < n; i++)
			if (abs(a[i][c]) > abs(a[sel][c]))
				sel = i;
		if (abs(a[sel][c]) < ERROR)
			continue;
		for (int i = c; i <= m; i++)
			swap(a[sel][i], a[r][i]);
		pivot[c] = r;
		for (int i = 0; i < n; i++) {
			if (i != r) {
				double k = a[i][c] / a[r][c];
				for (int j = c; j <= m; j++)
					a[i][j] -= k * a[r][j];
			}
		}
		r++;
	}
	sol.assign(m, 0);
	for (int i = 0; i < m; i++)
		if (pivot[i] != -1)
			sol[i] = a[pivot[i]][m] / a[pivot[i]][i];
	for (int i = 0; i < n; i++) {
		double sum = 0;
		for (int j = 0; j < m; j++)
			sum += sol[j] * a[i][j];
		if (abs(sum - a[i][m]) > ERROR)
			return 0;
	}
	for (int i = 0; i < m; i++)
		if (pivot[i] == -1)
			return INF;
	return 1;
}

int main() {

}
