#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>
#include <queue>
#include <map>

#define ll long long int
#define lll __int128
#define ull unsigned long long int

#define INF 10000000000;


using namespace std;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int start, end;
	scanf("%d %d", &start, &end);
	start -= 1;
	end -= 1;
	end += n;
	ll capacity[2 * n][2 * n], flow[2 * n][2 * n];
	for (int i = 0; i < 2 * n; i++) {
		for (int j = 0; j < 2 * n; j++) {
			capacity[i][j] = 0;
			flow[i][j] = 0;
		}
	}
	// 0 ~ (n-1) : node_in
	// n ~ (2n - 1) : node_out
	for (int i = 0; i < n; i++) {
		ll cost;
		scanf("%lld", &cost);
		capacity[i][i + n] = cost;
	}
	
	for (int i = 0; i < m; i++) {
		int v1, v2;
		scanf("%d %d", &v1, &v2);
		v1 -= 1;
		v2 -= 1;
		// v1_out -> v2_in
		capacity[v1 + n][v2] = INF;
		// v2_out -> v1_in
		capacity[v2 + n][v1] = INF;
	}
	
	while (true) {
		vector<int> prev(2 * n, -1);
		prev[start] = start;
		queue<int> q;
		q.push(start);
		
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			
			for (int f = 0; f < 2 * n; f++) {
				if (capacity[cur][f] - flow[cur][f] > 0 && prev[f] == -1) {
					q.push(f);
					prev[f] = cur;
				}
			}
			
			if (prev[end] != -1) {
				break;
			}
		}
		
		if (prev[end] == -1) {
			break;
		}
		
		ll cur_flow = INF;
		
		for (int f = end; f != start; f = prev[f]) {
			cur_flow = min(capacity[prev[f]][f] - flow[prev[f]][f], cur_flow);
		}
		
		for (int f = end; f != start; f = prev[f]) {
			flow[prev[f]][f] += cur_flow;
			flow[f][prev[f]] -= cur_flow;
		}
	}
	
	vector<bool> visited(2 * n, false);
	queue<int> q;
	q.push(start);
	visited[start] = true;
	
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		
		for (int f = 0; f < 2 * n; f++) {
			if (capacity[cur][f] - flow[cur][f] > 0 && !visited[f]) {
				q.push(f);
				visited[f] = true;
			}
		}
	}
	
	for (int v = 0; v < n; v++) {
		if (visited[v] && !visited[v + n]) {
			printf("%d ", v + 1);
		}
	}
}
