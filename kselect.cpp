// Min kth element in expected O(n)

#include "header.h"

#define MAXN 1048576

int A[MAXN];

int partition(int l, int r, int pivot) {
	swap(A[l + pivot], A[r]);
	int x = A[r], i = l;
	for (int j = l; j <= r - 1; j++)
		if (A[j] <= x) {
			swap(A[i], A[j]);
			i++;
		}
	swap(A[i], A[r]);
	return i;
}

int kth_random(int l, int r, int k) {
	int n = r - l + 1;
	int pivot = rand() % n;
	pivot = partition(l, r, pivot);
	if (pivot - l == k)
		return A[pivot];
	if (k < pivot - l)
		return kth_random(l, pivot - 1, k);
	return kth_random(pivot + 1, r, k - (pivot - l + 1));
}

int main() {

}
