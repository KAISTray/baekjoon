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
#define DEBUG false
#define test_fuzzer false

using namespace std;





void map_debugger(map<ll, int> m) {
	for (map<ll, int>::iterator i = m.begin(); i != m.end(); i++) {
		printf("map elem : %lld %d\n", i->first, i->second);
	}
}

void vector_debugger(vector<ll> m) {
	for (vector<ll>::iterator i = m.begin(); i != m.end(); i++) {
		printf("vec elem : %lld\n", *i);
	}
}

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

bool check_two_squares(ll N) {
	if (DEBUG) printf("call check_two_squares by %lld\n", N);
	vector<ll> factor;
	factor.clear();
	ll x = N;
	while (x > 1) {
		//printf("Flag : testing %lld\n", x);
		ll p = Pollard_Rho(x);
		x /= p;
		factor.push_back(p);
	}
	sort(factor.begin(), factor.end());
	ll f = 0;
	int count = 0;
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
	
	if (DEBUG) printf("== Check_two_squares for %lld factors check==\n", N);
	if (DEBUG) map_debugger(factors);
	
	for (map<ll, int>::iterator i = factors.begin(); i != factors.end(); i++) {
		if (i->first % 4 == 3 && i->second % 2 == 1) {
			return false;
			break;
		}
	}
	return true;
}

vector<ll> two_squares(ll N) {
	if (DEBUG) printf("call two_squares by %lld\n", N);
	vector<ll> u;
	u.clear();
	if (N % 4 == 0) {
		vector<ll> r = two_squares(N / 4);
		u.push_back(r[0] * 2);
		u.push_back(r[1] * 2);
	} else {
		vector<ll> factor;
		factor.clear();
		ll x;
		x = N;
		while (x > 1) {
			//printf("Flag : testing %lld\n", x);
			ll p = Pollard_Rho(x);
			x /= p;
			factor.push_back(p);
		}
		sort(factor.begin(), factor.end());
		
		if (DEBUG) vector_debugger(factor);
		
		ll f = 0;
		int count = 0;
		map<ll, int> factors;
		factors.clear();
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
		
		if (DEBUG) map_debugger(factors);
		
		ll x1 = 1, x2 = 0, y = 1;
		for (map<ll, int>::iterator i = factors.begin(); i != factors.end(); i++) {
			
			if (DEBUG) printf("Iterate factor %lld powers %lld\n", i->first, i->second);
			

			y *= M_Power(i->first, (i->second / 2), N);
			
			if (DEBUG) printf("Current y : %lld\n", y);
			
			if (i->second % 2 == 1) { // assured that i->first = 4k + 1 or 2
				ll v = i->first;
				ll t1, t2;
				if (v == 2) { // only exception
					t1 = 1;
					t2 = 1;
				} else if (v == 5) {
					t1 = 2;
					t2 = 1;					
				} else { // 
					// TODO : find t1 and t2
					ll p = i->first;
					ll x, a;
					
					// some process to determine x s.t. (x * x + 1) = 0 mod p = 4k + 1
					// TODO
					// find quadratic non-residue mod p, a
					// and x = a^((p - 1) / 4) (mod p).
					
					// for small a or arbitrary a
					while (true) {
						//printf("Flaggg\n");
						a = rand() % (100000) + 1; //some decision process
						if (DEBUG) printf("Jacobi for a = %lld\n", a);
						ll t = 1, tp = p, ta = a;
						while (ta != 0) {
							while (ta % 2 == 0) {
								ta /= 2;
								if (tp % 8 == 3 || tp % 8 == 5) {
									t = -t;
								}
							}
							swap(ta, tp);
							if (ta % 4 == 3 && tp % 4 == 3) {
								t = -t;
							}
							ta = ta % tp;
						}
						if (tp == 1 && t == -1) {
							break;
						}
					}
					
					//printf("a value : %lld\n", a);
					
					x = M_Power(a, (p - 1) / 4, p);
					
					if (DEBUG) printf("output x : %lld\n", x);
					
					while (true) {
						
						if (x > p) { // p should be always larger in here
							swap(x, p);
						}
						
						if (DEBUG) printf("%lld %lld \n", x, p);
						
						if ((lll)p * (lll)p > (lll)i->first && (lll)i->first > (lll)x * (lll)x) {
							t2 = x;
							t1 = p % x;
							break;
						}
						
						p %= x; //now x should be larger
						
					}
				}
				ll tx1 = x1, tx2 = x2; //temp value for x
				x1 = t1 * tx1 + t2 * tx2;
				x2 = (ll)abs((long long int)t1 * (long long int)tx2 - (long long int)t2 * (long long int)tx1);
				
				if (DEBUG) printf("Calculated t1 : %lld, t2 : %lld\n", t1, t2);
				
				if (DEBUG) printf("Updated x1 : %lld, x2 : %lld\n", x1, x2);
				
			}
		}
		u.push_back(x1 * y);
		u.push_back(x2 * y);
	}
	return u;
}

vector<ll> three_squares(ll N) {
	if (DEBUG) printf("call three_squares by %lld\n", N);
	vector<ll> u;
	u.clear();
	
	// exception
	if (N < 100) {
		if (DEBUG) printf("small number\n");
		for (ll i = 1; i <= (ll)sqrt(N); i++) {
			ll rem = N - i * i;
			if (check_two_squares(rem)) {
				u = two_squares(rem);
				u.push_back(i);
				return u;
				break;
			}
		}
	}
	
	
	
	if (N % 4 == 0) {
		vector<ll> r = three_squares(N / 4);
		u.push_back(r[0] * 2);
		u.push_back(r[1] * 2);
		u.push_back(r[2] * 2);
	} else if (N % 8 == 3) {
		ll x = (ll)sqrt(N) - 1, p;
		if (x % 2 == 0) {
			x -= 1;
		}
		do {
			x -= 2;
			p = (N - (x * x)) / 2;
		} while (!check_two_squares(p));
		vector<ll> r = two_squares(p);
		
		u.push_back(x);
		u.push_back(r[0] + r[1]);
		if (r[0] > r[1]) {
			u.push_back(r[0] - r[1]);
		} else {
			u.push_back(r[1] - r[0]);
		}
		
	} else {
		ll x = (ll)sqrt(N) - 1, p;
		if (x % 2 == N % 2) {
			x -= 1;
		}
		do {
			x -= 2;
			p = (N - (x * x));
		} while (!check_two_squares(p));
		vector<ll> r = two_squares(p);
		u.push_back(x);
		u.push_back(r[0]);
		u.push_back(r[1]);
	}
	return u;
}

vector<ll> pos_filter(vector<ll> i_vec) {
	vector<ll> ans;
	ans.clear();
	
	for (vector<ll>::iterator i = i_vec.begin(); i != i_vec.end(); i++) {
		long long int x = (long long int)(*i);
		if (x > 0) {
			ans.push_back((ll)(x));
		} else {
			ans.push_back((ll)(-x));
		}
	}
	return ans;
}



int main_proc(ll N) {
	vector<ll> factor;
	factor.clear();
	ll x = N; //copy
	while (x > 1) {
		//printf("Flag : testing %lld\n", x);
		ll p = Pollard_Rho(x);
		x /= p;
		factor.push_back(p);
	}
	sort(factor.begin(), factor.end());
	
	int ans = 0;
	// Filter for 4->3
	x = N;
	int count = 0;
	int count_4 = 0;
	for (vector<ll>::iterator i = factor.begin(); i != factor.end(); i++) {
		
		if (next(i) == factor.end()) {
			break;
		}
		
		ll f1 = *i;
		i++;
		ll f2 = *i;
		
		if (f1 == 2 && f2 == 2){
			count += 2;
		} else {
			break;
		}
	}
	x = N >> count;
	if (x % 8 == 7) {
		ans = 4;
		count_4 = count / 2;
	} else {
		// Filter for 3->2
		ll f = 0;
		int count = 0;
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
		
		for (map<ll, int>::iterator i = factors.begin(); i != factors.end(); i++) {
			if (i->first % 4 == 3 && i->second % 2 == 1) {
				ans = 3;
				break;
			}
		}
		
		if (ans != 3) {
			ans = 2;
		}
		
	}

	if ((ll)sqrt(N) * (ll)sqrt(N) == N) {
		ans = 1;
	}
	
	if (!test_fuzzer) printf("%d\n", ans);
	
	if (ans == 4) {
		ll a1 = M_Power(2, (count_4 + 1), N);
		vector<ll> a = pos_filter(three_squares(N - a1 * a1));
		if (!test_fuzzer) printf("%lld %lld %lld %lld", (a1), (a[0]), (a[1]), (a[2]));
		if (a1 * a1 + a[0] * a[0] + a[1] * a[1] + a[2] * a[2] != N) {
			return 1;
		}
	} else if (ans == 3) {
		vector<ll> a = pos_filter(three_squares(N));
		if (!test_fuzzer) printf("%lld %lld %lld", (a[0]), (a[1]), (a[2]));
		if (a[0] * a[0] + a[1] * a[1] + a[2] * a[2] != N) {
			return 1;
		}
	} else if (ans == 2) {
		vector<ll> a = pos_filter(two_squares(N));
		if (!test_fuzzer) printf("%lld %lld", (a[0]), (a[1]));
		if (a[0] * a[0] + a[1] * a[1] != N) {
			return 1;
		}
	} else {
		if (!test_fuzzer) printf("%lld", (ll)(sqrt(N)));
	}
		
	return 0;
	
}



int main() {
	
	
	
	//return 0;
	if (!test_fuzzer) {
		ll x;
		scanf("%lld", &x);
		main_proc(x);
	} else {
		for (int i = 1; i < 100000000; i++) {
			ll x;
			int rnd = rand() % 10;
			if (rnd < 7) {
				x = (((ll)rand() << 30) + ((ll)rand()));
			} else {
				x = (ll)rand() % 100000;
			}
			
			//printf("Test : %lld\n", x);
			int r = main_proc(x);
			if (r) {
				printf("Test failed with %lld\n", x);
				return 0;
			}
			if (i % 100 == 0) {
				printf("passed %d\n", i);
			}
		}
	}
	return 0;
}

