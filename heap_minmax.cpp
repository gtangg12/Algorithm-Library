// Min-Max Heap
//
// Double ended priority queue

#include "header.h"

using namespace bitmath;

#define func_bii function<bool(int, int)>
#define push_min(x) push(x, less<int>())
#define push_max(x) push(x, greater<int>())
#define pull_min(x) pull(x, less<int>())
#define pull_max(x) pull(x, greater<int>())

const int NONE = INF;
const int MAXN = 262144;

int A[MAXN], size = 0;

int c[6] = {2, 2, 4, 4, 4, 4};
int a[6] = {0, 1, 0, 1, 2, 3};

int m_node(int i, func_bii cmp) {
	int v = msb(i) % 2 ? -INF : INF;
	int m;
	for (int j = 0; j < 6; j++) {
		int idx = c[j] * i + a[j];
		if (A[idx] == NONE)
			continue;
		if (cmp(A[idx], v)) {
			v = A[idx];
			m = idx;
		}
	}
	return m;
}

void push(int i, func_bii cmp) {
	while (A[2 * i] != NONE || A[2 * i + 1] != NONE) {
		int m = m_node(i, cmp);
		if (m > 2 * i + 1) {
			if (cmp(A[m], A[i])) {
				swap(A[m], A[i]);
				if (cmp(A[m / 2], A[m]))
					swap(A[m], A[m / 2]);
			}
		}
		else if (cmp(A[m], A[i]))
			swap(A[m], A[i]);
		else
			break;
		i = m;
	}
}

void pull(int i, func_bii cmp) {
	while (i / 4 > 0 && cmp(A[i], A[i / 4])) {
		swap(A[i], A[i / 4]);
		i /= 4;
	}
}

void insert(int x) {
	A[++size] = x;
	if (size == 1)
		return;
	int dep = msb(size);
	if (dep % 2) { // mx level
		if (A[size] < A[size / 2]) {
			swap(A[size], A[size / 2]);
			pull_min(size / 2);
		}
		else
			pull_max(size);
	}
	else { // mn level
		if (A[size] > A[size / 2]) {
			swap(A[size], A[size / 2]);
			pull_max(size / 2);
		}
		else
			pull_min(size);
	}
}

int peek_min() {
	return A[1];
}

int peek_max() {
	if (size == 1)
		return A[1];
	return max(A[2], A[3]);
}

void pop_min() {
	swap(A[1], A[size]);
	A[size--] = NONE;
	push_min(1);
}

void pop_max() {
	if (size == 1) {
		pop_min();
		return;
	}
	int i = A[2] > A[3] ? 2 : 3;
	swap(A[i], A[size]);
	A[size--] = NONE;
	push_max(i);
}

void build(vi &v) {
	fill(A, A + MAXN, NONE);
	copy(all(v), A + 1);
	size = sz(v);
	if (size == 0)
		return;
	int dep = msb(size);
	for (int i = (1 << dep--) - 1; i >= 1; i--) {
		if (dep % 2)
			push_max(i);
		else
			push_min(i);
		if (popcnt(i) == 1)
			dep--;
	}
}

int main() {

}
