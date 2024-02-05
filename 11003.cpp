#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <stack>
#include <deque>
#include <queue>
#include <algorithm>
#include <string.h>

#ifndef __int128
#define __int128 long long int
#endif

#define ll long long int
#define lll __int128

#define v vector
#define it ::iterator

using namespace std;

struct db {
	int n;
	int idx;
};

struct cmp {
	bool operator()(const db& x, const db& y) {
		return x.n > y.n;
	}
}; 

int main () {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int N, L;
	cin >> N >> L;
	priority_queue<db, vector<db>, cmp> dq;
	
	for (int i = 0; i < N; i++) {
		int t;
		cin >> t;
		dq.push({t, i});
		int idx = dq.top().idx;
		while(idx < i - L + 1) {
			dq.pop();
			idx = dq.top().idx;
		}
		cout << dq.top().n << " ";
	}
}
