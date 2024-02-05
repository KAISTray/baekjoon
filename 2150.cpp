#include <stdio.h>
#include <stdlib.h>
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

class dir_graph {
	private:
		vector<vector<int>> graph;
		int num_node;
		
		/* section for SCC */
		bool scc_done;
		int scc_id;						// scc index
		vector<int> scc_d;				// index of node
		int scc_num;					// number of scc found
		vector<int> scc_idx;			// index of SCC
		vector<bool> scc_finished;		// true if SCC inside
		stack<int> scc_s;				// stack to do DFS
		vector<vector<int>> scc_total;	// SCC
		
		void SCC_init() {
			scc_done = false;
			scc_id = 0;
			scc_d.resize(num_node);
			scc_num = 0;
			scc_idx.resize(num_node);
			scc_finished.resize(num_node);
			scc_total.clear();
			while(!scc_s.empty()) scc_s.pop();
			
			return;
		}
		
		int SCC_DFS(int c) {
			scc_d[c] = ++scc_id;
			scc_s.push(c);
			int res = scc_d[c];
			for (v<int>it i = graph[c].begin(); i != graph[c].end(); i++) {
				if (scc_d[*i] == 0) {
					res = min(res, SCC_DFS(*i));
				} else if (!scc_finished[*i]) {
					res = min(res, scc_d[*i]);
				}
			}
			
			if (res == scc_d[c]) {
				vector<int> scc;
				while(true) {
					int n = scc_s.top();
					scc_s.pop();
					
					scc.push_back(n);
					scc_finished[n] = true;
					scc_idx[n] = scc_num;
					if (n == c) {
						break;
					} 
				}
				
				sort(scc.begin(), scc.end());
				scc_total.push_back(scc);
				scc_num++;
			}
			return res;
		}
		
		void SCC() {
			SCC_init();
			
			for (int i = 0; i < num_node; i++) {
				if (scc_d[i] == 0) {
					SCC_DFS(i);
				}
			}
			
			sort(scc_total.begin(), scc_total.end());
			for (v<v<int>>it i = scc_total.begin(); i != scc_total.end(); i++) {
				sort(i->begin(), i->end());
			}	
			scc_done = true;
		}
		/* End */
		
		
		void update() {
			scc_done = false;
		}
		
		
	public:
		
		dir_graph(vector<vector<int>> _graph) {
			graph = _graph;
			num_node = (int)_graph.size();
			update();
		}
		
		dir_graph(int _vertex) {
			num_node = _vertex;
			graph.clear();
			graph.resize(_vertex);
			update();
		}
		
		void add(int src, int dst) {
			graph[src].push_back(dst);
			update();
			return;
		}
		
		bool isConnected(int src, int dst) {
			bool find = false;
			for (v<int>it i = graph[src].begin(); i != graph[src].end(); i++) {
				if (*i == dst) {
					find = true;
					break;
				}
			}
			return find;
		}
		
		void add_s(int src, int dst) {
			if (isConnected(src, dst)) {
				return;
			}
			graph[src].push_back(dst);
			update();
			return;
		}
		
		void remove(int src, int dst) {
			vector<int> ori;
			ori.clear();
			for (v<int>it i = graph[src].begin(); i != graph[src].end(); i++) {
				if (*i != dst) {
					ori.push_back(*i);
				}
			}
			graph[src] = ori;
			update();
			return;
		}
		
		vector<vector<int>> getGraph() {
			return graph;
		}
		
		vector<vector<int>> getSCC() {
			if (!scc_done) {
				SCC();
			}
			
			return scc_total;
		}
		
		int getNumSCC() {
			if (!scc_done) {
				SCC();
			}
			
			return scc_num;
		}
};


int main() {
	int vert, e;
	scanf("%d %d", &vert, &e);
	dir_graph g(vert);
	for (int i = 0; i < e; i++) {
		int s, d;
		scanf("%d %d", &s, &d);
		g.add(s - 1, d - 1);
	}
	
	vector<vector<int>> scc = g.getSCC();
	int numSCC = g.getNumSCC();
	
	printf("%d\n", numSCC);
	for (v<v<int>>it i = scc.begin(); i != scc.end(); i++) {
		for (v<int>it j = i->begin(); j != i->end(); j++) {
			printf("%d ", (*j) + 1);
		}
		printf("-1\n");
	}
	
}
