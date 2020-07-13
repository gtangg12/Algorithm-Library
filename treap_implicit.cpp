// Implicit Treap

#include "header.h"

#define cnt(x) (x ? x->size : 0)

struct node {
	int y = rand() ^ (rand() << 16);
	int x;
	int size = 1;
	int sum, lazy = 0;
	node *l = NULL, *r = NULL;

	node(int x) : x(x), sum(x) {}

	void pull() {
		sum = x;
		if (l)
			l->push(), sum += l->sum;
		if (r)
			r->push(), sum += r->sum;
		size = cnt(l) + cnt(r) + 1;
	}

	void push() {
		x += lazy, sum += lazy;
		if (l)
			l->lazy += lazy;
		if (r)
			r->lazy += lazy;
		lazy = 0;
	}
};

void split_at(node *t, node *&l, node *&r, int i) {
	if (!t) {
		l = r = NULL;
		return;
	}
	t->push();
	if (i <= cnt(t->l))
		r = t, split_at(t->l, l, t->l, i);
	else
		l = t, split_at(t->r, t->r, r, i - cnt(t->l) - 1);
	t->pull();
}

void merge(node *&t, node *l, node *r) {
	if (!l || !r) {
		t = l ? l : r;
		return;
	}
	if (l->y < r->y)
		t = l, l->push(), merge(l->r, l->r, r);
	else
		t = r, r->push(), merge(r->l, l, r->l);
	t->pull();
}

node *find_at(node *t, int i) {
	if (!t)
		return NULL;
	t->push();
	node *ret;
	if (i == cnt(t->l))
		ret = t;
	else if (i < cnt(t->l))
		ret = find_at(t->l, i);
	else
		ret = find_at(t->r, i - cnt(t->l) - 1);
	t->pull();
	return ret;
}

void insert_at(node *&t, int i, int x) {
	node *l = NULL, *r = NULL;
	split_at(t, l, r, i);
	node *n = new node(x);
	merge(t, l, n);
	merge(t, t, r);
}

void remove_at(node *&t, int i) {
	node *l = NULL, *r = NULL;
	split_at(t, l, t, i);
	split_at(t, t, r, 1);
	merge(t, l, r);
}

int range_sum(node *t, int li, int ri) {
	node *l = NULL, *r = NULL, *s = NULL;
	split_at(t, l, r, li);
	split_at(r, r, s, ri - li + 1);
	int ret = r->sum;
	merge(t, l, r);
	merge(t, t, s);
	return ret;
}

void range_add(node *t, int li, int ri, int v) {
	node *l = NULL, *r = NULL, *s = NULL;
	split_at(t, l, r, li);
	split_at(r, r, s, ri - li + 1);
	r->lazy += v;
	merge(t, l, r);
	merge(t, t, s);
}

int main() {
	node *root = new node(-1);
}
