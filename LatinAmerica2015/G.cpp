#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 1000 + 100;
const double eps = 1e-6;
const double INF = 1e18;

struct node{
    int to;
    double a, b;
    node(int _to = 0, double _a = 0, double _b = 0) {
        to = _to;
        a = _a;
        b = _b;
    }
};
vector<node> G[maxn];
int n, m;
double d[maxn], inq[maxn];

double spfa(double x) {
    queue<int> q;
    memset(inq, 0, sizeof(inq));
    q.push(1);
    inq[1] = 1;
    for(int i = 1; i <= n; i++) {
        d[i] = INF;
    }
    d[1] = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].to;
            double w = G[u][i].a * x + G[u][i].b;
            if(w + d[u] < d[v] - eps) {
                d[v] = w + d[u];
                if(inq[v] == 0) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return d[n];
}

void solve() {
    double l = 0, r = 24 * 60;
    for(int i = 1; i <= 100; i++) {
        double mid = (l + r) / 2;
        double midmid = (l + mid) / 2;
        double ans1 = spfa(mid);
        double ans2 = spfa(midmid);
        if(ans1 < ans2) {
            r = mid;
        } else {
            l = midmid;
        }
    }
    printf("%.5f\n", spfa(l));
}
int main() {
    freopen("G.txt", "r", stdin);
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= n; i++) G[i].clear();
        for(int i = 1; i <= m; i++) {
            int id1, id2;
            double a, b;
            scanf("%d%d%lf%lf", &id1, &id2, &a, &b);
            G[id1].push_back(node(id2, a, b));
            G[id2].push_back(node(id1, a, b));
        }
        solve();
    }
    return 0;
}
