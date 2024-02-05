#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <algorithm>

#define ll unsigned long long int
#define lll __int128

ll M_Power(lll b, lll e, lll MOD) {
	if (e == 0) {
		return 1;
	}
	b %= MOD;
	if (e == 1) {
		return b;
	}
	lll h = M_Power(b, e / 2, MOD) % MOD;
	h = (h * h) % MOD;
	if (e % 2 == 1) {
		return (ll)(((b % MOD) * h) % MOD);
	} else {
		return (ll)h;
	}
}

bool Miller_Rabin(ll N) {
	if (N < 2) return false;
	
	if (N % 2 == 0 && N != 2) return false;
	
	int p[] = {2, 7, 61};
	for (int i = 0; i < 3; i++) {
		ll a = p[i];
		if (a == N) {
			return true;
		}
		ll n = N - 1;
		bool flag = false;
		ll test;
		while (n % 2 == 0) {
			n /= 2;
			test = M_Power(a, n, N);
			if (test == N - 1) {
				flag = true;
			}
		}
		if (test == 1) {
			flag = true;
		}
		
		if (!flag) {
			return false;
		}
	}
	return true;
}

int main() {
	int T;
	int cnt = 0;
	scanf("%d", &T);
	
	for (int i = 0; i < T; i++) {
		ll A;
		scanf("%lld", &A);
		if (Miller_Rabin((ll)2 * A + 1)) {
		cnt++;
		}	
	}
	printf("%d", cnt);
	
	
}

