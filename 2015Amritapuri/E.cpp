#include <bits/stdc++.h>
using namespace std;
const int N = 256;
const double eps = 1e-9;
int n, k;
struct Point {
    int x, y;
}cat[N], mice[N];
int used[N + N], match[N + N];
vector <int> G[N];
double dist(const Point &A, const Point &B) {
    return sqrt(1. * (A.x - B.x) * (A.x - B.x) + 1. * (A.y - B.y) * (A.y - B.y));
}
bool dfs(int x) {
    used[x] = 1;
    for (int v : G[x]) {
        int w = match[v];
        if (w < 0 || (!used[w] && dfs(w))) {
            match[x] = v;
            match[v] = x;
            return true;
        }
    }
    return false;
}
bool check(double x) {
    for (int i = 0; i < n + n; ++ i) G[i].clear();
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            double d = dist(cat[i], mice[j]);
            if (d > x) {
                G[i].push_back(n + j);
                G[n + j].push_back(i);
            }
        }
    }
    int ans = 0;
    fill (match, match + n + n, -1);
    for (int i = 0; i < n; ++ i) {
        if (match[i] < 0) {
            memset(used, 0, sizeof used);
            if (dfs(i)) ans ++;
        }
    }
    if (n + n - ans >= k) return true;
    return false;
}
int main() {
    while (~scanf("%d%d", &n, &k)) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &cat[i].x, &cat[i].y);
        }
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &mice[i].x, &mice[i].y);
        }
        double l = 0., r = 1e6;
        for (int t = 0; t < 200; ++ t) {
            double mid = (l + r) / 2;
            if (check(mid)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        printf("%.8f\n", r);
    }
    return 0;
}
