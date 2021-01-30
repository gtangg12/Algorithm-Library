// 2D geometry algorithms

#include "header.h"

const double PI = 3.1415926;
const double EPS = 1e-9;

inline pd operator + (const pd p, const pd q) { return mp(p.f + q.f, p.s + q.s); }
inline pd operator - (const pd p, const pd q) { return mp(p.f - q.f, p.s - q.s); }
inline pd operator * (const double k, const pd p) { return mp(k * p.f, k * p.s); }
inline pd operator / (const pd p, const double k) { return mp(p.f / k, p.s / k); }

inline double len(const pd p) { return sqrt(p.f * p.f + p.s * p.s); }
inline pd norm(pd p) { return p / len(p); }
inline double dot(pd p, pd q) { return p.f * q.f + p.s * q.s; }
inline double cross(pd p, pd q) { return p.f * q.s - p.s * q.f; }

pd proj(pd a, pd b, pd c) {
	// project c - a on b - a
	return a + dot(c - a, b - a) * (b - a) / dot(b - a, b - a);
}

pd rotate_ccw(pd p, double t) {
	// rotate through origin
	return mp(p.f * cos(t) - p.s * sin(t), p.f * sin(t) + p.s * cos(t));
}

double dis_point_line(pd a, pd b, pd c) {
	// distance from c to b - a
	return len(c - proj(a, b, c));
}

vpd sort_vert(vpd &pnts) {
	// order points of polygon in CCW starting with point w/ smallest x-coord, then y-coord
	sort(all(pnts));
	vector<pair<double, int> > tmp;
	for (int i = 1; i < sz(pnts); i++) {
		pd v = pnts[i] - pnts[0];
		tmp.pb({asin(v.s / len(v)), i});
	}
	sort(all(tmp));
	vpd polygon;
	polygon.pb(pnts[0]);
	for (auto &p : tmp)
		polygon.pb(pnts[p.s]);
	return polygon;
}

// Assumes points in CCW order
bool point_in_polygon(vpd &pnts, pd p) {
	int n = sz(pnts);
	if (cross(pnts[1] - pnts[0], p - pnts[0]) < 0 ||
	    cross(pnts[n - 1] - pnts[0], p - pnts[0]) > 0)
		return false;
	int l = 1, h = n - 2;
	int ans;
	while (l <= h) {
		int mid = (l + h) / 2;
		if (cross(pnts[mid] - pnts[0], p - pnts[0]) >= 0) {
			ans = mid;
			l = mid + 1;
		}
		else
			h = mid - 1;
	}
	return cross(pnts[ans + 1] - pnts[ans], p - pnts[ans + 1]) >= 0;
}

double polygon_area(vpd &pnts) {
	double area = 0;
	for (int i = 1; i < sz(pnts) - 1; i++)
		area += cross(pnts[i] - pnts[0], pnts[i + 1] - pnts[i]);
	return area / 2;
}

pd centroid(vpd &pnts) {
	double area = polygon_area(pnts);
	pd cent = mp(0, 0);
	for (int i = 1; i < sz(pnts) - 1; i++) {
		double a = cross(pnts[i] - pnts[0], pnts[i + 1] - pnts[i]) / 2;
		cent = cent + a / area * (pnts[0] + pnts[i] + pnts[i + 1]) / 3;
	}
	return cent;
}

// Returns number of intersections
int isect_lines(pd a, pd b, pd c, pd d, pd &isect) {
	// intersection of lines through a, b and c, d
	pd r = b - a;
	pd s = d - c;
	double u = cross(r, s);
	double v = cross(c - a, r);
	if (fabs(u) < EPS)
		return fabs(v) < EPS ? INF : 0;
	isect = c + v / u * s;
	return 1;
}

int isect_circles(pd p, double r1, pd q, double r2, vpd &isect) {
	// intersection of circles centered at p, q with radius r1, r2
	if (p == q && r1 == r2)
		return INF;
	double t = len(q - p);
	if (t > r1 + r2 + EPS || t < fabs(r1 - r2) - EPS)
		return 0;
	pd n = (q - p) / t;
	double u = (r1 * r1 - r2 * r2 + t * t) / (2 * t);
	pd mid = p + u * n;
	if (fabs(u - r1) < EPS) {
		isect.pb(mid);
		return 1;
	}
	double v = sqrt(r1 * r1 - u * u);
	pd n2 = rotate_ccw(n, PI / 2);
	isect.pb(mid + v * n2);
	isect.pb(mid - v * n2);
	return 2;
}

int isect_line_circle(pd a, pd b, pd p, double r, vpd &isect) {
	// intersection of line through a, b and circle p with radius r
	a = a - p;
	b = b - p;
	double m = (b.s - a.s) / (b.f - a.f);
	double u = m * a.f - a.s;
	double v = 1 + m * m;
	double t = fabs(u) / sqrt(v);
	if (t > r + EPS)
		return 0;
	double x = -u / v;
	double y = m * u / v;
	pd mid = mp(x, y);
	if (t > r - EPS) {
		isect.pb(mid + p);
		return 1;
	}
	double t2 = sqrt(r * r - u * u / v);
	pd n = norm(b - a);
	isect.pb(mid + t2 * n + p);
	isect.pb(mid - t2 * n + p);
	return 2;
}

int main() {

}
