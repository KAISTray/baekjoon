#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

int main() {
	int v, e;
	scanf("%d %d", &v, &e);
	
	vector<tuple<int, int, int> > edge;
	bool visited[v+1];
	vector<vector<int> > isConnectWith(v+1); //정점 v와 연결된 간선의 index들 목록
	priority_queue<int, vector<int>, greater<int> > prior;
	
	for (int i=1; i<=v; i++) {
		visited[i] = false;
	}
	
	tuple<int, int, int> nullTuple = make_tuple
	edge.push_back()
	
	for (int i=1; i<=e; i++) {
		int init,fin,d;
		scanf("%d %d %d", &init, &fin, &d);
		tuple<int, int, int> tmp = make_tuple(d, init, fin);
		edge.push_back(tmp);
		isConnectWith[init].push_back(i);
		isConnectWith[fin].push_back(i);
	}
	
	//기준점 : 0, 따라서 dist[0] = -1000001; 
	
	vector<int> min; //selected edge
	
	int nowDist = 0;
	int conCount = 1;
	int cur = 1;
	while(conCount < v) {
		printf("cur : %d | ", cur);
		visited[cur] = true;
		while(!isConnectWith[cur].empty()) { //selected된(cur) vertex 인근의 edge들을 모두 priority_queue에 추가 
			printf("A");
			prior.push(isConnectWith[cur].back());
			isConnectWith[cur].pop_back();
		}
		printf("\n");
		int selEdge;
		while(true) { //visited된 건 거르고 간선 고르기
			int temp = prior.top();
			printf("{B : %d}", temp);
			prior.pop();
			if (visited[get<1>(edge[temp])] && visited[get<2>(edge[temp])]) {
				continue;
			} else {
				selEdge = temp;
				printf("\nSelected SelEdge : %d", selEdge);
				break;
			}
			
		}
		printf("\nDist : %d ConNode : %d %d\n", get<0>(edge[selEdge]), get<1>(edge[selEdge]), get<2>(edge[selEdge]));
		for (int i=1; i<=v; i++) {
			printf("C");
			if (visited[i] && get<1>(edge[selEdge]) == i) {
				cur = get<2>(edge[selEdge]);
				break;
			} else if (visited[i] && get<2>(edge[selEdge]) == i) {
				cur = get<1>(edge[selEdge]);
				break;
			}
		}
		
		printf("\nDist : %d ConNode : %d %d\n", get<0>(edge[selEdge]), get<1>(edge[selEdge]), get<2>(edge[selEdge]));
		nowDist += get<0>(edge[selEdge]);
		conCount++;
		printf("SelEdge : %d\n", selEdge);
	}
	
	printf("%d", nowDist);
	
}
