// Fast Fourier Transform and Polynomial Multiplication

#include "header.h"

typedef complex<double> cd;

#define MAXN 262144

void fft(vector<cd> &a, bool inv) {
	int n = sz(a);
	int invert = inv ? -1 : 1;
	int j = 0;
	for (int i = 1; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;
		if (i < j)
			swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * M_PI / len * invert;
		cd wm(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			cd w(1);
			for (int j = 0; j < len / 2; j++) {
				cd u = a[i + j];
				cd v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wm;
			}
		}
	}
	if (inv)
		for (cd &x : a)
			x /= n;
}

vi mult(vi &a, vi &b) {
	vector<cd> fa(be(a), en(a)), fb(be(b), en(b));
	int n = 1;
	while (n < sz(a) + sz(b))
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
