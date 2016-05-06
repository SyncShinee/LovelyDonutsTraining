#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

const ll maxn = 1e5 + 100;
const ll MAXNODE = 4 * maxn + 100;
const ll INF = 1e15;

struct node {
    ll to, w;
    node(ll _to = 0, ll _w = 0) {
        to = _to;
        w = _w;
    }
};
vector<node> G[maxn];
ll n, m;
ll tree[MAXNODE], tag[MAXNODE];
ll son[maxn], top[maxn], pa[maxn], num[maxn], deep[maxn], no[maxn], id, fanno[maxn];
ll w[maxn], wm[maxn], wse[maxn];
ll dp[maxn], ans;


void dfs1(ll u, ll fa) {
    pa[u] = fa;
    num[u] = 1;
    son[u] = 0;
    for(ll i = 0; i < G[u].size(); i++) {
        ll v = G[u][i].to;
        if(v != fa) {
            deep[v] = deep[u] + 1;
            dfs1(v, u);
            num[u] += num[v];
            if(num[v] > num[son[u]]) {
                son[u] = v;
            }
        }
    }
}
void dfs2(ll u, ll tp) {
    top[u] = tp;
    id++;
    no[u] = id;
    fanno[id] = u;
    if(son[u] != 0) {
        dfs2(son[u], tp);
    }
    for(ll i = 0; i < G[u].size(); i++) {
        ll v = G[u][i].to;
        if(v != pa[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}
void pushDown(ll rt, ll l, ll r) {
    ll lrt = (rt << 1), rrt = lrt + 1;
    ll m = (l + r) / 2;
    if(tag[rt] == 0) {
        return ;
    }
    ll val = tag[rt];
    tag[rt] = 0;
    tag[lrt] += val;
    tag[rrt] += val;
    tree[lrt] += val * (m - l + 1);
    tree[rrt] += val * (r - m);
}

void update(ll L, ll R, ll val, ll rt, ll l, ll r) {
    //prllf("222  %d  %d  %d\n", rt, l, r);
    if(L <= l && R >= r) {
        tag[rt] += val;
        tree[rt] += val * (r - l + 1);
        return;
    }
    ll lrt = (rt << 1), rrt = lrt + 1;
    ll m = (l + r) / 2;
    pushDown(rt, l, r);
    if(L <= m) {
        update(L, R, val, lrt, l, m);
    }
    if(R > m) {
        update(L, R, val, rrt, m + 1, r);
    }
}
void update(ll u, ll v) {
    ll tu = top[u], tv = top[v];
    while(tu != tv) {
        if(deep[tu] < deep[tv]) {
            swap(tu, tv);
            swap(u, v);
        }
        //prllf(" ---  %d  %d %d  %d\n", u, tu, no[tu], no[u]);
        // prllf("dfs\n");
        update(no[tu], no[u], 1, 1, 1, n);
        // prllf("dfs\n");
        u = pa[tu];
        tu = top[u];
        //prllf(" ---  %d  %d\n", u, tu);
    }
    if(u == v) {
        return ;
    }
    if(deep[u] < deep[v]) {
        swap(u, v);
    }
    update(no[son[v]], no[u], 1, 1, 1, n);
}
void calcu(ll rt, ll l, ll r) {
    if(l == r) {
        //prllf("44  %d  %d  %d\n", l, fanno[l], tree[rt]);
        w[fanno[l]] = tree[rt];
        return;
    }
    pushDown(rt, l, r);
    ll lrt = (rt << 1), rrt = lrt + 1;
    ll m = (l + r) / 2;
    calcu(lrt, l, m);
    calcu(rrt, m + 1, r);
}
void dfsDp(ll u, ll fa) {
    wm[u] = w[u];
    wse[u] = 0;
    for(ll i = 0; i < G[u].size(); i++) {
        ll v = G[u][i].to;
        ll weight = w[v];
        if(v != fa) {
            if(weight > wm[u]) {
                wse[u] = wm[u];
                wm[u] = weight;
            } else if(weight > wse[u]) {
                wse[u] = weight;
            }
        }
    }
    dp[u] = 0;
    ll tmp = 0;
    ll sum = 0;
    for(ll i = 0; i < G[u].size(); i++) {
        ll v = G[u][i].to;
        ll weight = w[v];
        if(v != fa) {
            dfsDp(v, u);
            dp[u] += dp[v];
            tmp = max(tmp, weight);
            sum += weight;
        }
    }
    dp[u] += sum - (ll)tmp;
}
void dfsAns(ll u, ll fa) {
    ll dpu, dpv;
    ans = min(ans, dp[u]);
    //prllf("66   %d  %lld\n", u, dp[u]);
    for(ll i = 0; i < G[u].size(); i++) {
        ll v = G[u][i].to;
        if(v != fa) {
            dpu = dp[u];
            dpv = dp[v];

            dp[u] -= dp[v];
            if(w[v] == wm[u]) {
                dp[u] = dp[u] - (ll)wse[u];
            } else {
                dp[u] = dp[u] - (ll)w[v];
            }
            dp[v] += dp[u];
            if(w[v] == wm[v]) {
                dp[v] = dp[v] + (ll)wse[v];
            } else {
                dp[v] = dp[v] + (ll)w[v];
            }
            dfsAns(v, u);

            dp[u] = dpu;
            dp[v] = dpv;
        }
    }
}
void solve() {
    deep[1] = 0;
    num[0] = 0;
    id = 0;
    dfs1(1, 0);
    dfs2(1, 1);

    memset(tag, 0, sizeof(tag));
    memset(tree, 0, sizeof(tree));
    for(ll i = 0; i < m; i++) {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        update(a, b);
    }
    calcu(1, 1, n);

    dfsDp(1, 0);

    ans = INF;
    dfsAns(1, 0);
    printf("%lld\n", ans);
}

int main() {
    //freopen("K.txt", "r", stdin);
    while(scanf("%lld%lld", &n, &m) != EOF) {
        for(ll i = 1; i <= n; i++) {
            G[i].clear();
        }
        for(ll i = 1; i <= n - 1; i++) {
            ll a, b;
            scanf("%lld%lld", &a, &b);
            G[a].push_back(node(b, 0));
            G[b].push_back(node(a, 0));
        }
        solve();
    }
    return 0;
}
