#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>

#define state_debug false
#define DEBUG if (state_debug) 

using namespace std;

stack<tuple<int, int>> cur;
stack<vector<int>> mem;
/*
bool movable(vector<int> m, int src, int dst) {
	if (src < -n + 1 || src > n - 1 || dst < -n + 1 || dst > n - 1) {
		return false;
	}
	
	if (m[src + n - 1] == 0 || m[src + n] == 0) {
		return false;
	}
	
	if (m[dst + n - 1] != 0 || m[dst + n] != 0) {
		return false;
	}
	return true;
}

vector<int> move(vector<int> m, int src, int dst) {
	m[dst + n - 1] = m[src + n - 1];
	m[dst + n] = m[src + n];
	m[src + n - 1] = 0;
	m[src + n] = 0;
	return m;
}

void dump() {
	stack<tuple<int, int>> cur_rev;
	while(!cur.empty()) {
		cur_rev.push(cur.top());
		cur.pop();
	}
	
	while(!cur_rev.empty()) {
		tuple<int, int> id = cur_rev.top();
		printf("%d %d\n", get<0>(id), get<1>(id));
		cur_rev.pop();
	}
	
	printf("===========================\n");
	return;
}

void dump_vec(vector<int> m) {
	for (int i = -n + 1; i <= n; i++) {
		printf("%2d ", abs(i));
	}
	printf("\n");
	for (int i = 0; i < 2*n; i++) {
		printf("%2d ", m[i]);
	}
	printf("\n");
}

void dfs(int dpt) {
	DEBUG printf("DFS in depth %d\n", dpt);
	vector<int> m(2*n, 0);
	if (dpt != 0) {
		m = mem.top();
	} else {
		for (int i = n; i < 2*n; i++) {
			m[i] = (i % 2) ? 1 : 2;
		}
	}
	
	if (dpt == n / 2) {
		// check AAAABBBB
		int p;
		bool find = false;
		bool fail = false;
		for (int i = 0; i < n + 1; i++) {
			if (m[i] != 0) {
				p = i;
				find = true;
				break;
			}
		}
		
		if (find = false) return;
		
		for (int j = p; j < p + n; j++) {
			if (m[j] != (j < p + (n / 2) ? 1 : 2)) {
				fail = true;
				break;
			}
		}
		if (!fail) {
			dump();
		}
		return;
	}
	int j;
	if (dpt == 0) {
		j = -1;
	} else {
		j = get<0>(cur.top());
	}
	for (int i = -n + 1; i < n; i++) {
		if (movable(m, i, j)) {
			tuple<int, int> x(i, j);
			cur.push(x);
			vector<int> n = move(m, i, j);
			mem.push(n);
			DEBUG printf("Find for %d and %d\n", i, j);
			DEBUG dump_vec(m);
			dfs(dpt + 1);
			mem.pop();
			cur.pop();
		}
	}
}




*/


void pt(int a, int b, int st) {
	printf("%d to %d\n", a + st, b + st);
}

void solve(int n, int st) {
	if (n == 3) {
		pt(2, -1, st);
		pt(5, 2, st);
		pt(3, -3, st);
	} else if (n == 4) {
		pt(6, -1, st);
		pt(3, 6, st);
		pt(0, 3, st);
		pt(7, 0, st);
	} else if (n == 5) {
		pt(8, -1, st);
		pt(3, 8, st);
		pt(6, 3, st);
		pt(0, 6, st);
		pt(9, 0, st);
	} else if (n == 6) {
		//-1 10 7 2 6 0 11
		pt(10, -1, st);
		pt(7, 10, st);
		pt(2, 7, st);
		pt(6, 2, st);
		pt(0, 6, st);
		pt(11, 0, st);
	} else if (n == 7) {
		pt(8, -1, st);
		pt(5, 8, st);
		pt(12, 5, st);
		pt(3, 12, st);
		pt(9, 3, st);
		pt(0, 9, st);
		pt(13, 0, st);
	} else {
		pt(2 * n - 2, -1 , st);
		pt(3, 2 * n - 2, st);
		solve(n - 4, st + 4);
		pt(0, 2 * n - 5, st);
		pt(2 * n - 1, 0, st);
	}
}


int main() {
	int N;
	while(!cur.empty()) cur.pop();
	while(!mem.empty()) mem.pop();
	scanf("%d", &N);
	solve(N, 0);
}
