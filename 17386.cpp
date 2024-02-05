#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <stack>
#include <deque>
#include <queue>
#include <algorithm>
#include <complex>
#include <string.h>

#ifndef __int128
#define __int128 long long int
#endif

#define ll long long int
#define lll __int128

#define v vector
#define it ::iterator

#define GeometryDefaultType long long int
#define point pair<GeometryDefaultType, GeometryDefaultType>
#define vec pair<point, point>

using namespace std;

GeometryDefaultType sign(GeometryDefaultType n) {
	return (n == 0) ? 0 : ((n > 0) ? 1 : -1);
}

GeometryDefaultType ccw(point p1, point p2, point p3) {
	return sign(p1.first * p2.second + p2.first * p3.second + p3.first * p1.second - p1.second * p2.first - p2.second * p3.first - p3.second * p1.first);
}

bool cross(vec a, vec b) {
	point s1 = a.first, e1 = a.second;
	point s2 = b.first, e2 = b.second;
	
	GeometryDefaultType c1 = ccw(s1, e1, s2) * ccw(s1, e1, e2);
	GeometryDefaultType c2 = ccw(s2, e2, s1) * ccw(s2, e2, e1);
	
	if (c1 == 0 && c2 == 0) {
		if (s1 > e1) {
			swap(s1, e1);
		}
		if (s2 > e2) {
			swap(s2, e2);
		}
		return (s2 <= e1) && (s1 <= e2); // crossed?
	} else {
		return (c1 <= 0 && c2 <= 0);
	}
}

int main() {
	
	int a, b, c, d, e, f, g, h;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	scanf("%d %d %d %d", &e, &f, &g, &h);
	vec v1(make_pair(a, b), make_pair(c, d));
	vec v2(make_pair(e, f), make_pair(g, h));
	printf("%lld", cross(v1, v2));
}
