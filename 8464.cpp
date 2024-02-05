#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <math.h>

#define ll long long int

using namespace std;

int NUM_MAX_Eratos = 500000;
int NUM_MAX_MOBIUS = 200000;

vector<bool> isPrime_Eratos(NUM_MAX_Eratos, true);
vector<ll> prime;
vector<ll> mobius(NUM_MAX_MOBIUS, 0);

void vec_init() {
    mobius[0] = 0;
    mobius[1] = 1;
    for (ll i = 1; i < NUM_MAX_MOBIUS; i++) {
        if (mobius[i]) {
            for (int j = 2 * i; j < NUM_MAX_MOBIUS; j += i) {
                mobius[j] -= mobius[i];
            }
        }
    }

    for (ll i = 0; i < NUM_MAX_Eratos; i++) {
        isPrime_Eratos[i] = true;
    }
    isPrime_Eratos[0] = isPrime_Eratos[1] = false;
    for (ll i = 2; i <= (int)(sqrt(NUM_MAX_Eratos)); i++) {
        if (isPrime_Eratos[i]) {
            for (ll j = i * i; j < NUM_MAX_Eratos; j += i) {
                isPrime_Eratos[j] = false;
            }
        }
    }
}

ll num_non_SFI(ll N) {
	ll ret = 0;
    for (ll i = 1; i * i < N; i++) {
        ret += (ll)mobius[i] * (ll)(N / (i * i));
    }
    return (N - ret);
}

ll nearest_non_SFI(ll N) {
	for (ll i = N; true; i--) {
        bool flag = false;
        for (vector<ll>::iterator jp = prime.begin(); jp != prime.end(); jp++) {
            if ((ll)(*jp) * (ll)(*jp) > N) {
                break;
            }
            //printf("Checking with int %d and prime %d\n", i, *jp);
            if (i % ((ll)(*jp) * (ll)(*jp)) == 0) {
                flag = true;
                break;
            }
        }
        if (flag) {
            return i;
            break;
        }
    }
}

// Binary Search with num_SFI - return kth SFI
ll non_SFI(ll min, ll max, ll k) {

    if (k <= 20) {
        vector<int> inits = {4, 8, 9, 12, 16, 18, 20, 24, 25, 27, 28, 32, 36, 40, 44, 45, 48, 49, 50, 52, 54, 56, 60, 63, 64, 68, 72, 75, 76, 80, 81, 84, 88, 90, 92, 96};    
        return (ll)inits[k - 1];
    }

    //printf("Searching for %d to %d with mid %d, targeting %d\n", min, max, (min + max) / 2, k);
    ll mid = (((ll)min + (ll)max) / 2);
    ll n = num_non_SFI(mid);
    if (n == k) {
        return nearest_non_SFI(mid);
    } else if (n < k) {
    	if (mid != min) {
    		return non_SFI(mid, max, k);
		} else {
        	return non_SFI(mid + 1, max, k);
		}
    } else {
    	if (mid != max) {
    		return non_SFI(min, mid, k);
		} else {
			return non_SFI(min, mid - 1, k);
		}
    }
}


int main() {
    vec_init();
    ll K;
    scanf("%lld", &K);
    prime.clear();
    for (int i = 0; i < NUM_MAX_Eratos; i++) {
        if (isPrime_Eratos[i]) {
            prime.push_back(i);
        }
    }

    printf("%lld", non_SFI(0, (ll)3*(ll)K, (ll)K));

    return 0;
}
