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
				if (scc_finished[*i]) {
					continue;
				}
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
		/* section for SCC End */
		
		
		void update() {
			scc_done = false;
		}
		
		
	public:
		dir_graph() {
			num_node = 0;
			graph.clear();
			update();
		}

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

		void resize(int _vertex) {
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
		
		vector<int> getIdxSCC() {
			if (!scc_done) {
				SCC();
			}
			
			return scc_idx;
		}
};

class sat_formula {
	typedef int sat_var;
	private:
		vector<vector<sat_var>> F;
		int num_var;
		int num_clause;
		int num_maxL;
		dir_graph graph;
		
		int getVarName(sat_var v) {
			return (int)v;
		}
		
		sat_var satVarName(int idx) {
			return (sat_var)idx;
		}
		
		int getListIdx(sat_var v) {
			return v > 0 ? (v - 1) : -v - 1 + num_var;
		}
		
		sat_var getVar(int idx) {
			return satVarName((idx >= num_var ? -1 : 1) * (idx % num_var));
		}
		
	public:
		sat_formula() {
			F.clear();
			num_var = 0;
		}
		
		void set(vector<vector<int>> _F) {
			F = _F;
			int max_var = 0;
			for (v<v<sat_var>>it p1 = _F.begin(); p1 != _F.end(); p1++) {
				vector<sat_var> C = *p1;
				for (v<sat_var>it p2 = C.begin(); p2 != C.end(); p2++) {
					sat_var L = *p2;
					max_var = max(max_var, abs(L));
				}
			}
			
			num_var = max_var;
			set_F(_F);
		}
		
		void set_F(vector<vector<int>> _F) {
			graph.resize(2 * num_var);
			for (v<v<sat_var>>it p1 = _F.begin(); p1 != _F.end(); p1++) {
				vector<sat_var> C = *p1;
				graph.add(getListIdx(-C[0]), getListIdx(C[1]));
				graph.add(getListIdx(-C[1]), getListIdx(C[0]));
			}
		}
		
		sat_formula(vector<vector<sat_var>> _F) {
			set(_F);
		}
		
		sat_formula(vector<vector<sat_var>> _F, int _max_var) {
			num_var = _max_var;
			set_F(_F);
		}
		
		vector<vector<sat_var>> getFormula() {
			return F;
		}
		
		int getNumVar() {
			return num_var;
		}
		
		int getNumClause() {
			return num_clause;
		}
		
		bool sat2_sat() {
			// find SCC
			vector<int> scc = graph.getIdxSCC();
			bool ans = true;
			for (int i = 1; i <= num_var; i++) {
				if (scc[getListIdx(i)] == scc[getListIdx(-i)]) {
					ans = false;
				}
			}
			return ans;
		}
		
		vector<bool> sat2_sol() {
			vector<int> scc = graph.getIdxSCC();
			vector<bool> ans;
			ans.clear();
			if (!sat2_sat()) {
				return ans; // err : not satisfiable
			}
			for (int i = 1; i <= num_var; i++) {
				ans.push_back(scc[getListIdx(i)] < scc[getListIdx(-i)]);
			}
			
			return ans;
		}
};

void sol() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<vector<int>> f;
	vector<bool> fa(n + 1, false);
	f.clear();
	char s[n+1];
	scanf("%s", s);
	for (int i = 0; i < n; i++) {
		if (s[i] == 'A') {
			fa[i + 1] = true;
		}
	}
	bool aa = false;
	for (int i = 0; i < m; i++) {
		vector<int> tmp;
		tmp.clear();
		int t1, t2;
		scanf("%d %d", &t1, &t2);
		
		if (fa[abs(t1)] && fa[abs(t2)]) {
			if (t1 + t2 == 0) {
				continue;
			}
			printf("FALSE\n");
			aa = true;
			break;
		}
		
		tmp.push_back(t1);
		tmp.push_back(t2);
		f.push_back(tmp);
		tmp.clear();
		
	}
	if (!aa) {
		sat_formula F(f, n);
		bool isSat = F.sat2_sat();
		if (!isSat {
			printf("FALSE\n");
		} else {
			printf("TRUE\n");
		}
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		sol();
	}
}
