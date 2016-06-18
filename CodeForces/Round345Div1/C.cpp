#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
const int N = 1e6 + 7;
int n, m, a[N], num;
int f[N];
int gf(int x) {
    return f[x] == x ? x : f[x] = gf(f[x]);
}
void merge(int x, int y) {
    int i = gf(x), j = gf(y);
    f[i] = j, f[x] = j;
}
bool judge(int x, int y) {
    return gf(x) == gf(y);
}
pair <int, int> c[N];
vector <int> G[N];
int deg[N], ans[N];
void add_edge(int x, int y) {
    x = gf(x), y = gf(y);
    G[x].push_back(y);
    deg[y]++;
}
queue<int> q;
int main() {
    scanf("%d%d", &n, &m);
    num = n * m;
    for (int i = 0; i < num; ++ i) {
        scanf("%d", &a[i]);
        f[i] = i;
    }
    for (int i = 0; i < n; ++ i) {
        int id = i * m;
        for (int j = 0; j < m; ++ j) {
            c[j] = make_pair(a[id], id);
            ++ id;
        }
        sort(c, c + m);
        for (int j = 0; j < m;) {
            int k = j;
            while (k < m && c[j].first == c[k].first) {
                merge(c[j].second, c[k].second);
                ++ k;
            }
            j = k;
        }
    }
    for (int i = 0; i < m; ++ i) {
        int id = i;
        for (int j = 0; j < n; ++ j) {
            c[j] = make_pair(a[id], id);
            id += m;
        }
        sort(c, c + n);
        for (int j = 0; j < n;) {
            int k = j;
            while (k < n && c[j].first == c[k].first) {
                merge(c[j].second, c[k].second);
                ++ k;
            }
            j = k;
        }
    }
    for (int i = 0; i < n; ++ i) {
        int id = i * m;
        for (int j = 0; j < m; ++ j) {
            c[j] = make_pair(a[id], id);
            ++ id;
        }
        sort(c, c + m);
        for (int j = 0; j < m;) {
            int k = j;
            while (k < m && c[j].first == c[k].first) {
                ++ k;
            }
            if (k < m) add_edge(c[j].second, c[k].second);
            j = k;
        }
    }
    for (int i = 0; i < m; ++ i) {
        int id = i;
        for (int j = 0; j < n; ++ j) {
            c[j] = make_pair(a[id], id);
            id += m;
        }
        sort(c, c + n);
        for (int j = 0; j < n;) {
            int k = j;
            while (k < n && c[j].first == c[k].first) {
                ++ k;
            }
            if (k < n) add_edge(c[j].second, c[k].second);
            j = k;
        }
    }
    for (int i = 0; i < num; ++ i) {
        if (gf(i) == i && deg[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++ ans[u];
        for (int i = 0; i < G[u].size(); ++ i) {
            int v = G[u][i];
            ans[v] = max(ans[v], ans[u]);
            deg[v] --;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    num = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            printf("%d%c", ans[gf(num)], " \n"[j == m - 1]);
            ++ num;
        }
    }
    return 0;
}
