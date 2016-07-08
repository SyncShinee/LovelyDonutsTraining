#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int BLK = 256;
const int D = 128;
const int N = 5e5 + 7;
const int M = 1e5 + 7;
const int MOD = 1e9 + 7.1;
int a[N];
struct node {
    int l, r, k, id, rk;
}q[N];
int ans[N];
//int lis[N * D], lenl;
vector <int> lis;
vector <bool> used;
int inl[M * D];
int num[M * D];
int sump[M * D], sumn[M * D];
vector <int> divs[M];
bool operator < (const node &A, const node &B) {
    return A.rk < B.rk || A.rk == B.rk && A.r < B.r;
}
int mu[M], p[M], len;
bool flag[M];//, used[N * D];
int fac[M], inv[M];
int C(int n, int k) {
    return 1ll * fac[n] * inv[k] % MOD * inv[n - k] % MOD;
}
void Ins(int numv, int v) {
    if (numv < D) {
        if (mu[v] > 0) {
            ++ sump[numv];
        } else {
            ++ sumn[numv];
        }
        return;
    }
    lis.push_back(v);
    used.push_back(1);
    inl[v] = lis.size() - 1;
}
void Del(int numv, int v) {
    if (numv < D) {
        if (mu[v] > 0) {
            -- sump[numv];
        } else {
            -- sumn[numv];
        }
        return;
    }
    used[inl[v]] = false;
}
void Ins(int x) {
    for (int v : divs[x]) {
        if (num[v] >= D) {
            ++ num[v];
            return;
        }
        Del(num[v], v);
        ++ num[v];
        Ins(num[v], v);
    }
}
void Del(int x) {
    for (int v : divs[x]) {
        if (num[v] >= D + 1) {
            -- num[v];
            return;
        }
        Del(num[v], v);
        -- num[v];
        Ins(num[v], v);
    }
}
int main() {
    int n, query;
    fac[1] = fac[0] = inv[1] = inv[0] = 1;
    for (int i = 2; i < M; ++ i) {
        fac[i] = 1ll * fac[i - 1] * i % MOD;
        inv[i] = 1ll * inv[MOD % i] * (MOD - MOD / i) % MOD;
    }
    for (int i = 2; i < M; ++ i) {
        inv[i] = 1ll * inv[i] * inv[i - 1] % MOD;
    }
    mu[1] = 1, len = 0;
    for (int i = 2; i < M; ++ i) {
        if (!flag[i]) {
            mu[i] = -1;
            p[len ++] = i;
        }
        for (int j = 0; j < len && i * p[j] < M; ++ j) {
            flag[i * p[j]] = true;
            if (i % p[j]) {
                mu[i * p[j]] = -mu[i];
            } else {
                mu[i * p[j]] = 0;
                break;
            }
        }
    }
    for (int i = 1; i < M; ++ i) {
        if (!mu[i]) continue;
        for (int j = i; j < M; j += i) {
            divs[j].push_back(i);
        }
    }
    while (~scanf("%d", &n)) {
        memset(num, 0, sizeof num);
        memset(sumn, 0, sizeof sumn);
        memset(sump, 0, sizeof sump);
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[i]);
        }
        scanf("%d", &query);
        for (int i = 0; i < query; ++ i) {
            scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].k);
            q[i].id = i;
            q[i].rk = q[i].l / BLK;
        }
        sort(q, q + query);
        int L = 1, R = 1;
        Ins(a[1]);
        //lenl = 0;
        lis.clear();
        for (int _q = 0; _q < query; ++ _q) {
            int l = q[_q].l, r = q[_q].r, k = q[_q].k, id = q[_q].id;
            while (L < l) {
                Del(a[L ++]);
            }
            while (L > l) {
                Ins(a[-- L]);
            }
            while (R < r) {
                Ins(a[++ R]);
            }
            while (R > r) {
                Del(a[R --]);
            }
            ans[id] = 0;
            for (int i = k; i < D; ++ i) {
                if (sump[i] - sumn[i]) {
                    ans[id] = (ans[id] + 1ll * (sump[i] - sumn[i]) * C(i, k) % MOD) % MOD;
                }
            }
            int lent = 0;
            for (int i = 0; i < lis.size(); ++ i) {
                if (used[i]) {
                    int nu = lis[i];
                    lis[lent] = nu;
                    inl[nu] = lent;
                    used[lent] = true;
                    ++ lent;
                    if (!mu[nu] || num[nu] < k) continue;
                    ans[id] = (ans[id] + mu[nu] * C(num[nu], k)) % MOD;
                }
            }
            vector <int> :: iterator it = lis.begin();
            vector <bool> :: iterator iter = used.begin();
            it += lent;
            iter += lent;
            lis.erase(it, lis.end());
            used.erase(iter, used.end());
        }
        for (int i = 0; i < query; ++ i) {
            printf("%d\n", (ans[i] + MOD) % MOD);
        }
    }
    return 0;
}
