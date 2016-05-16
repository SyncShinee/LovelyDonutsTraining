#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 256;
int n, p, q;

int mults[N];
int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}
vector <int> get_binomial() {
    vector <int> binom(p + 1, 0);
    binom[0] = 1;
    for (int i = 1; i <= p && i <= n; ++ i) {
        mults[i] = n - i + 1;
        int div = i;
        for (int j = 1; j <= i; ++ j) {
            if (div == 1) break;
            int gc = gcd(div, mults[j]);
            if (gc > 1) {
                div /= gc;
                mults[j] /= gc;
            }
        }
        binom[i] = 1;
        for (int j = 1; j <= i; ++ j) {
            binom[i] *= mults[j];
        }
    }
    return binom;
}

vector <int> get_binomial(int n) {
    vector <int> ret(p + 1, 0);
    if (n == 0) {
        ret[0] = 1;
    } else if (n & 1) {
        vector <int> c = get_binomial(n - 1);
        for (int i = 0; i <= p; ++ i) {
            for (int j = 0; j < 2; ++ j) {
                if (i + j > p) break;
                ret[i + j] += c[i];
            }
        }
    } else {
        vector <int> c = get_binomial(n >> 1);
        for (int i = 0; i <= p; ++ i) {
            for (int j = 0; j <= p; ++ j) {
                if (i + j > p) break;
                ret[i + j] += c[i] * c[j];
            }
        }
    }
    return ret;
}
int main() {
    scanf("%d%d%d", &n, &p, &q);
    vector <int> binom = get_binomial(n);
    int ans = 0;
    for (int i = 1; i <= q; ++ i) {
        int tmp = 0;
        int base = i;
        for (int j = 0; j <= p && j < n; ++ j) {
            tmp += binom[j] * base;
            base *= i;
        }
        ans ^= tmp;
    }
    printf("%u\n", ans);
    return 0;
}
