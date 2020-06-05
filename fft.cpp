// Fast Fourier Transform and Polynomial Multiplication

#include "header.h"

typedef complex<double> cd;

const int MAXN = 262144;

void fft(vector<cd> &fa, bool inv) {
	int n = sz(fa);
	int invert = inv ? -1 : 1;
	int j = 0;
	for (int i = 1; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;
		if (i < j) swap(fa[i], fa[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		double a = 2 * M_PI / len * invert;
		cd wm(cos(a), sin(a));
		for (int i = 0; i < n; i += len) {
			cd w(1);
			for (int j = 0; j < len / 2; j++) {
				cd u = fa[i + j];
				cd v = fa[i + j + len / 2] * w;
				fa[i + j] = u + v;
				fa[i + j + len / 2] = u - v;
				w *= wm;
			}
		}
	}
	if (inv) for (cd &x : fa) {
		x /= n;
	}
}

vi mult(vi &ca, vi &cb) {
	vector<cd> fa(all(ca));
	vector<cd> fb(all(cb));
	int n = 1;
	while (n < sz(ca) + sz(cb))
		n <<= 1;
	fa.resize(n);
	fb.resize(n);
	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < n; i++)
		fa[i] *= fb[i];
	fft(fa, true);
	vi res(n);
	for (int i = 0; i < n; i++)
		res[i] = round(fa[i].real());
	return res;
}

int main() {

}
