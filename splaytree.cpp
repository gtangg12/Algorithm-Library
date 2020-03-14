// Splay Tree

#include "header.h"

#define cnt(x) (x ? x->sz : 0)

struct node {
	ll x, sz = 1;
	node *c[2] = {NULL}, *p = NULL;

	node(ll x) : x(x) {}

	void pull() {
		sz = cnt(c[0]) + cnt(c[1]) + 1;
	}
};

void link(node *x, node *y, int d) {
	if (x)
		x->c[d] = y;
	if (y)
		y->p = x;
}

void rotate(node *t, int d) {
	// d = 0 for left child, 1 right
	node *p = t->p, *c = t->c[d];
	link(t, c->c[!d], d);
	link(c, t, !d);
	link(p, c, p ? t == p->c[1] : -1);
	t->pull(), c->pull();
}

void splay(node *t) {
	while (t->p != NULL) {
		node *p = t->p, *g = p->p;
		bool dg, dp = (t == p->c[1]);
		if (!g) {
			rotate(p, dp);
			return;
		}
		dg = (p == g->c[1]);
		if (dp == dg)
			rotate(g, dg), rotate(p, dp);
		else
			rotate(p, dp), rotate(g, dg);
	}
}

void split(node *t, node *&l, node *&r, ll x) {
	node *n = NULL, *s = t;
	while (s != NULL) {
		if (s->x >= x)
			n = s;
		s = (s->x > x) ? s->c[0] : s->c[1];
	}
	if (n == NULL)
		l = t, r = NULL;
	else {
		splay(n);
		l = n->c[0], n->c[0] = NULL, n->pull();
		r = n;
	}
}

void merge(node *&t, node *l, node *r) {
	if (l == NULL) {
		t = r;
		return;
	}
	node *s = l;
	while (s->c[1] != NULL)
		s = s->c[1];
	splay(s);
	link(s, r, 1);
	s->pull();
	t = s;
}

node* find(node *&t, ll x) {
	if (!t)
		return NULL;
	if (t->x == x)
		return t;
	return (t->x > x) ? find(t->c[0], x) : find(t->c[1], x);
}

void insert(node *&t, ll x) {
	node *l = NULL, *r = NULL;
	split(t, l, r, x);
	node *n = new node(x);
	link(n, l, 0);
	link(n, r, 1);
	n->pull();
	t = n;
}

void remove(node *&t, ll x) {
	node *n = find(t, x);
	if (n == NULL)
		return;
	splay(n);
	link(NULL, n->c[0], -1);
	link(NULL, n->c[1], -1);
	merge(t, n->c[0], n->c[1]);
}

int main() {
	node *root = new node(-1);
}
