#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 100;
const int MOD = 1e9 + 7;
int n, k;
int fac[N], inv[N], a[N];
int Hash[N], tot;
int f[1010][1010], sum[110];
void init(){
    fac[0] = 1;
    for (int i = 1; i <= 100000; ++ i) fac[i] = 1ll * fac[i - 1] * i % MOD;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= 100000; ++ i){
        inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
    for (int i = 2; i <= 100000; ++ i){
        inv[i] = 1ll * inv[i - 1] * inv[i] % MOD;
    }
}
int add(int x, int y){
    int res = x + y; if (res >= MOD) res -= MOD;
    return res;
}
int C(int mm, int nn){
    if (nn < mm) return 0;
    return 1ll * fac[nn] * inv[mm] % MOD * inv[nn - mm] % MOD;
}
int main(){
    init();
    int t; scanf("%d", &t);
    while (t--){
        static int ca = 0;
        printf("Case %d: ", ++ ca);
        scanf("%d %d", &n, &k);
        map<int, int> mp;
        tot = 0;
        for (int i = 1; i <= n; ++ i){
            scanf("%d", &a[i]);
            Hash[++tot] = a[i];
            mp[a[i]] ++;
        }
        sort(Hash + 1, Hash + n + 1);
        tot = unique(Hash + 1, Hash + n + 1) - Hash - 1;
        sum[0] = 0;
        for (int i = 1; i <= tot; ++ i) sum[i] = sum[i - 1] + mp[Hash[i]];
        f[1][0] = 1;
        for (int i = 2; i <= tot; ++ i){
            for (int j = 0; j <= k; ++ j){
                f[i][j] = f[i - 1][j];
                // if (i == 3 && j == 1) printf("%d\n", f[i][j]);
                int num = mp[Hash[i]];
                for (int l = 1; l <= j && l <= num; ++ l){
                    //    if (i == 3 && j == 1) printf("%d\n", f[3][j - l]);
                    f[i][j] = add(f[i][j], 1ll * f[i - 1][j - l] * C(l,l + sum[i - 1] - 1) % MOD);
                }
            }
        }
        //  printf("%d %d %d %d\n", tot, f[2][0], sum[2], f[2][0] * C(1,1 + sum[2] - 1));
        printf("%d\n", f[tot][k]);
    }
}
