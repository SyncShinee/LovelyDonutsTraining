#include <bits/stdc++.h>

using namespace std;
#define fi first
#define se second
typedef long long ll;
typedef pair <ll, ll> pll;
const int N = 1e5 + 100;
int n;
ll f[N];
pll p[N];
ll cross(pll a, pll b){
    return a.fi * b.se - a.se * b.fi;
}
ll check(int a, int b){
    if (a > b) swap(a, b);
    // printf("%d %d\n", a, b);
    ll res = f[a - 1] + cross(p[a], p[b]) + (f[n] - f[b - 1]);
    return min(res, f[n] - res);
}
int main(){
    while (~scanf("%d", &n)){
        for (int i = 1; i <= n; ++ i){
            scanf("%lld %lld", &p[i].fi, &p[i].se);
        }
        for (int i = 1; i < n; ++ i){
            f[i] = f[i - 1] + cross(p[i], p[i + 1]);
            //    printf("%lld\n", f[i]);
        }
        f[n] = f[n - 1] + cross(p[n], p[1]);
        //printf("%lld\n", f[n]);
        ll ans = f[n] + 1;
        for (int i = 1; i <= n; ++ i){
            int l = 1, r = n - 1;
            while (l < r - 1){
                int m1 = (l + r) >> 1;
                int m2 = (m1 + r) >> 1;
                int id1 = i + m1; if (id1 > n) id1 -= n;
                int id2 = i + m2; if (id2 > n) id2 -= n;
                if (check(i, id1) < check(i, id2)) l = m1;
                else
                    r = m2;
            }
            int id = i + r; if (id > n) id -= n;
            //  printf("%lld\n", check(i, id));
            ans = min(ans, check(i, id));
        }
        printf("%lld %lld\n", f[n] - ans, ans);
    }
    
}
