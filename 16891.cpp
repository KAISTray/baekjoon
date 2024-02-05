#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

int sol(int N) {
	double f = M_PI / atan(1.0 / (double)N);
	if (f == (double)(int)f) {
		return (int)f - 1;
	} else {
		return (int)f;
	}
}

int main() {
	int N;
	scanf("%d", &N);
	printf("%d", sol(N));
}
