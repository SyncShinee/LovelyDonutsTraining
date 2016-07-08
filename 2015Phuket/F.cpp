#include <bits/stdc++.h>

using namespace std;
const int N = 1100;
const int INF = 1e9;
int f[N][N], p[N], r[N], n, d;
int main(){
    int t; scanf("%d", &t);
    while (t--){
        static int ca = 0;
        printf("Case %d: ", ++ ca);
        scanf("%d%d", &n, &d);
        for (int i = 0; i <= n + 1; ++ i) scanf("%d", &p[i]);
        for (int i = n + 1; i > 0; -- i) p[i] = p[i] - p[i - 1];
        for (int i = 1; i <= n + 1; ++ i) scanf("%d", &r[i]);
        for (int i = 0; i <= n + 1; ++ i){
            for (int j = 0; j <= n + 1; ++ j){
                f[i][j] = INF;
            }
        }
        f[0][0] = 0;
        for (int i = 1; i <= n + 1; ++ i){
            for (int j = 0; j <= i; ++ j){
                int tmp = max(f[i - 1][j] + p[i] - r[i], 0);
                f[i][j] = tmp;
                int la = min(r[i], p[i] + f[i - 1][j - 1]);
                int ra = max(0, p[i] + f[i - 1][j - 1] - r[i]);
                f[i][j] = min(f[i][j], max(0, la - d) + ra);
            }
        }
        //    printf("%d %d %d %d\n", n + 1, f[2][1], f[2][2], r[n + 1] - p[n + 1]);
        int ans = 0;
        for (int i = 0; i <= n + 1; ++ i){
            if (f[n + 1][i] > 0) continue;
            ans = n + 1 - i;
        }
        printf("%d\n", ans);
    }
}
