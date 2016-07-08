#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
int h[N];
int ans[N];
int f[N][N][2];
int mxj[N];
int main() {
    int n;
    freopen("A.txt", "r", stdin);
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &h[i]);
        }
        memset(f, -1, sizeof f);
        memset(ans, 0, sizeof ans);
        memset(mxj, 0, sizeof mxj);
        for (int i = n; i >= 1; -- i) {
            int mxi = 0;
            for (int j = i; j <= n; ++ j) {
                if (i == j) {
                    f[i][j][0] = f[i][j][1] = 0;
                    continue;
                }
                if (h[i] < h[j]) {
                    f[i][j][1] = mxi + 1;
                    mxj[j] = max(mxj[j], f[i][j][1]);
                    ans[j] = max(ans[j], f[i][j][1]);
                } else if (h[i] > h[j]) {
                    f[i][j][0] = mxj[j] + 1;
                    mxi = max(mxi, f[i][j][0]);
                    ans[i] = max(ans[i], f[i][j][0]);
                }
                // printf("%d %d %d %d\n", i, j, f[i][j][0], f[i][j][1]);
            }
        }
        for (int i = 1; i <= n; ++ i) {
            printf("%d%c", ans[i], " \n"[i == n]);
        }
    }
    return 0;
}
