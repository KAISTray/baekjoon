#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>
#include <queue>
#include <map>
#include <complex>


using namespace std;

// O (N log N)

int q_total;

void debug(vector<int> t) {
	printf("vector debug\n");
	for (int i = 0; i < 10; i++) {
		printf("%d : %d | ", i, t[i]);
	}
	printf("\n");
}

void debug(list<int> t) {
	printf("list debug\n");
	int cnt = 0;
	for (list<int>::iterator i = t.begin(); i != t.end(); i++) {
		printf("%d : %d | ", cnt, *i);
		cnt++;
	} 
	printf("\n");
}

vector<list<int>> pos(100001); // value k list : pos[k] 
vector<int> cnt(100001, 0), bucket(500, 0); 
vector<int> A(100001, 0);

void dump() {
	printf("==============cnt debug=============\n");
	debug(cnt);
	printf("==============buk debug=============\n");
	debug(bucket);
	for (int i = 4; i < 8; i++) {
		printf("============pos %d debug=============\n", i);
		debug(pos[i]);
	}
}

class Query {
	private:
		int _L, _R;
		int _idx;
		int _N;
		int _sL;
	public:
		Query(int L, int R, int N) {
			_L = L;
			_R = R;
			_idx = q_total++;
			_N = N;
			_sL = L / (int)sqrt(N);
		}
		
		int left() {
			return _L;
		}
		
		int right() {
			return _R;
		}
		
		int s_left() {
			return _sL;
		}
		
		int idx() {
			return _idx;
		}
		
		bool operator < (Query t) {
			return (_sL == t.s_left()) ? (_R < t.right()) : (_sL < t.s_left());
		}
};

void Q_Add(int x, bool dir, int sN) {
	//printf("QAdd for %d\n", x);
	auto &d = pos[A[x]];
	int n = 0;
	if (!d.empty()) {
		n = d.back() - d.front();
		cnt[n]--;
		bucket[n / sN]--;
	}
	
	if (dir) {
		d.push_back(x);
	} else {
		d.push_front(x);
	}
	
	n = d.back() - d.front();
	cnt[n]++;
	bucket[n / sN]++;
}

void Q_Sub(int x, bool dir, int sN) {
	//printf("QSub for %d\n", x);
	auto &d = pos[A[x]];
	int n = d.back() - d.front();
	
	cnt[n]--;
	bucket[n / sN]--;
	
	if (dir) {
		d.pop_back();
	} else {
		d.pop_front();
	}
	
	if (!d.empty()) {
		n = d.back() - d.front();
		cnt[n]++;
		bucket[n / sN]++;
	}
}

int q_execute(int sN) {
	//printf("Execute\n");
	for (int i = 499; i >= 0; i--) {
		if (bucket[i] != 0) {
			for (int j = sN - 1; j >= 0; j--) {
				if (cnt[i * sN + j] > 0) {
					return i * sN + j; 
				}
			}			
		}
	}
	return 0;
}

int main() {
	pos.clear();
	q_total = 0;
	
	int N, K;
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		int t;
		scanf("%d", &t);
		A[i+1] = t;
	}
	
	int M;
	scanf("%d", &M);
	
	int n = (int)sqrt(N);
	
	vector<Query> q;
	q.clear();
	
	for (int i = 0; i < M; i++) {
		int L, R;
		scanf("%d %d", &L, &R);
		Query t(L, R, N);
		q.push_back(t);
	}
	
	vector<int> ans(100001, 0);
	
	sort(q.begin(), q.end());
	
	int l = 1, r = 1;
	
	Q_Add(1, true, n);
	
	for (int i = 0; i < M; i++) { // execute
		int idx = q[i].idx();
		// expand if needed
		while(q[i].left() < l) {
			l--;
			Q_Add(l, false, n);
		}
		
		while(r < q[i].right()) {
			r++;
			Q_Add(r, true, n);
		}
		
		// shrink if needed
		while(l < q[i].left()) {
			Q_Sub(l, false, n);
			l++;
		}
		
		while(q[i].right() < r) {
			Q_Sub(r, true, n);
			r--;
		}
		
		// get answer
		//dump();
		int s = q_execute(n);
		
		ans[idx] = s;
	}
	
	for (int i = 0; i < M; i++) {
		printf("%d\n", ans[i]);
	}
}
