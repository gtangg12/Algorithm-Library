// Persistent Segment Tree

#include "header.h"

#define MAXN 262144

struct node {
	int sum;
	node *l, *r;

	node(int x, node *l, node *r) : sum(x), l(l), r(l) {};

	void pull() {
		sum = 0;
		if (l)
			sum += l->sum;
		if (r)
			sum += r->sum;
	}
};

int range_sum(node *t, int l, int r, int li = 0, int ri = MAXN - 1) {
	if (ri < l || li > r)
		return 0;
	if (l <= li && ri <= r)
		return t->sum;
	int m = (li + ri) / 2;
	return range_sum(t->l, l, r, li, m) + range_sum(t->r, l, r, m + 1, ri);
}

node *point_upd(node *t, int idx, int v, int li = 0, int ri = MAXN - 1) {
	if (ri < idx || li > idx)
		return t;
	node *n = new node(0, NULL, NULL);
	if (li == ri) {
		n->sum = t->sum + v;
		return n;
	}
	int m = (li + ri) / 2;
	n->l = point_upd(t->l, idx, v, li, m);
	n->r = point_upd(t->r, idx, v, m + 1, ri);
	n->pull();
	return n;
}

node *st_build(vi &v, int li, int ri) {
	if (li == ri)
		return new node(v[li], NULL, NULL);
	int m = (li + ri) / 2;
	node *n = new node(0, st_build(v, li, m), st_build(v, m + 1, ri));
	n->pull();
	return n;
}

// root maintenance
map<int, node*> t_map;

int range_sum(int l, int r, int t) {
	node *n = prev(t_map.ub(t))->s;
	return range_sum(n, l, r);
}

void point_upd(int idx, int v, int t) {
	node *cur_n, *n;
	cur_n = prev(en(t_map))->s;
	n = point_upd(cur_n, idx, v);
	t_map[t] = n;
}

int main() {
	vi init(MAXN, 0);
	t_map[0] = st_build(init, 0, MAXN - 1);
}
