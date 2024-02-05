#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>
#include <queue>
#include <map>
#include <complex>

using namespace std;

#define ll long long int
#define lll __int128
#define ull unsigned long long int

typedef complex<double> cpx;


vector<cpx> FFT(vector<cpx> v) {
	//printf("Call FFT by vector : \n");
	//vector_debugger(v);
	int len = v.size();
	if (len == 1) {
		return v;
	}
	vector<cpx> even, odd;
	even.clear();
	odd.clear();
	for (int i = 0; i < len; i++) {
		if (i % 2) {
			odd.push_back(v[i]);
		} else {
			even.push_back(v[i]);
		}
	}
	
	vector<cpx> r_even = FFT(even), r_odd = FFT(odd);
	
	double arg = -2.0 * acos(-1) / len;
	cpx w = cpx(cos(arg), sin(arg));
	vector<cpx> ret(len);
	cpx pol = cpx(1, 0);
	for (int i = 0; i < len/2; i++) {
		ret[i] = r_even[i] + r_odd[i] * pol;
		ret[i + len / 2] = r_even[i] - r_odd[i] * pol;
		pol *= w; // turn w;
	}
	
	return ret;
}

vector<cpx> IFFT(vector<cpx> v) {
	reverse(++v.begin(), v.end());
	vector<cpx> ret = FFT(v);
	int N = (int)ret.size();
	for (int i = 0; i < N; i++) {
		ret[i] /= N;
	}
	return ret;
}

vector<ll> convolution(vector<ll> x, vector<ll> y) {
	int sx = (int)x.size();
	int sy = (int)y.size();
	int n = 1;
	while (n <= sx || n <= sy) {
		n *= 2;
	}
	n *= 2;
	
	x.resize(n);
	y.resize(n);
	vector<cpx> xc, yc;
	xc.clear();
	yc.clear();
	for (int i = 0; i < n; i++) {
		xc.push_back(cpx(x[i], 0));
		yc.push_back(cpx(y[i], 0));
	}
	
	xc = FFT(xc);
	yc = FFT(yc);
	
	vector<cpx> zc;
	zc.clear();
	for (int i = 0; i < n; i++) {
		zc.push_back(xc[i] * yc[i]);
	}
	
	
	vector<ll> ret;
	ret.clear();
	
	zc = IFFT(zc);
	
	for (int i = 0; i < n; i++) {
		ret.push_back(round(zc[i].real()));
	}
	
	return ret;
}

vector<ll> multiply (vector<ll> a, vector<ll> b) {
	vector<ll> aa;
	aa.clear();
	int na = a.size();
	for (int i = 0; i < 2 * na; i++) {
		aa.push_back(a[i % na]);
	}
	reverse(++b.begin(), b.end());
	return convolution(aa, b);
}


int main() {
	int n;
	scanf("%d", &n);
	vector<ll> a, b;
	a.clear();
	b.clear();
	for (int i = 0; i < n; i++) {
		ll x;
		scanf("%lld", &x);
		a.push_back(x);
	}
	for (int i = 0; i < n; i++) {
		ll x;
		scanf("%lld", &x);
		b.push_back(x);
	}
	vector<ll> c = multiply(a, b);
	
	printf("%lld", *max_element(c.begin(), c.end()));
}
