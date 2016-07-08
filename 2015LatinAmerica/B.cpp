#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

const int INF = 1e9;
const int maxV = 300 + 10;
const int maxE = 100000 + 10;

struct Edge {
    int from, to, cap, flow, next;
    Edge(int _from = 0, int _to = 0, int _cap = 0, int _flow = 0, int _next = 0) {
        from = _from;
        to = _to;
        cap = _cap;
        flow = _flow;
        next = _next;
    }
};
struct Dinic {
    int s, t;
    Edge edges[2 * maxE];
    int tot;
    int head[maxV];
    int cur[maxV];
    bool vis[maxV];
    int d[maxV];
    queue<int> que;

    void init() {
        tot = 0;
        memset(head, -1, sizeof(head));
    }
    void addEdge(int from, int to, int cap) {
        edges[tot] = Edge(from, to, cap, 0, head[from]);
        head[from] = tot;
        tot++;
        edges[tot] = Edge(to, from, 0, 0, head[to]);
        head[to] = tot;
        tot++;
    }
    bool BFS() {
        memset(vis, 0, sizeof(vis));
        while(!que.empty()) {
            que.pop();
        }
        que.push(s);
        vis[s] = 1;
        d[s] = 0;
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int i = head[u]; i != -1; i = edges[i].next) {
                Edge &e = edges[i];
                if(!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[u] + 1;
                    que.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int DFS(int u, int exFlow) {
        if(u == t || exFlow == 0) {
            return exFlow;
        }
        int flow = 0, f;
        for(int &i = cur[u]; i != -1; i = edges[i].next) {
            Edge &e = edges[i];
            if(d[u] + 1 == d[e.to]) {
                f = DFS(e.to, min(exFlow, e.cap - e.flow));
                if(f > 0) {
                    e.flow += f;
                    edges[i ^ 1].flow -= f;
                    flow += f;
                    exFlow -= f;
                    if(exFlow == 0) break;
                }
            }
        }
        return flow;
    }
    int Maxflow(int s, int t, int limit) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while(BFS()) {
            memcpy(cur, head, sizeof(cur));
            flow += DFS(s, limit - flow);
            if(flow == limit) break;
        }
        return flow;
    }
};
Dinic g;

const int maxn = 100 + 10;
int vis[maxn], n, q, k;
vector<int> have[maxn];

void solve() {
    for(int i = 1; i <= n; i++) {
        have[i].clear();
    }
    for(int i = 1; i <= n; i++) {
        int t, a;
        scanf("%d", &t);
        for(int j = 1; j <= t;j++) {
            scanf("%d", &a);
            have[i].push_back(a);
        }
        //        have[i].push_back(a);
    }
    for(int qt = 1; qt <= q; qt++) {
        memset(vis, 0, sizeof(vis));
        int num, a;
        scanf("%d", &num);
        for(int i = 1; i <= num; i++) {
            scanf("%d", &a);
            vis[a] = 1;
        }
        int flag = 1;
        for(int i = 1; i <= n; i++) {
            // printf("11 %d  %d\n", have[i].size(), num);
            if(have[i].size() == n) {
                if(num == 0) {
                    flag = 0;
                    break;
                }
            }
        }
        if(flag == 0) {
            printf("N\n");
            continue;
        }
        g.init();
        int s = 2 * n + 1, t = 2 * n + 2;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < have[i].size(); j++) {
                int u = have[i][j];
                g.addEdge(i, u + n, 1);
            }
            g.addEdge(s, i, 1);
            if(vis[i]) {
                g.addEdge(n + i, t, 1);
            }
        }
        int ans = g.Maxflow(s, t, INF);
        //printf("1111  %d\n", ans);
        if(ans == num) {
            printf("Y\n");
        }else {
            printf("N\n");
        }
        
    }
}

int main() {
    freopen("B.txt", "r", stdin);
    while(scanf("%d%d", &n, &q) != EOF) {
        solve();
    }
    return 0;
}
