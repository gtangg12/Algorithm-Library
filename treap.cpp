// Treap

#include "header.h"

#define cnt(x) (x ? x->size : 0)

struct node {
	int y = rand() ^ (rand() << 16);
	int size = 1;
	int x;
	node *l = NULL, *r = NULL;

	node(int x) : x(x) {}

	void pull() {
		size = cnt(l) + cnt(r) + 1;
	}
};

void split(node *t, node *&l, node *&r, int x) {
	if (!t) {
		l = r = NULL;
		return;
	}
	if (x <= t->x)
		r = t, split(t->l, l, t->l, x);
	else
		l = t, split(t->r, t->r, r, x);
	t->pull();
}

void merge(node *&t, node *l, node *r) {
	if (!l || !r) {
		t = l ? l : r;
		return;
	}
	if (l->y < r->y)
		t = l, merge(l->r, l->r, r);
	else
		t = r, merge(r->l, l, r->l);
	t->pull();
}

node *find(node *t, int x) {
	if (!t)
		return NULL;
	if (t->x == x)
		return t;
	return (t->x > x) ? find(t->l, x) : find(t->r, x);
}

void insert(node *&t, int x) {
	node *l = NULL, *r = NULL;
	split(t, l, r, x);
	node *n = new node(x);
	merge(t, l, n);
	merge(t, t, r);
}

void remove(node *&t, int x) {
	node *l = NULL, *r = NULL;
	split(t, l, t, x);
	split(t, t, r, x + 1);
	merge(t, l, r);
}

int main() {
	node *root = new node(-1);
}
