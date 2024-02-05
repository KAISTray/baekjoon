#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>
#include <vector>
#include <list>
#include <tuple>
#include <map>
#include <algorithm>

#define ll unsigned long long int
#define lll __int128

using namespace std;

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* itoa(int num, char* str, int base) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Handle negative numbers for bases other than 10
    if (num < 0 && base != 10) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int remainder = num % base;
        str[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
        num = num / base;
    }

    // Append negative sign for base 10
    if (isNegative && base == 10)
        str[i++] = '-';

    str[i] = '\0'; // Null-terminate the string

    // Reverse the string
    reverse(str, i);

    return str;
}

string itoa_str(int i) {
	if (!i) return string("0");
	char* buf = (char*)malloc((int)(log10(i) + 2) * sizeof(char));
	itoa(i, buf, 10);
	string s(buf);
	return s;
}

int main() {
	int A, B;
	scanf("%d %d", &A, &B);
	int q = A / B;
	A = A - (q * B);
	// Q.(R)(R)...
	int i = A * 10;
	vector<int> r;
	int len = 0;
	r.clear();
	bool finite = false;
	bool isEmpty;
	
	if (i == 0) {
		isEmpty = true;
	} else {
		isEmpty = false;
		while(len < 1500) {
			if (i == 0) {
				finite = true;
				break;
			}
			int u = i / B;
			i %= B;
			r.push_back(u);
			len++;
			i *= 10;
		}
	}
	string ans(itoa_str(q).c_str());
	
	string rem("");
	
	if (isEmpty) {
		finite = true;
		rem += "0";
		len = 0;
	}
	
	
	for (int i = 0; i < len; i++) {
		rem += itoa_str(r[i]);
	}
	
	//printf("Q : %s\nR : %s\n", ans.c_str(), rem.c_str());
	
	ans += string(".");
	
	ans += rem;
	printf("%s", ans.c_str());
}
