#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <algorithm>

#define ll long long int
#define lll __int128

using namespace std;

#define smax 500002

class stype {
	public:
		int x, y, z;
		stype(int _x, int _y, int _z) {
			x = _x;
			y = _y;
			z = _z;
		}
		bool operator< (stype& cmp) {
			return x < cmp.x;
		}
		
		bool operator> (stype& cmp) {
			return x > cmp.x;
		}
};

int segnode(int x, int y) {
	return x < y ? x : y;
}

int segupdate(vector<int>& tree, int node, int start, int end, int idx, int newval) {
	if (start > idx || end < idx) {
		return tree[node]; // oob
	}
	
	if (start == end) {
		tree[node] = newval;
	} else {
		int mid = (start + end) / 2;
		tree[node] = segnode(
		segupdate(tree, node * 2, start, mid, idx, newval),
		segupdate(tree, node * 2 + 1, mid + 1, end, idx, newval)
		);
	}
	
	return tree[node];
}

int segget(vector<int>& tree, int node, int start, int end, int left, int right) {
	if (start > right || end < left) {
		return tree[node]; // oob
	}
	
	if (start == end) {
		return tree[node];
	} else {
		int mid = (start + end) / 2;
		return segnode(
		segget(tree, node * 2, start, mid, left, right),
		segget(tree, node * 2 + 1, mid + 1, end, left, right)
		);
	}
}

int main() {
	int N;
	scanf("%d", &N);
	stype nul(smax, smax, smax);
	vector<stype> istr(N, nul);
	int t;
	for (int i = 0; i < N; i++) {
		scanf("%d", &t);
		istr[t].x = i;
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &t);
		istr[t].y = i;
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &t);
		istr[t].z = i;
	}
	sort(istr.begin(), istr.end());
	vector<int> tree(4 * N + 10);
	
	for (int i = 0; i < N; i++) {
		segupdate(tree, 1, 0, N - 1, i, smax);
	}
	
	int ans = 0;
	for (int i = 0; i < N; i++) {
		if (segget(tree, 1, 0, N - 1, 1, istr[i].y) > istr[i].z) {
			ans++;
		}
		segupdate(tree, 1, 0, N - 1, istr[i].y, istr[i].z);
	}
	printf("%d", ans);
	
}

