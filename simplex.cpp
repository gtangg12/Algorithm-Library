// Simplex Algorithm
//
//     maximize     c^T x
//     subject to   Ax <= b
//                  x >= 0
//
// Input: A -- m x n matrix
//        B -- m-dimensional vector
//        C -- n-dimensional vector
//
// Output: 1 and opt value if solvable, -1 if unbounded

#include "header.h"

typedef vector<vd> mat;

const double EPS = 1e-9;

int M, N;
mat D; vd B, C;
double opt;

int get_pivots(int &rp, int &cp) {
	// Returns 0 if pivots found, 1 if optimal, -1 if unbounded
	int cnt = 0;
	double mn = INF;
	for (int i = 0; i < N + M; i++) {
		cnt += C[i] >= 0;
		if (C[i] < mn) mn = C[i], cp = i;
	}
	if (cnt == N + M)
		return 1;
	cnt = 0, mn = INF;
	for (int i = 0; i < M; i++) {
		cnt += D[i][cp] <= 0;
		if (D[i][cp] > 0) {
			double tmp = B[i] / D[i][cp];
			if (tmp < mn) mn = tmp, rp = i;
		}
	}
	return cnt == M ? -1 : 0;
}

void pivot(int rp, int cp) {
	double p = D[rp][cp];
	double c = C[cp];
	for (int i = 0; i < N + M; i++) {
		D[rp][i] /= p;
		C[i] -= c * D[rp][i];
	}
	B[rp] /= p;
	opt -= c * B[rp];
	for (int i = 0; i < M; i++) {
		if (i == rp) continue;
		p = D[i][cp];
		for (int j = 0; j < N + M; j++)
			D[i][j] -= p * D[rp][j];
		B[i] -= p * B[rp];
	}
}

int simplex() {
	// Returns same code as get_pivots()
	int cnt = 0;
	while (true) {
		int rp, cp;
		int code = get_pivots(rp, cp);
		if (code != 0)
			return code;
		print(D);
		pivot(rp, cp);
	}
}

void init(mat &a, vd &b, vd &c) {
	D = a, B = b, C = c;
	for (int i = 0; i < M; i++) {
		D[i].resize(N + M);
		D[i][N + i] = 1;
	}
	for (int i = 0; i < N; i++)
		C[i] *= -1;
	C.resize(N + M);
}

int main() {

}
