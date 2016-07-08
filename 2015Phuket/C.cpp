#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
const int INF = 1.05e9 + 7;
struct Edge {
    int to, val;
    Edge(int _t = 0, int _v = 0) : to(_t), val(_v) {}
};
vector <Edge> G[N];
vector <int> V;
bool vis[N];
int dist[128][N];
int dis[N];
int n, m;
int deep[N], anc[N][20];
void dfs(int x, int pre) {
    vis[x] = true;
    for (auto v : G[x]) {
        if (v.to == pre) continue;
        if (vis[v.to]) {
            V.push_back(x);
            V.push_back(v.to);
            continue;
        }
        anc[v.to][0] = x;
        deep[v.to] = deep[x] + 1;
        dis[v.to] = dis[x] + v.val;
        dfs(v.to, x);
    }
}
queue <int> q;
void spfa(int id) {
    memset(vis, 0, sizeof vis);
    fill(dist[id], dist[id] + n + 1, INF);
    dist[id][V[id]] = 0;
    q.push(V[id]);
    vis[V[id]] = true;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : G[u]) {
            if (dist[id][v.to] > dist[id][u] + v.val) {
                dist[id][v.to] = dist[id][u] + v.val;
                if (!vis[v.to]) {
                    q.push(v.to);
                }
            }
        }
        vis[u] = false;
    }
}
int LCA(int x, int y) {
    int lo;
    if (deep[x] < deep[y]) swap(x, y);
    for (lo = 1; (1 << lo) <= deep[x]; ++ lo); 
    lo --;
    for (int i = lo; i >= 0; -- i) {
        if (deep[x] - (1 << i) >= deep[y]) {
            x = anc[x][i];
        }
    }
    if (x == y) return x;
    for (int i = lo; i >= 0; -- i) {
        if (anc[x][i] != -1 && anc[x][i] != anc[y][i]) {
            x = anc[x][i];
            y = anc[y][i];
        }
    }
    return anc[x][0];
}
int main() {
    int T, x, y, z, q;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 1; i <= n; ++ i) G[i].clear();
        V.clear();
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d%d", &x, &y, &z);
            G[x].push_back(Edge(y, z));
            G[y].push_back(Edge(x, z));
        }
        memset(vis, 0, sizeof vis);
        dis[1] = deep[1] = 0;
        dfs(1, 0);
        sort(V.begin(), V.end());
        V.erase(unique(V.begin(), V.end()), V.end());
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; (1 << j) <= n; ++ j) {
                anc[i][j] = -1;
            }
        }
        for (int j = 1; (1 << j) <= n; ++ j) {
            for (int i = 1; i <= n; ++ i) {
                if (anc[i][j - 1] != -1) {
                    anc[i][j] = anc[anc[i][j - 1]][j - 1];
                }
            }
        }
        for (int i = 0; i < V.size(); ++ i) {
            spfa(i);
        }
        printf("Case %d:\n", cas);
        while (q --) {
            scanf("%d%d", &x, &y);
            int ans = dis[x] + dis[y] - 2 * dis[LCA(x, y)];
            for (int i = 0; i < V.size(); ++ i) {
                if (ans > dist[i][x] + dist[i][y]) {
                    ans = dist[i][x] + dist[i][y];
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
