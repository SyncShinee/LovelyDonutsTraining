#include <bits/stdc++.h>
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int N = 2e5 + 7;
const ll MOD = 1e9 + 7.1;
int v[N];
struct node {
    int type, x;
}query[N];
vector <int> G[N];
int in[N], out[N], len;
void dfs(int x) {
    ++ len;
    in[x] = len;
    for (int v : G[x]) {
        dfs(v);
    }
    out[x] = len;
}
ll deg[N];
struct Tnode {
    ll m, mv, tag;
}T[N << 2];
ll inv(ll x) {
    int p = MOD - 2;
    ll ret = 1;
    while (p) {
        if (p & 1) {
            ret = ret * x % MOD;
        }
        x = x * x % MOD;
        p >>= 1;
    }
    return ret;
}
void build(int l, int r, int rt) {
    T[rt].mv = 0;
    T[rt].m = T[rt].tag = 1;
    if (l == r) return;
    int mid = l + r >> 1;
    build(lson);
    build(rson);
}
void pushup(int rt) {
    T[rt].mv = (T[rt << 1].mv + T[rt << 1 | 1].mv) % MOD;
}
void pushdown(int rt) {
    T[rt << 1].m = T[rt << 1].m * T[rt].tag % MOD;
    T[rt << 1].mv = T[rt << 1].mv * T[rt].tag % MOD;
    T[rt << 1].tag = T[rt << 1].tag * T[rt].tag % MOD;
    T[rt << 1 | 1].m = T[rt << 1 | 1].m * T[rt].tag % MOD;
    T[rt << 1 | 1].mv = T[rt << 1 | 1].mv * T[rt].tag % MOD;
    T[rt << 1 | 1].tag = T[rt << 1 | 1].tag * T[rt].tag % MOD;
    T[rt].tag = 1;
}
void upd(int L, int R, ll val, int l, int r, int rt) {
    if (L <= l && r <= R) {
        T[rt].tag = T[rt].tag * val % MOD;
        T[rt].m = T[rt].m * val % MOD;
        T[rt].mv = T[rt].mv * val % MOD;
        return;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if (L <= mid) upd(L, R, val, lson);
    if (mid < R) upd(L, R, val, rson);
    pushup(rt);
}
void upd(int x, ll val, int l, int r, int rt) {
    if (l == r && l == x) {
        T[rt].mv = T[rt].m * val % MOD;
        return;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if (x <= mid) upd(x, val, lson);
    else upd(x, val, rson);
    pushup(rt);
}
ll qry(int L, int R, int l, int r, int rt) {
    ll ret = 0;
    if (L <= l && r <= R) {
        return T[rt].mv;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if (L <= mid) ret = (ret + qry(L, R, lson)) % MOD;
    if (mid < R) ret = (ret + qry(L, R, rson)) % MOD;
    return ret;
}
ll qry(int x, int l, int r, int rt) {
    if (l == r && l == x) {
        return T[rt].m;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if (x <= mid) return qry(x, lson);
    return qry(x, rson);
}
int main() {
    int q, type, x, y, tot = 1;
    scanf("%d%d", &v[1], &q);
    for (int i = 0; i < q; ++ i) {
        scanf("%d%d", &query[i].type, &query[i].x);
        if (query[i].type == 1) {
            G[query[i].x].push_back(++ tot);
            scanf("%d", &v[tot]);
        }
    }
    len = 0;
    dfs(1);
    build(1, len, 1);
    tot = 1;
    upd(in[1], v[1], 1, len, 1);
    for (int i = 0; i < q; ++ i) {
        int x = query[i].x;
        if (query[i].type == 1) {
            ++ deg[x];
            ll p = (deg[x] + 1) * inv(deg[x]) % MOD;
            upd(in[x], out[x], p, 1, len, 1);
            ++ tot;
            upd(in[tot], v[tot], 1, len, 1);
        } else {
            ll ans = qry(in[x], out[x], 1, len, 1);
            ll div = qry(in[x], 1, len, 1);
            ans = ans * (deg[x] + 1) % MOD * inv(div) % MOD;
            printf("%d\n", (int)ans);
        }
    }
    return 0;
}
