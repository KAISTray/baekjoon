#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <algorithm>
#include <string.h>

#define ll long long int
#define lll __int128
#define FLAG printf("Flag\n");
#define D(X) dump(X)

using namespace std;

ll h[111111], hc[111111];



void dump(array<int, 11> x) {
	for (int i = 0; i < 11; i++) {
		printf("%d ", x[i]);
	}
	printf("\n");
}

void synch() {
	memcpy(hc, h, sizeof h);
}

array<int, 11> vector_increment (array<int, 11> iter_init, array<int, 11> iter_end, array<int, 11> x) {
	x[10]++;
	for (ll i = 10; i >= 0; i--) {
		if (x[i] > iter_end[i]) {
			if (i > 0) {
				x[i] = iter_init[i];
				x[i - 1]++;
			} else {
				return x;
			}
		} else {
			return x;
		}
	}
}

array<int, 11> axis, axis_inv;
array<int, 11> s_axis;

ll idx[55][2];

void init() {
	for (ll i = 0; i < 11; i++) {
		axis[i] = i;
		axis_inv[i] = i;
	}
	int t = 0;
	for (int i = 0; i < 11; i++) {
		for (int j = i + 1; j < 11; j++) {
			idx[t][0] = i;
			idx[t][1] = j;
			t++;
		}
	}
	return;
}

void state_update() {
	for (ll i = 0; i < 11; i++) {
		axis_inv[axis[i]] = i;
	}
}

ll get_id(array<int, 11> x) {
	//printf("GetId Call \n");
	//D(x);
	ll id = 0;
	state_update();
	for (ll i = 0; i < 11; i++) {
		id = id * s_axis[i] + x[axis_inv[i]];
	}
	return id;
}

array<int, 11> get_id_from_n(ll n) {
	array<int, 11> id;
	state_update();
	for (ll i = 10; i >= 0; i--) {
		id[axis_inv[i]] = n % s_axis[i];
		n /= s_axis[i];
	}
	return id;
}

void dump_h() {
	ll n = 12;
	array<int, 11> a = get_id_from_n(0), b = get_id_from_n(n - 1), k = get_id_from_n(0);
	//D(a);
	//D(b);
	for (int i = 0; i < n; i += s_axis[axis[10]]) {
		for (int j = 0; j < s_axis[axis[10]]; j++) {
			printf("%lld ", h[get_id(k)]);
			k = vector_increment(a, b, k);
		}
		printf("\n");
	}
}

void convert(array<int, 11> x, array<int, 11> y) {
	//printf("Update %lld to %lld\n", get_id(x), get_id(y));
	h[get_id(x)] = hc[get_id(y)];
	//dump_h();
	return;
}



void execute(ll op, array<int, 11> a, array<int, 11> b) {
	if (op <= 66) synch();
	
	if (op <= 11) { // op 1 ~ op 11
		op--;
		
		// op-dimension flip : (before filping + after filping) = a[op] + b[op] 
		for (array<int, 11> i = a; i[0] <= b[0]; i = vector_increment(a, b, i)) {
			//D(i);
			array<int, 11> x = i;
			//x_new + x_old = a + b
			x[op] = a[op] + b[op] - x[op];
			// convert for new hyper-array
			convert(x, i);
		}
		
	} else if (op <= 66) { // op 12 ~ op 66
		op -= 12;
		// use only 2 dimension!
		int t1, t2;
		t1 = idx[op][0];
		t2 = idx[op][1];
		bool flag = (b[t1] - a[t1] < b[t2] - a[t2]);
		int t = flag ? (b[t1] - a[t1] + 1) / 2 : (b[t2] - a[t2] + 1) / 2;
		for (array<int, 11> i = a; i[0] <= b[0]; i = vector_increment(a, b, i)) {
			array<int, 11> x = i;
			bool flag2 = (x[t2] - x[t1] >= a[t2] - a[t1]);
			bool flag5 = (x[t2] - x[t1] <= b[t2] - b[t1]);
			bool flag3 = (x[t1] + x[t2] < a[t1] + b[t2]);
			bool flag4 = (x[t1] + x[t2] > b[t1] + a[t2]);
			if (
			(x[flag ? t1 : t2] < a[flag ? t1 : t2] + t) &&
			(flag ? flag2 : !flag2) &&
			(flag ? flag3 : !flag4)) {
				if (flag) x[t2]++;
				else x[t1]--;
			} else if (
			(x[flag ? t1 : t2] >= a[flag ? t1 : t2] + t) &&
			(flag ? flag5 : !flag5) &&
			(flag ? flag4 : !flag3)) {
				if (flag) x[t2]--;
				else x[t1]++;
			} else if (x[flag ? t2 : t1] < a[flag ? t2 : t1] + t) {
				if (flag) x[t1]--;
				else x[t2]++;
			} else {
				if (flag) x[t1]++;
				else x[t2]--;
			}
			convert(x, i);
		}
	} else { // Op 67 ~ 121
		op -= 67;
		// idea : swap the axis!
		swap(axis[idx[op][0]], axis[idx[op][1]]);
	}
	return;
}

int main() {
	
	init();
	ll n = 1;
	
	for (ll i = 0; i < 11; i++) {
		ll t;
		scanf("%lld", &t);
		s_axis[i] = t;
		n *= t;
	}
	for (ll i = 0; i < n; i++) {
		scanf("%lld", &h[i]);
	}
	
	ll num_q;
	scanf("%lld", &num_q);
	
	for (ll i = 0; i < num_q; i++) {
		ll op;
		scanf("%lld", &op);
		array<int, 11> a, b;
		if (op <= 66) { // op m1 n1 ... w1 m2 n2 ... w2  
			for (ll i = 0; i < 11; i++) {
				scanf("%lld", &a[i]);
			}
			for (ll i = 0; i < 11; i++) {
				scanf("%lld", &b[i]);
			}
			for (ll i = 0; i < 11; i++) {
				a[i]--;
				b[i]--;
			}
		}
		
		execute(op, a, b);
	}
	
	// output..
	for (int i = 0; i < 11; i++) {
		printf("%d ", s_axis[axis[i]]);
	}
	printf("\n");
	array<int, 11> a = get_id_from_n(0), b = get_id_from_n(n - 1), k = get_id_from_n(0);
	//D(a);
	//D(b);
	for (int i = 0; i < n; i += s_axis[axis[10]]) {
		for (int j = 0; j < s_axis[axis[10]]; j++) {
			printf("%lld ", h[get_id(k)]);
			k = vector_increment(a, b, k);
		}
		printf("\n");
	}
}
