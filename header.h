#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<double, double> pd;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<pi> vpi;
typedef vector<pd> vpd;

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define be(x) x.begin()
#define en(x) x.end()
#define all(x) x.begin(), x.end()

const int INF = INT_MAX;

// Link file I/O to cin/cout
#define SET_IO(name) \
	ios_base::sync_with_stdio(0); \
	cin.tie(0); \
	freopen((name + ".in").c_str(), "r", stdin); \
	freopen((name + ".out").c_str(), "w", stdout) \

// Multiple test cases from cin/cout
#define MULTIPLE_TESTS \
	int num_tests; \
	cin >> num_tests; \
	for (int cur_test = 0; cur_test < num_tests; cur_test++)

// =============== Customs Libraries ===============

namespace bitmath {
// add l for long, ll for long long
#define popcnt __builtin_popcount
#define onepar __builtin_parity
#define lzero __builtin_clz
#define tzero __builtin_ctz
#define lsb(x) (x == 0 ? -1 : tzero(x))
#define msb(x) (x == 0 ? -1 : sizeof(x) * 8 - lzero(x) - 1)
#define onebit(x) ((x & (x - 1)) == 0)
}
