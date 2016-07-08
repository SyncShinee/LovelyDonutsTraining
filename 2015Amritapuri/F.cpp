#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 5000 + 100;
const int M = 1e9 + 7.1;

int add(int a, int b) {
    int c = a + b;
    if(c >= M) c -= M;
    return c;
}
int mul(int a, int b) {
    ll c = (ll)a * (ll)b;
    c = c % M;
    return c;
}

int c[maxn][maxn];
int f[maxn][maxn], g[maxn];
int n;

void solve() {
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = add(ans, mul(mul(f[n][i], f[n][i]), g[i]));
    }
    printf("%d\n", ans);
}

int main() {
    freopen("F.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    memset(c, 0, sizeof(c));
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    c[0][0] = 1;
    for(int i = 1; i <= 5000; i++) {
        c[i][0] = 1;
        c[i][i] = 1;
        for(int j = 1; j < i; j++) {
            c[i][j] = add(c[i - 1][j - 1], c[i - 1][j]);
        }
    }
    g[1] = 26;
    for(int i = 2; i <= 5000; i++) {
        g[i] = mul(g[i - 1], 25);
    }
    for(int i = 1; i <= 5000; i++) {
        for(int j = 1; j <= i; j++) {
            f[i][j] = c[i - 1][j - 1];
        }
    }
    for(int i = 1; i <= 5000; i++) {
        for(int j = i; j <= 5000; j++) {
            f[j][i] = add(f[j - 1][i], f[j][i]);
        }
    }
    while(T--) {
        scanf("%d", &n);
        solve();
    }
    return 0;
}
