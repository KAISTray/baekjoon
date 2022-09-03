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
	vector<vector<int> > isConnectWith(v+1); //���� v�� ����� ������ index�� ���
	priority_queue<int, vector<int>, greater<int> > prior;
	
	tuple<int, int, int> nullTuple = make_tuple(0, 0, 0);
	edge.push_back(nullTuple);
	
	for (int i=1; i<=v; i++) {
		visited[i] = false;
	}
	
	for (int i=1; i<=e; i++) {
		int init,fin,d;
		scanf("%d %d %d", &init, &fin, &d);
		tuple<int, int, int> tmp = make_tuple(d, init, fin);
		edge.push_back(tmp);
		isConnectWith[init].push_back(i);
		isConnectWith[fin].push_back(i);
	}
	
	//������ : 0, ���� dist[0] = -1000001; 
	
	vector<int> min; //selected edge
	
	int nowDist = 0;
	int conCount = 1;
	int cur = 1;
	while(conCount < v) {
		visited[cur] = true;
		while(!isConnectWith[cur].empty()) { //selected��(cur) vertex �α��� edge���� ��� priority_queue�� �߰� 
			prior.push(isConnectWith[cur].back());
			isConnectWith[cur].pop_back();
		}
		int selEdge;
		while(true) { //visited�� �� �Ÿ��� ���� ����
			int temp = prior.top();
			prior.pop();
			if (visited[get<1>(edge[temp])] && visited[get<2>(edge[temp])]) {
				continue;
			} else {
				selEdge = temp;
				break;
			}
			
		}
		for (int i=1; i<=v; i++) {
			if (visited[i] && get<1>(edge[selEdge]) == i) {
				cur = get<2>(edge[selEdge]);
				break;
			} else if (visited[i] && get<2>(edge[selEdge]) == i) {
				cur = get<1>(edge[selEdge]);
				break;
			}
		}
		nowDist += get<0>(edge[selEdge]);
		conCount++;
	}
	
	printf("%d", nowDist);
	
}
