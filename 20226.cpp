#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <algorithm>

#define ll long long int
#define lll __int128

#define llmax 10000000000000000

using namespace std;

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
	
	int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43}; // 13
	for (int i = 0; i < 14; i++) {
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

vector<ll> factorization_vector(ll N) {
	ll x = N;
	vector<ll> factor;
	factor.clear();
	while (x > 1) {
		ll p = Pollard_Rho(x);
		x /= p;
		factor.push_back(p);
	}
	sort(factor.begin(), factor.end());
	return factor;
}

map<ll, int> factorization_map(ll N) {
	ll f = 0;
	int count = 0;
	vector<ll> factor = factorization_vector(N);
	map<ll, int> factors;
	for (vector<ll>::iterator i = factor.begin(); i != factor.end(); i++) {
		if (f != *i) {
			if (f != 0) {
				factors.insert({f, count});
			}
			f = *i;
			count = 1;
		} else {
			count++;
		}
	}
	factors.insert({f, count});
	return factors;
}

ll Euler_Phi(ll N) {
	if (N == 1) {
		return 1;
	}
	
	ll mult = 1, div = 1;
	map<ll, int> factors = factorization_map(N);
	for (map<ll, int>::iterator i = factors.begin(); i != factors.end(); i++) {
		ll p = i->first;
		mult *= (p - 1);
		div *= p;
	}
	return (N / div) * mult;
}

void factor_dfs(map<ll, int>::iterator e, ll x, vector<ll>& div, map<ll, int>& fac) {
	if (e == fac.end()) {
		div.push_back(x);
		return;
	}
	ll n = 1;
	for (int i = 0; i <= e->second; i++) {
		e++;
		factor_dfs(e, x * n, div, fac);
		e--;
		n *= e->first;
	}
	return;
}

vector<ll> factor_vector(ll N) {
	vector<ll> div;
	div.clear();
	if (N == 1) {
		div.push_back(1);
		return div;
	}
	map<ll, int> fac = factorization_map(N);
	factor_dfs(fac.begin(), 1, div, fac);
	sort(div.begin(), div.end());
	/*
	IFDEBUG {
		printf("Input : %lld\n", N);
		printf("Output :");
		for (vector<ll>::iterator i = div.begin(); i != div.end(); i++) {
			printf(" %lld", *i);
		}
		printf("\n");
	}
	*/
	return div;
}

vector<ll> primepower_vector(ll N) {
	vector<ll> ppv;
	ppv.clear();
	map<ll, int> factors = factorization_map(N);
	
	for (map<ll, int>::iterator i = factors.begin(); i != factors.end(); i++) {
		ll K = M_Power(i->first, i->second, N);
		ppv.push_back(K);
	}
	
	return ppv;
}


int main() {
	while (true) {
		ll N;
		scanf("%lld", &N);
		ll min_v = N + 2;
		if (N == 0) {
			break;
		}
		if (Miller_Rabin(N)) {
			printf("%lld\n", min_v);
			continue;
		}
		vector<ll> ans_set;
		ans_set.clear();
		vector<ll> div = factor_vector(N);
		for (vector<ll>::iterator i = div.begin(); i != div.end(); i++) {
			vector<ll>::iterator fx = lower_bound(div.begin(), div.end(), (ll)sqrt(N / *i));
			ll U = N / *i;
			for (vector<ll>::iterator j = fx - 5; j < fx + 5; j++) {
				if (j >= div.begin() && j < div.end()) {
					if (U % *j == 0) {
						min_v = min(min_v, U / *j + *i + *j);
					}
				}
			}
		}
		printf("%lld\n", min_v);
	}
}
