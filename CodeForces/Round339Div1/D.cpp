#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
const int INF = 1e9 + 7;
vector <int> G[N];
set <int> R[N];
set <int> query[N];
int ans[N];
void dfs(int x, int pre) {
    set <int> met;
    for (int v : G[x]) {
        if (v == pre) continue;
        for (int q : query[v]) {
            if (query[x].count(q)) ans[q] = INF;
        }
        dfs(v, x);
        if (R[v].size() > R[x].size()) swap(R[v], R[x]);
        for (int q : R[v]) {
            if (query[x].count(q)) ans[q] ++;
            else if (R[x].count(q)) met.insert(q);
            else R[x].insert(q);
        }
    }
    for (int q : met) {
        R[x].erase(q), ans[q] ++;
    }
    for (int q : query[x]) {
        if (R[x].count(q)) ans[q] ++;
        R[x].insert(q);
    }
}
int main() {
    int n, q, x, y;
    scanf("%d", &n);
    for (int i = 1; i < n; ++ i) {
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++ i) {
        scanf("%d", &x);
        while (x --) {
            scanf("%d", &y);
            query[y].insert(i);
        }
    }
    dfs(1, 0);
    for (int i = 0; i < q; ++ i) {
        printf("%d\n", ans[i] >= INF ? -1 : ans[i]);
    }
    return 0;
}
