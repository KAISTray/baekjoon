#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>
#include <queue>
#include <map>
#include <complex>

using namespace std;

int dp[302][302][2]; // l r pos
bool visit[302][302][2];


vector<int> pos;

int dist (int l, int r) {
	return abs(pos[l] - pos[r]);
}

// l, r : 구간
// s : 수아 position (false -> Left, true -> right)
// k : **먹으려는 사탕바구니의 수** 

int n, m;

int sol(int l, int r, int s, int k) {
	//if (l == r) printf("Called sol for [%d %d], %s with k = %d\n", l, r, s ? "right" : "left ", k);
	if (k == 0) { // 먹으려는 사탕 바구니가 없음
		return 0;
	}
	if (l == 0 && r == n) { // 탐색 끝
		return 0;
	}
	int& R = dp[l][r][s];
	if (visit[l][r][s]) { // accessed
		return R;
	}
	int now = s ? r : l;
	if (l > 0) {
		R = max(R, sol(l - 1, r, 0, k - 1) + m - k * dist(l - 1, now));
	}
	if (r < n) {
		R = max(R, sol(l, r + 1, 1, k - 1) + m - k * dist(r + 1, now));
	}
	visit[l][r][s] = true;
	return R;
}

int main() {
	scanf("%d %d", &n, &m);
	pos.clear();
	bool isStart = false;
	for (int i = 0; i < n; i++) {
		int t;
		scanf("%d", &t);
		pos.push_back(t);
		if (t == 0) {
			isStart = true;
		}
	}
	
	if (isStart) {
		n--;
	} else {
		pos.push_back(0);
	}
	
	sort(pos.begin(), pos.end());
	
	int idx = lower_bound(pos.begin(), pos.end(), 0) - pos.begin();
	
	int ans = 0;
	
	for (int k = 0; k <= n; k++) {
		memset(dp, 0, sizeof(dp));
		memset(visit, 0, sizeof(visit));
		int ret = sol(idx, idx, 0, k) + (isStart ? m : 0);
		ans = ans > ret ? ans : ret;
	}

	printf("%d", ans);
	
	
	
}
