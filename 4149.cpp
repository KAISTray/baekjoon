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

using namespace std;

ll M_Power(lll b, lll e, lll MOD) {
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
	
	int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41}; // 13
	for (int i = 0; i < 13; i++) {
		ll a = p[i];
		if (a == N) {
			return true;
		}
		ll n = N - 1;
		n /= 2;
		bool flag = false;
		do {
			ll test = M_Power(a, n, N);
			if (test == 1 || test == N - 1) {
				flag = true;
				break;
			}
			n /= 2;
		} while (n % 2 == 0);
		if (!flag) {
			return false;
		}
	}
	return true;
}

ll GCD(ll x, ll y) {
	while (x != 0 && y != 0) {
		if (x > y) {
			x %= y;
		} else {
			y %= x;
		}
	}
	return x + y;
}

ll abs_128(lll x) {
	if (x > 0) {
		return (ll)(x);
	} else {
		return (ll)(-x);
	}
}

ll Pollard_Rho(ll N) {
	if (N % 2 == 0) return 2;
	
	if (Miller_Rabin(N)) return N;
	
	lll x = rand() % (N - 2) + 2; // 1 ~ N-1
	lll y = x;
	lll p = rand() % 20 + 1;
	lll d = 1;
	
	while (d == 1) {
		x = (((x % N) * (x % N) % N) + p) % N;
		y = (((y % N) * (y % N) % N) + p) % N;
		y = (((y % N) * (y % N) % N) + p) % N;
		d = GCD(abs_128(x - y), N);
	}
	if (d == N) {
		return Pollard_Rho(N); // Retry
	} else{
		return Pollard_Rho(d); // If d is prime; return d. else factorize d again.
	}
}


int main() {
	ll x;
	vector<ll> factor;
	factor.clear();
	scanf("%lld", &x);
	while (x > 1) {
		//printf("Flag : testing %lld\n", x);
		ll p = Pollard_Rho(x);
		x /= p;
		factor.push_back(p);
	}
	sort(factor.begin(), factor.end());
	for (vector<ll>::iterator i = factor.begin(); i != factor.end(); i++) {
		printf("%lld\n", *i);
	}
}

