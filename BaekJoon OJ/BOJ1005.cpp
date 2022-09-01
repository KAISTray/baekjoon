#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>

using namespace std;

int main() {
	int T;
	int t, i, j; //iter var. t for testcase Iter
	scanf("%d", &T);	
	
	
	for (t=0; t<T; t++) {
		int n,k;
		scanf("%d %d", &n, &k);
		
		int d[n+1]; //time to build
		
		for (i=1; i<=n; i++) {
			scanf("%d", &d[i]);
		}
		
		vector<vector<int> > a(n+1);
		int init, end;
		
		for (i=0; i<k; i++) {
			scanf("%d %d", &init, &end);
			a[end].push_back(init); //역방향 그래프 : W번째 정점이 중심이되는..! 
		}
		
		vector<int> min(n), visited(n);	
		deque<int> valid; //유효한 끝노드 인덱스들 
		deque<int> visit; //방문할 덱들 
		
		int W, now, cur;
		scanf("%d", &W);
		
		visit.push_front(W);
		
		while(!visit.empty()) { //순회버스 출발
		// 정점 W에서 시작해서 주변 하나씩 탐색하기 
			
			now = visit.back();
			visit.pop_back();
			
			if (visited[now] == 1) {
				continue;
			}
			
			//visit_pop_back을 뽑아옴
			//그 근처에 애들 다 순회함
			if (a[now].empty()) {
				valid.push_back(now);
			}
			
			while(!a[now].empty()) {
				cur = a[now].back();
				a[now].pop_back();
				
				if (min[cur] == 0 || min[cur] < min[now] + d[cur]) {
					min[cur] = min[now] + d[cur];
				}
				
				if (visited[now] != 1) {
					visit.push_front(cur);
				}
			}
			visited[now] = 1;
		}
		
		int Ans = -1;
		
		
		while(!valid.empty()) {
			cur = valid.back();
			valid.pop_back();
			if (Ans == -1 || Ans > min[cur]) {
				Ans = min[cur];
			}
		}
		
		printf("%d\n", Ans);
	}
}
