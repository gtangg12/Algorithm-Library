// Convex Hull
//
// Uses Andrew's Monotone Chain Algorithm
// Computes lower then upper hull after sorting by x)

#include "header.h"

double cross(pd a, pd b, pd c) {
	return (b.f - a.f) * (c.s - a.s) - (b.s - a.s) * (c.f - a.f);
}

vpd graham_scan(vpd &pnts) {
	sort(all(pnts));
	int n = sz(pnts);
	vpd hull = vpd(n + 1);
	int idx = 0;
	for (int i = 0; i < n; i++) {
		while (idx >= 2 && cross(hull[idx - 2], hull[idx - 1], pnts[i]) >= 0)
			idx--;
		hull[idx++] = pnts[i];
	}
	int mid = idx;
	for (int i = n - 2; i >= 0; i--) {
		while (idx > mid && cross(hull[idx - 2], hull[idx - 1], pnts[i]) >= 0)
			idx--;
		hull[idx++] = pnts[i];
	}
	hull.resize(idx - 1);
	return hull;
}

int main() {

}
