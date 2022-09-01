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
		
		int d[n]; //time to build
		
		for (i=0; i<n; i++) {
			scanf("%d", &d[i]);
		}
		
		vector<int> a[n];
		int init, end;
		
		for (i=0; i<k; i++) {
			scanf("%d %d", &init, &end);
			a[end].push_back(init); //역방향 그래프 : W번째 정점이 중심이되는..! 
		}
		
		vector<int> min(n), visited(n);	
		deque<int> valid; //유효한 끝노드 인덱스들 
		deque<int> visit; //방문할 덱들 
		
		int W, now;
		scanf("%d", &W);
		
		visit.push_front(W);
		
		while(true) { //순회버스 출발
		// 정점 W에서 시작해서 주변 하나씩 탐색하기 
			
			
			now = visit.pop_back();
			//visit_pop_back을 뽑아옴
			//그 근처에 애들 다 순회함
			while(true) {
				if (min[n] == 0) {
					
				} 
			}
			
		}
	}
}
