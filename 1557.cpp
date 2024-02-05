#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <math.h>

using namespace std;

int NUM_MAX_Eratos = 100000;
int NUM_MAX_MOBIUS = 55000;

vector<bool> isPrime_Eratos(NUM_MAX_Eratos, true);
vector<int> prime;
vector<int> mobius(NUM_MAX_MOBIUS, 0);

void vec_init() {
    mobius[0] = 0;
    mobius[1] = 1;
    for (int i = 1; i < NUM_MAX_MOBIUS; i++) {
        if (mobius[i]) {
            for (int j = 2 * i; j < NUM_MAX_MOBIUS; j += i) {
                mobius[j] -= mobius[i];
            }
        }
    }

    for (int i = 0; i < NUM_MAX_Eratos; i++) {
        isPrime_Eratos[i] = true;
    }
    isPrime_Eratos[0] = isPrime_Eratos[1] = false;
    for (int i = 2; i <= (int)(sqrt(NUM_MAX_Eratos)); i++) {
        if (isPrime_Eratos[i]) {
            for (int j = i * i; j < NUM_MAX_Eratos; j += i) {
                isPrime_Eratos[j] = false;
            }
        }
    }
}

// N 이하의 SFI가 몇개인가?
int num_SFI(int N) {
    // f(N) = Sum i = 1 to sqrt(N); mobius(i) * [N / i^2]
    int ret = 0;
    for (int i = 1; i * i < N; i++) {
        ret += mobius[i] * (int)(N / (i * i));
    }
    return ret;
}

// N 이하의 수 중 가장 큰 SFI number
int nearest_SFI(int N) {
    for (int i = N; true; i--) {
        bool flag = true;
        for (vector<int>::iterator jp = prime.begin(); jp != prime.end(); jp++) {
            if ((*jp) * (*jp) > N) {
                break;
            }
            //printf("Checking with int %d and prime %d\n", i, *jp);
            if (i % ((*jp) * (*jp)) == 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return i;
            break;
        }
    }

    // ASSERT(NO_ACCESS);
}

// Binary Search with num_SFI - return kth SFI
int SFI(int min, int max, int k) {

    if (k <= 28) {
        vector<int> inits = {1, 2, 3, 5, 6, 7, 10, 11, 13, 14, 15, 17, 19, 21, 22, 23, 26, 29, 30, 31, 33, 34, 35, 37, 38, 39, 41, 42};    
        return inits[k - 1];
    }

    //printf("Searching for %d to %d with mid %d, targeting %d\n", min, max, (min + max) / 2, k);
    int mid = (int)(((long long int)min + (long long int)max) / 2);
    int n = num_SFI(mid);
    if (n == k) {
        return nearest_SFI(mid);
    } else if (n < k) {
        return SFI(mid, max, k);
    } else {
        return SFI(min, mid, k);
    }
}


int main() {
    vec_init();
    int K;
    scanf("%d", &K);
    prime.clear();
    for (int i = 0; i < NUM_MAX_Eratos; i++) {
        if (isPrime_Eratos[i]) {
            prime.push_back(i);
        }
    }

    printf("%d", SFI(0, 2*K, K));

    return 0;
}
