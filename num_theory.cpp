// Number theory implementations

#include "header.h"

const int MOD = 10e9 + 7;

namespace mod {

ll operator + (const ll p, const ll q) { return (p + q) % MOD; }
ll operator - (const ll p, const ll q) { return (p - q + MOD) % MOD; }
ll operator * (const ll p, const ll q) { return (p * q) % MOD; }

}

// using namespace mod;

int gcd(int a, int b) {
	while (b) {
		int t = a % b;
        a = b, b = t;
	}
    return a;
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int pow(int a, int b) {
	int ret = 1;
	while (b) {
		if (b & 1) ret = ret * a;
		a = a * a;
		b >>= 1;
	}
	return ret;
}

int mod_inv(int a, int m) {

}

int extended_euclid(int a, int b) {

}

vi modular_linear_equation_solver(int a, int b, int n) {

}

pi chinese_remainder_theorem(int m1, int r1, int m2, int r2) {

}

pi chinese_remainder_theorem(vi &m, vi &r) {

}

bool linear_diophantine(int a, int b, int c, int &x, int &y) {

}

vi factors(int a) {

}

vi prime_factorization(int a) {

}

int main() {

}
