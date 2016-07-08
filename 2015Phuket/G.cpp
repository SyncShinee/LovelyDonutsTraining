#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;
ll n;
int ok[10100000];
vector <int> prime;
ll f[10100000];
void init(){
    for (int i = 2; i <= 10000000; ++ i){
        if (ok[i] != 1){
            prime.push_back(i);
        }
        for (int j = 0; j < prime.size() && 1ll * prime[j] * i <= 10000000; ++ j){
            ok[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    f[0] = 1;
    for (int i = 1; i <= 10000000; ++ i){
        f[i] = f[i - 1];
        if (ok[i] != 1) f[i] = 1ll * f[i] * i % MOD;
    }
}
double pow_mod(double x, int nn){
    double res = 1;
    while (nn){
        if (nn & 1) res = res * x;
        x = x * x;
        nn >>= 1;
    }
    return res;
}
int main(){
    init();
    int t; scanf("%d", &t);
    // puts("here");
    while (t--){
        static int ca = 0;
        printf("Case %d: ", ++ ca);
        scanf("%lld", &n);
        int ans = 1, now = 2;
        int sqr = 0;
        sqr = sqrt(n);
        while (1ll * sqr * sqr <= n) sqr++;
        while (1ll * sqr * sqr > n) sqr--; 
        for (int k = 50; k >= 1; -- k){
            int l = 1, r = sqr + 1;
            while (l < r - 1){
                int mid = l + r >> 1;
                if (pow_mod(mid, k + 1) <= n + 0.1) l = mid;
                else
                    r = mid;
            }
            now = l;
            //  if (now > 1) printf("%d %d\n", now, k);
            ans = 1ll * ans * f[now] % MOD;
        }
        printf("%d\n", ans);
    }
}
/*
Case 1: 1
Case 2: 1
Case 3: 2
Case 4: 2
Case 5: 2
Case 6: 2
Case 7: 4
Case 8: 12
Case 9: 12
Case 10: 744593350
 */
