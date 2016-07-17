#include <bits/stdc++.h>
using namespace std;
const int N = 512;
int n, m;
int a[N][N];
vector <int> G[N];
vector <int> vertex;
bool vis[N];
double p[N], pd[N];
int main() {
    int x, y;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            if (i == j) a[i][j] = 0;
            else a[i][j] = n;
        }
    }
    for (int i = 0; i < m; ++ i) {
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
        a[x][y] = a[y][x] = 1;
    }
    for (int t = 1; t <= n; ++ t) {
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= n; ++ j) {
                a[i][j] = min(a[i][j], a[i][t] + a[t][j]);
            }
        }
    }
    double ans = 0.;
    for (int i = 1; i <= n; ++ i) {
        double new_ans = 0.;
        for (int j = 0; j < n; ++ j) {
            vertex.clear();
            for (int t = 1; t <= n; ++ t) {
                if (a[i][t] == j) {
                    int deg = G[t].size();
                    for (int v : G[t]) {
                        vis[v] = true;
                        p[v] += 1. / n / deg;
                    }
                }
            }
            for (int t = 1; t <= n; ++ t) {
                if (vis[t]) {
                    vertex.push_back(t);
                }
            }
            if (vertex.empty()) continue;
            double best = 1. / n;
            for (int t = 1; t <= n; ++ t) {
                double cur = 0.;
                for (int v : vertex) {
                    pd[a[t][v]] = max(pd[a[t][v]], p[v]);
                }
                for (int v : vertex) {
                    cur += pd[a[t][v]];
                    pd[a[t][v]] = 0.;
                }
                best = max(best, cur);
            }
            new_ans += best;
            for (int v : vertex) {
                vis[v] = false;
                p[v] = 0.;
            }
        }
        ans = max(ans, new_ans);
    }
    printf("%.10f\n", ans);
    return 0;
}
