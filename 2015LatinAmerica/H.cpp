#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
int n, m;
int a[128][128];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
struct node {
    int x, y;
    node (int _x = 0, int _y = 0) : x(_x), y(_y) {}
};
queue <node> q;
bool vis[128][128];
bool legal(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}
void bfs(int x, int y) {
    vis[x][y] = true;
    q.push(node(x, y));
    while (!q.empty()) {
        node u = q.front();
        q.pop();
        for (int i = 0; i < 4; ++ i) {
            int nx = u.x + dx[i], ny = u.y + dy[i];
            if (!legal(nx, ny) || vis[nx][ny] || a[nx][ny] != a[x][y]) continue;
            vis[nx][ny] = true;
            q.push(node(nx, ny));
        }
    }
}
bool check1(int tag, int i, int j) {
    if (tag < 0) {
        return min(a[i][j], a[i][j - 1]) <= max(a[i + 1][j], a[i + 1][j - 1]);
    } else {
        return min(a[i + 1][j], a[i + 1][j - 1]) <= max(a[i][j], a[i][j - 1]);
    }
}
bool check2(int tag, int i, int j) {
    if (tag < 0) {
        return min(a[i][j], a[i - 1][j]) <= max(a[i][j + 1], a[i - 1][j + 1]);
    } else {
        return min(a[i][j + 1], a[i - 1][j + 1]) <= max(a[i][j], a[i - 1][j]);
    }
}
int sgn(int x) {
    if (x < 0) return -1;
    if (x == 0) return 0;
    return 1;
}
int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                scanf("%d", &a[i][j]);
            }
        }
        memset(vis, 0, sizeof vis);
        int ans = 5;
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                if (!vis[i][j]) {
                    ans ++;
                    bfs(i, j);
                }
            }
        }
        for (int i = 1; i < n; ++ i) {
            int tag = 0;
            for (int j = 1; j <= m; ++ j) {
                int tmp = sgn(a[i + 1][j] - a[i][j]);
                if (tmp == 0) {
                    tag = 0;
                    continue;
                }
                if (tmp != tag || tmp == tag && check1(tag, i, j)) {
                    ans ++;
                }
                tag = tmp;
            }
        }
        for (int i = 1; i < m; ++ i) {
            int tag = 0;
            for (int j = 1; j <= n; ++ j) {
                int tmp = sgn(a[j][i + 1] - a[j][i]);
                if (tmp == 0) {
                    tag = 0;
                    continue;
                }
                if (tmp != tag || tmp == tag && check2(tag, j, i)) {
                    ans ++;
                }
                tag = tmp;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
