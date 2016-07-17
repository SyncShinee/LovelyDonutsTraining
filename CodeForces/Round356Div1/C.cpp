#include <bits/stdc++.h>
#define COMP(x, y) ((x) * n + (y))
using namespace std;
const int N = 512;
int n, k;
bool legal(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}
char s[N][N];
int vis[N][N];
queue <int> q;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int ink[N * N];
bool used[N * N];
int num[N * N];
vector <int> upd;
void insert(int id, int &nw) {
    if (id && !used[id]) {
        nw += num[id] - ink[id];
        used[id] = true;
        upd.push_back(id);
    }
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", s[i]);
    }
    int tot = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (s[i][j] == '.' && !vis[i][j]) {
                ++ tot;
                q.push(COMP(i, j));
                vis[i][j] = tot;
                ++ num[tot];
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    int x = u / n, y = u % n;
                    for (int t = 0; t < 4; ++ t) {
                        int tx = x + dx[t], ty = y + dy[t];
                        if (!legal(tx, ty) || s[tx][ty] == 'X' || vis[tx][ty]) continue;
                        q.push(COMP(tx, ty));
                        vis[tx][ty] = tot;
                        ++ num[tot];
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n - k; ++ i) {
        int L = 0, R = -1;
        for (int j = 0; j <= n - k + 1; ++ j) {
            int l, r;
            if (j < n - k + 1) {
                l = j, r = j + k - 1;
            } else {
                l = n, r = n - 1;
            }
            while (L < l) {
                for (int t = i; t < i + k; ++ t) {
                    if (vis[t][L]) {
                        -- ink[vis[t][L]];
                    }
                }
                ++ L;
            }
            while (R < r) {
                ++ R;
                for (int t = i; t < i + k; ++ t) {
                    if (vis[t][R]) {
                        ++ ink[vis[t][R]];
                    }
                }
            }
            if (j == n - k + 1) break;
            int nw = k * k;
            if (i > 0) {
                for (int t = j; t < j + k; ++ t) {
                    insert(vis[i - 1][t], nw);
                }
            }
            if (i < n - k) {
                for (int t = j; t < j + k; ++ t) {
                    insert(vis[i + k][t], nw);
                }
            }
            if (j > 0) {
                for (int t = i; t < i + k; ++ t) {
                    insert(vis[t][j - 1], nw);
                }
            }
            if (j < n - k) {
                for (int t = i; t < i + k; ++ t) {
                    insert(vis[t][j + k], nw);
                }
            }
            for (int x : upd) {
                used[x] = false;
            }
            upd.clear();
            ans = max(ans, nw);
        }
    }
    printf("%d\n", ans);
    return 0;
}
