#include <bits/stdc++.h>
 
using namespace std;
 
#define sd(x) scanf("%d", &x)
#define F first
#define S second
#define PB push_back
#define MP make_pair
 
typedef pair<int, int> pii;
typedef pair< pii, pii > QT;
typedef long long int LL;
 
#define rep(i, j, k) for(int i = j; i < k; ++i)
 
#define N 112345
#define M 2123456
#define B 350
#define MOD 1000000007
 
inline void norm(int &x){
    if(x >= MOD){
        x -= MOD;
    }
    if(x < 0){
        x += MOD;
    }
}
 
inline LL powerMod(LL a, LL p, LL mod){
    LL ret = 1;
    a %= mod;
    while(p > 0){
        if(p & 1){
            ret *= a;
            ret %= mod;
        }
        p >>= 1;
        a *= a;
        a %= mod;
    }
    return ret;
}
 
bool comp(const QT &a, const QT &b){
    if(a.F.F / B == b.F.F / B){
        return a.F.S < b.F.S;
    }
    return a.F.F < b.F.F;
}
 
vector<int> divs[N];
int mu[N], spf[N];
LL fac[N], ifac[N];
 
LL com(int n, int r){
    if(n < r){
        return 0;
    }
    LL ret = fac[n];
    ret *= ifac[r];
    ret %= MOD;
    ret *= ifac[n - r];
    ret %= MOD;
    return ret;
}
 
void pre(){
    mu[1] = 1;
    fac[1] = 1;
    fac[0] = 1;
    rep(i, 2, N){
        fac[i] = (fac[i - 1] * i) % MOD;
        if(spf[i] == 0){
            spf[i] = i;
            for(int j = i; j < N; j += i){
                spf[j] = i;
            }
        }
        mu[i] = - mu[i / spf[i]];
        if((i / spf[i]) % spf[i] == 0){
            mu[i] = 0;
        }
    }
    int x = 0;
    ifac[N - 1] = powerMod(fac[N - 1], MOD - 2, MOD);
    rep(i, 1, N){
        ifac[N - i - 1] = (ifac[N - i] * (N - i)) % MOD;
        if(mu[i] != 0){
            if(i <= 10000){
                x++;
            }
            for(int j = i; j < N; j += i){
                divs[j].PB(i);
            }
        }
    }
}
 
bool alive[M];
int id[N], rid[M], cnt[N], sz;
int cntp[N], cntn[N];
 
void add(int k, int x){
    if(k < B){
        if(mu[x] == 1){
            cntp[k]++;
        }
        else{
            cntn[k]++;
        }
        return;
    }
    id[x] = sz;
    rid[sz] = x;
    alive[sz] = true;
    sz++;
}
 
void rem(int k, int x){
    if(k < B){
        if(mu[x] == 1){
            cntp[k]--;
        }
        else{
            cntn[k]--;
        }
        return;
    }
    alive[id[x]] = false;
}
 
void inc(int x){
    if(cnt[x] >= B){
        cnt[x]++;
        return;
    }
    rem(cnt[x], x);
    cnt[x]++;
    add(cnt[x], x);
}

void dec(int x){
    if(cnt[x] >= B + 1){
        cnt[x]--;
        return;
    }
    rem(cnt[x], x);
    cnt[x]--;
    add(cnt[x], x);
}
 
void incad(int x){
    for (v : divs[x]){
        inc(v);
    }
}
 
void decad(int x){
    for (v : divs[x]){
        dec(v);
    }
}
 
int ans[N], a[N];
QT query[N];
 
int main(){
    pre();
    int n, q, l, r, cl, cr, ck, ci, csz, k;
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++ i){
            scanf("%d", &a[i]);
        }
        scanf("%d", &q);
        for (int i = 0; i < q; ++ i){
            scanf("%d%d%d", &query[i].F.F, &query[i].F.S, &query[i].S.F);
            query[i].S.S = i;
        }
        sort(query, query + q, comp);
        l = r = 1;
        sz = 0;
        incad(a[1]);
        rep(i, 0, q){
            cl = query[i].F.F;
            cr = query[i].F.S;
            ck = query[i].S.F;
            ci = query[i].S.S;
            while(r < cr){
                incad(a[r + 1]);
                r++;
            }	
            while(l > cl){
                incad(a[l - 1]);
                --l;
            }
            while(l < cl){
                decad(a[l]);
                l++;
            }
            while(r > cr){
                decad(a[r]);
                --r;
            }
            ans[ci] = 0;
            for (int j = ck; j < B; ++ j){
                if(cntp[j] - cntn[j] != 0){
                    ans[ci] += (com(j, ck) * (cntp[j] - cntn[j])) % MOD;
                    norm(ans[ci]);
                }
            }
            csz = 0;
            for (int j = 0; j < sz; ++ j){
                if(alive[j]){
                    k = rid[j];
                    rid[csz] = k;
                    id[k] = csz;
                    alive[csz] = true;
                    csz++;
                    if(mu[k] == 0 || cnt[k] < ck){
                        continue;
                    }
                    if(mu[k] == 1){
                        ans[ci] += com(cnt[k], ck);
                        norm(ans[ci]);
                    }
                    else{
                        ans[ci] -= com(cnt[k], ck);
                        norm(ans[ci]);
                    }
                }
            }
            sz = csz;
        }
        for (int i = 0; i < q; ++ i){
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
