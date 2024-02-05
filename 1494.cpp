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

using namespace std;

ll GCD(ll x, ll y) {
	if (x * y == 0) {
		return 0;
	}
	while (x != 0 && y != 0) {
		if (x > y) {
			x %= y;
		} else {
			y %= x;
		}
	}
	return x + y;
}

ll naive(ll f, ll s, ll idx) {
	
}

int main() {
	ll f, s, N;
	scanf("%lld %lld %lld", &f, &s, &N);
	// 21 12 9 3 6 3 3 0 3 3 0 3 3 0 ...
	u.push_back(f);
	u.push_back(s);
	int i = 2;
	ll v = 0, g = GCD(f, s);
	while (true) { // f : S_(i - 2), s : S_(i - 1), v = S_i;
		v = abs(f - s); // s_2 = abs(S_0 - S_1)
		u.push_back(v); // u[2] = v;
		if (v == s && s == g) { // g g (0) ..
			break;
		} else {
			f = s;
			s = v;
			i++;
		}
	}
	vector<ll> ans(N);
	for (int j = 0; j < N; j++) {
		ll idx;
		scanf("%lld", &idx);
		if (idx < i) {
			ans[j] = u[idx];
		} else {
			ans[j] = (idx - i) % 3 == 0 ? 0 : g;
		}
	}
	
	for (int j = 0; j < N; j++) {
		printf("%lld\n", ans[j]);
	}
}
