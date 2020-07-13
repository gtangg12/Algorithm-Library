// Binomial Heap
//
// Allows two heaps to be merged together in O(logN)
// All keys must be unique among all heaps

#include "header.h"

#define get(h, i) (i < sz(h) ? h[i] : NULL)

struct node {
	int k, x;
	int deg;
	node *c = NULL, *p = NULL, *s = NULL;

	node(int k, int x) : k(k), x(x) {}
};

typedef vector<node*> heap;

map<int, node*> dict;

void link(node *t1, node *t2) {
	// t1 as t2's child
	t1->p = t2;
	t1->s = t2->c;
	t2->c = t1;
	t2->deg++;
}

heap merge(heap &h1, heap &h2) {
	heap tmp;
	int i = 0, j = 0;
	while (i < sz(h1) && j < sz(h2)) {
		if (h1[i]->deg < h2[j]->deg)
			tmp.pb(h1[i++]);
		else
			tmp.pb(h2[j++]);
	}
	while (i < sz(h1))
		tmp.pb(h1[i++]);
	while (j < sz(h2))
		tmp.pb(h2[j++]);
	heap res;
	node *a, *b, *c;
	a = get(tmp, 0);
	b = get(tmp, 1);
	c = get(tmp, 2);
	int idx = 0;
	while (a != NULL) {
		idx++;
		if (b == NULL || a->deg < b->deg || c != NULL && b->deg == c->deg) {
			res.pb(a);
			a = b;
			b = get(tmp, idx + 1);
			c = get(tmp, idx + 2);
		}
		else {
			if (a->k < b->k)
				swap(a, b);
			link(a, b);
			a = b;
			b = c;
			c = get(tmp, idx + 2);
		}
	}
	return res;
}

void decrease_key(int k, int kn) {
	node *t = dict[k];
	while (t->p != NULL && t->p->k > kn) {
		swap(dict[k], dict[t->p->k]);
		swap(t->x, t->p->x);
		t->k = t->p->k;
		t = t->p;
	}
	t->k = kn;
	dict.erase(k);
	dict[kn] = t;
}

void insert(heap &h, int k, int x) {
	heap tmp;
	node *t = new node(k, x);
	dict[k] = t;
	tmp.pb(t);
	h = sz(h) ? merge(h, tmp) : tmp;
}

void remove_root(heap &h, int k) {
	node *t = dict[k];
	heap tmp;
	node *cur = t->c;
	while (cur != NULL) {
		tmp.pb(cur);
		node *nxt = cur->s;
		cur->p = NULL;
		cur->s = NULL;
		cur = nxt;
	}
	reverse(be(tmp), en(tmp));
	heap rem;
	for (node *t : h) if (t->k != k)
		rem.pb(t);
	h = merge(tmp, rem);
}

void remove(heap &h, int k) {
	decrease_key(k, -INF);
	remove_root(h, -INF);
}

int main () {

}
