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
			a[end].push_back(init); //������ �׷��� : W��° ������ �߽��̵Ǵ�..! 
		}
		
		vector<int> min(n), visited(n);	
		deque<int> valid; //��ȿ�� ����� �ε����� 
		deque<int> visit; //�湮�� ���� 
		
		int W, now;
		scanf("%d", &W);
		
		visit.push_front(W);
		
		while(true) { //��ȸ���� ���
		// ���� W���� �����ؼ� �ֺ� �ϳ��� Ž���ϱ� 
			
			
			now = visit.pop_back();
			//visit_pop_back�� �̾ƿ�
			//�� ��ó�� �ֵ� �� ��ȸ��
			while(true) {
				if (min[n] == 0) {
					
				} 
			}
			
		}
	}
}
