#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;




int main() {
	int N, S;
	
	scanf("%d %d", &N, &S);
	
	vector<int> vr, vl;
	vr.clear();
	vl.clear();
	
	for (int i = 0; i < N; i++) {
		int x;
		scanf("%d", x);
		if (i < N/2) {
			vr.push_back(x);
		} else {
			vl.push_back(x);
		}
	}
	map<int, int> sSum;
	sSum.clear();
	
	for (int i = -2000000; i <= 2000000; i++) {
		sSum.insert({i, 0});
	}
	
	int r = vr.size(), l = vl.size();
	
	for (int i = 0; i < (1 << r); i++) {
		int pSum = 0;
		for (int j = 0; j < r; j++) {
			if (i & (1 << j)) {
				pSum += vr[j];
			}
		}
		sSum[pSum] += 1;
	}
	
	for (int i = 0; i < (1 << l); i++) {
		int pSum = 0;
		for (int j = 0; j < r; j++) {
			if (i & (1 << j)) {
				pSum += vl[j];
			}
		}
	}
	
}
