#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 3000 + 100;
const ll INF = 1e14;

ll f[maxn][maxn], s[maxn];
int n, a[maxn];

void solve() {
    s[0] = 0;
    for(int i = 1;i <= n; i++) {
        s[i] = s[i - 1] + (ll)a[i];
    }
    f[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        f[0][i] = INF;
    }
    for(int i = 1; i <= n; i++) {
        int k = n;
        for(int j = n; j >= 0; j--) {
            while(k >= j) {
                k--;
            }
            while(k >= 0 && f[i - 1][k] > s[j] - s[k]) {
                k--;
            }
            if(k == -1) {
                f[i][j] = INF;
            } else {
                f[i][j] = s[j] - s[k];
            }
        }
    }
    int ans = 1;
    for(int i = 2; i <= n; i++) {
        if(f[i][n] != INF) {
            ans = i;
        }
    }
    printf("%d\n", ans);
}

int main() {
    freopen("G.txt", "r", stdin);
    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        solve();
    }
    return 0;
}
