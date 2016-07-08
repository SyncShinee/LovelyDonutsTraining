#include <bits/stdc++.h>
using namespace std;
const int N = 128;
int n, m;
char s[N][N];
struct Edge {
    int x, y, val;
    Edge (int _x = 0, int _y = 0, int _v = 0) : x(_x), y(_y), val(_v) {}
};
bool operator < (const Edge &A, const Edge &B){
    return A.val < B.val;
}
vector <Edge> e;
int f[N * N * 4];
int gf(int x) {
    return x == f[x] ? x : f[x] = gf(f[x]);
}
void merge(int x, int y) {
    int i = gf(x), j = gf(y);
    f[i] = j, f[x] = j;
}
bool judge(int x, int y) {
    return gf(x) == gf(y);
}
int main() {
    int T, x;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) {
            scanf("%s", s[i]);
        }
        for (int i = 0; i < n * m * 4; ++ i) {
            f[i] = i;
        }
        e.clear();
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                scanf("%d", &x);
                if (s[i][j] == '\\') {
                    e.push_back(Edge((i * m + j) * 4 + 0, (i * m + j) * 4 + 3, x));
                    e.push_back(Edge((i * m + j) * 4 + 1, (i * m + j) * 4 + 2, x));
                    e.push_back(Edge((i * m + j) * 4 + 0, (i * m + j) * 4 + 1, 0));
                    e.push_back(Edge((i * m + j) * 4 + 2, (i * m + j) * 4 + 3, 0));
                } else {
                    e.push_back(Edge((i * m + j) * 4 + 0, (i * m + j) * 4 + 3, 0));
                    e.push_back(Edge((i * m + j) * 4 + 1, (i * m + j) * 4 + 2, 0));
                    e.push_back(Edge((i * m + j) * 4 + 0, (i * m + j) * 4 + 1, x));
                    e.push_back(Edge((i * m + j) * 4 + 2, (i * m + j) * 4 + 3, x));
                }
                if (j > 0) {
                    e.push_back(Edge((i * m + j) * 4 + 3, (i * m + j - 1) * 4 + 1, 0));
                }
                if (i > 0) {
                    e.push_back(Edge((i * m + j) * 4 + 0, ((i - 1) * m + j) * 4 + 2, 0));
                }
            }
        }
        sort(e.begin(), e.end());
        int ans = 0, num = 0;
        for (auto v : e) {
            if (!judge(v.x, v.y)) {
                ans += v.val;
                merge(v.x, v.y);
                num ++;
                if (num == n * m * 4 - 1) {
                    break;
                }
            }
        }
        printf("Case %d: %d\n", cas, ans);
    }
    return 0;
}
