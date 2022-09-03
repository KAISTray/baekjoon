#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
	int v, e;
	scanf("%d %d", &v, &e);
	
	vector<tuple<int, int, int> > edge;
	
	for (int i=0; i<5; i++) {
		int a,b,c;
		scanf("%d %d %d", &a, &b, &c);
		tuple<int, int, int> temp = make_tuple(a, b, c);
	}
	
	for (int i=0; i<5; i++) {
		printf("%d %d %d", get<0>(edge[i]), get<1>(edge[i]), get<2>(edge[i]));
	}
}
