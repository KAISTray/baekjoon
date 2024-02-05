#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <algorithm>
#include <tuple>

#define V_MAX 10000

using namespace std;

int root[V_MAX];
int height[V_MAX];


void union_clear(int N) {
	for (int i = 0; i < N; i++) {
		root[i] = i;
		height[i] = 0;
	}
}

int union_find(int x) {
	return (root[x] == x ? x : root[x] = union_find(root[x]));
}

void union_join(int x, int y) {
	x = union_find(x);
	y = union_find(y);
	if (x == y) {
		return;
	}
	if (height[x] < height[y]) {
		root[x] = y;
	} else {
		root[y] = x;
	}
	if (height[x] == height[y]) {
		height[x]++;
	}
}

static bool weight_cmp(tuple<int, int, int>& t1, tuple<int, int, int>& t2) {
	return get<2>(t1) < get<2>(t2);
}

int main() {
	int v, e;
	scanf("%d %d", &v, &e);
	
	
	vector<tuple<int, int, int>> weight;
	weight.clear();
	
	union_clear(v);
	
	for (int i = 0; i < e; i++) {
		int v1, v2, w;
		scanf("%d %d %d", &v1, &v2, &w);
		tuple<int, int, int> new_tuple = make_tuple(v1, v2, w);
		weight.push_back(new_tuple);
	}
	
	sort(weight.begin(), weight.end(), weight_cmp);
	tuple<int, int, int> sel;
	int selected_weight = 0;
	int sum_weight = 0;
	
	for (vector<tuple<int, int, int>>::iterator i = weight.begin(); i != weight.end(); i++) {
		sel = *i;
		int v1 = get<0>(sel), v2 = get<1>(sel);
		if (union_find(v1) == union_find(v2)) {
			continue;
		} else {
			selected_weight++;
			union_join(v1, v2);
			sum_weight += get<2>(sel);
		}
		if (selected_weight == v-1) {
			break;
		}
	}
	printf("%d", sum_weight);
}
