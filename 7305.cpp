#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

// a ~ z, + * / ? : 30 alphabets


void algo_7305() {
	int num_word, i, j;
	scanf("%d", &num_word);
	vector<int> alphabet_occur(30, 0);
	char word[30];
	for (i = 0; i < num_word; i++) {
		scanf("%s", word);
		for (j = 0; word[j] != 0; j++) {
			switch (word[j]) {
				case '+':
					alphabet_occur[26] += 1;
					break;
				case '*':
					alphabet_occur[27] += 1;
					break;
				case '/':
					alphabet_occur[28] += 1;
					break;
				case '?':
					alphabet_occur[29] += 1;
					break;
				default:
					alphabet_occur[(int)(word[j] - 'a')];
					break;
			}
		}
	}
	
	
	return;
}


int main() {
	int num_test;
	scanf("%d", &num_test);
	
	for (;num_test > 0; num_test--) {
		algo_7305();
	}
	
	return 0;	
}

