#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
const int MOD = 1e9 + 7.1;
int f[N][N];
int main() {
    f[1][1] = 1;
    for (int i = 2; i < N; ++ i) {
        for (int j = 1; j <= i; ++ j) {
            f[i][j] = (1ll * j * f[i - 1][j] % MOD + 1ll * (i - j + 1) * f[i - 1][j - 1] % MOD) % MOD;
        }
    }
    for (int i = 1; i < N; ++ i) {
        for (int j = 1; j <= i; ++ j) {
            f[i][j] = (f[i][j] + f[i][j - 1]) % MOD;
        }
    }
    int n, q, k;
    while (~scanf("%d%d", &n, &q)) {
        while (q --) {
            scanf("%d", &k);
            k = min(n, k);
            printf("%d%c", f[n][k], " \n"[!q]);
        }
    }
    
    return 0;
}
