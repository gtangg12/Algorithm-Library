/**
    Binary Index Tree w/ 2D range sum and 2D range add
 */
#include "header.h"

#define MAXN 1024

int bit2D[MAXN][MAXN];

int range_sum(int r, int c) {
	int sum = 0;
	for (int i = r; i >= 0; i = (i&(i+1))-1)
		for (int j = c; j >= 0; j = (j&(j+1))-1)
			sum += bit2D[i][j];
	return sum;
}

void point_upd(int r, int c, int v) {
	for (int i = r; i < MAXN; i = i|(i+1))
		for (int j = c; j < MAXN; j = j|(j+1))
			bit2D[i][j] += v;
}

int main() {
	fill(bit2D[0], bit2D[0]+MAXN*MAXN, 0);
}
