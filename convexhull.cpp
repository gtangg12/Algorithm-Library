/**
    Convex Hull via Andrew's Monotone Chain Algorithm (computes lower then upper
    hull after sorting by x)
 */
#include "header.h"

double cross(pd a, pd b, pd c) {
	return (b.f-a.f)*(c.s-a.s) - (b.s-a.s)*(c.f-a.f);
}

void graham_scan(vpd &vp, vpd &vh) {
	sort(be(vp), en(vp));
	vh = vpd(sz(vp)+1);
	int idx = 0, mid;
	for (int i = 0; i < sz(vp); i++) {
		while (idx >= 2 && cross(vh[idx-2], vh[idx-1], vp[i]) >= 0)
			idx--;
		vh[idx++] = vp[i];
	}
    mid = idx;
	for (int i = sz(vp)-2; i >= 0; i--) {
        while (idx > mid && cross(vh[idx-2], vh[idx-1], vp[i]) >= 0)
            idx--;
        vh[idx++] = vp[i];
	}
    vh.resize(idx-1);
}

int main() {
    vpd vp, vh;
}
