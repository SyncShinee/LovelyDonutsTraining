#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 2e2 + 100;

int d, p, r, b;

vector<int> G[maxn];
int vis[maxn];
int sum[maxn], ln[maxn], rn[maxn], money[maxn];
int tot;
int f[210][10000 + 100];

void dfs(int u, int c) {
    vis[u] = 1;
    if(u <= d) {
        ln[c]++;
        sum[c] += money[u];
    } else {
        rn[c]++;
        sum[c] += money[u];
    }
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(vis[v] == 0) {
            dfs(v, c);
        }
    }
}

void dp(int l[], int r[]) {
    memset(f, 0, sizeof(f));
    for(int i = 1; i <= tot; i++) {
        for(int j = b; j >= 0; j--) {
            if(j >= sum[i])
                f[i][j] = max(f[i - 1][j] + l[i], f[i - 1][j - sum[i]] + r[i]);
            else
                f[i][j] = f[i - 1][j] + l[i];
        }
    }
}

void solve() {
    memset(vis, 0, sizeof(vis));
    tot = 0;
    for(int i = 1; i <= d + p; i++) {
        if(vis[i] == 0) {
            ++tot;
            ln[tot] = rn[tot] = sum[tot] = 0;
            dfs(i, tot);
        }
    }
    dp(ln, rn);
    printf("%d ", f[tot][b]);
    dp(rn, ln);
    printf("%d\n", f[tot][b]);
}

int main() {
    freopen("E.txt", "r", stdin);
    while(scanf("%d%d%d%d", &d, &p, &r, &b) != EOF) {
        for(int i = 1; i <= d + p; i++) {
            scanf("%d", &money[i]);
        }
        for(int i = 1; i <= r; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            G[x].push_back(y + d);
            G[y + d].push_back(x);
        }
        solve();
    }
    return 0;
}
