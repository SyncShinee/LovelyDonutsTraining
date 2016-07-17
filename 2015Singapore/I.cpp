#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 6e5 + 100;
const int key = 600000 + 10;
const int M = 1e9 + 7.1;

int fac[maxn], rev[maxn];

int pow_mod(int x, int n) {
    int ans = 1, tmp = x % M;
    while(n) {
        if(n & 1) {
            ans = (ll)ans * (ll)tmp % M;
        }
        tmp = (ll)tmp * (ll)tmp % M;
        n = n >> 1;
    }
    return ans;
}
void pre() {
    fac[0] = 1;
    rev[0] = 1;
    for(int i = 1; i <= key; i++) {
        fac[i] = (ll)fac[i - 1] * (ll)i % M;
        rev[i] = pow_mod(fac[i], M - 2);
    }
}
int C(int n, int m) {
    return (ll)fac[n] * (ll)rev[m] % M * (ll)rev[n - m] % M;
}
int add(int a, int b) {
    int c = a + b;
    if(c >= M) c-= M;
    return c;
}
int a, b, c;
int ans;
void solve(int num) {
    //    int ans = 0;
    
    for(int i = 0; i <= b; i++) {
        int j = i - b + c;
        if(j >= 0) {
            int k = num - i - j;
            if(k >= 0) {
                int newb = b - i - k;
                if(newb >= 0) {
                    //printf("fafdas");
                    int x = newb, y = num;
                    
                    ans = add(ans, (ll)1 * (ll)pow_mod(2, k) * (ll)C(x + y - 1, y - 1) % M * (ll)fac[i + j + k] % M * rev[i] % M * rev[j] % M * rev[k] % M);
                    
                    
                }
            }
        }
    }
    
    //printf("%d\n", ans);
}

int main() {
    freopen("I.txt", "r", stdin);
    pre();
    while(scanf("%d%d%d", &a, &b, &c) != EOF) {
        int sum = a + b + c;
        int ta = max(a, max(b, c));
        int tc = min(a, min(b, c));
        int tb = sum - tc - ta;
        a = ta;
        b = tb;
        c = tc;
        ans = 0;
        solve(a - 1);
        solve(a);
        solve(a);
        solve(a + 1);
        printf("%d\n", ans);
    }
    return 0;
}
