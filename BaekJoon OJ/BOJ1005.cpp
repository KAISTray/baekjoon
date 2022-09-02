#include <stdio.h>
#include <vector>
#include <deque>
#include <stdlib.h>


using namespace std;

int main() {
	int T,t;
	scanf("%d", &T);
	
	for (t=0; t<T; t++) {
		int n,k;
		scanf("%d %d", &n, &k);
		
		vector<int> d; //time req
		d.push_back(0);
		
		for (int i=0; i<n; i++) {
			int delay;
			scanf("%d", &delay);
			d.push_back(delay);
		}
		
		vector<vector<int> >rule(n+1), ruleInv(n+1); //rules
		vector<int> input(n+1); //input dimensions. the node where input dim is 0 will be the 1st.
		input[0] = -1;
		
		//always node 0 must be NULL
		
		
		for (int i=0; i<k; i++) {
			int init, fin;
			scanf("%d %d", &init, &fin);
			rule[init].push_back(fin);
			ruleInv[fin].push_back(init);
			input[fin]++;
		}
		
		vector<int> min(n+1);
		
		int W;
		scanf("%d", &W);
		
		deque<int> goingVisit;
		vector<int> visited(n+1);
		
		bool allVisit;
		while (true) {
			for (int i=1; i<=n; i++) {
				if (input[i] == 0) {
					goingVisit.push_front(i);
				}
			}
			while(!goingVisit.empty()) {
				int cur = goingVisit.back();
				
				int max = 0;
				while (!ruleInv[cur].empty()) {
					int nowPt;
					nowPt = ruleInv[cur].back();
					ruleInv[cur].pop_back();
					if (min[nowPt] > max) {
						max = min[nowPt];
					}
				}
				min[cur] = max + d[cur];
				while (!rule[cur].empty()) {
					int pushIn;
					pushIn = rule[cur].back();
					rule[cur].pop_back();
					input[pushIn]--;
				}
				goingVisit.pop_back();
			}
		}
		
		printf("%d\n", &min[W]);
		
		
	}
}
