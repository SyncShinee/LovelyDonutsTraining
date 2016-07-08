#include <bits/stdc++.h>
#define FI first
#define SE second
#define MP make_pair
using namespace std;
const int N = 256;
pair <int, int> stal[N], star[N];
int a[N][N], b[N][N];
int sum[N];
int lenl, lenr;
int main() {
    int T, n, m;
    scanf("%d", &T);
    for (int cas = 1; cas <= T ; ++ cas) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                scanf("%d", &a[i][j]);
            }
        }
        int q, h;
        scanf("%d", &q);
        printf("Case %d:\n", cas);
        while (q --) {
            scanf("%d", &h);
            for (int i = 1; i <= n; ++ i) {
                for (int j = 1; j <= m; ++ j) {
                    b[i][j] = (a[i][j] >= h ? 1 : -1);
                    b[i][j] += b[i][j - 1];
                }
            }
            for (int i = 2; i <= n; ++ i) {
                for (int j = 1; j <= m; ++ j) {
                    b[i][j] += b[i - 1][j];
                }
            }
            /*
            for (int i = 1; i <= n; ++ i) {
                for (int j = 1; j <= m; ++ j) {
                    printf("%d ", b[i][j]);
                }
                puts("");
            }
            */
            int ans = 0;
            for (int lo = 0; lo < n; ++ lo) {
                for (int hi = lo + 1; hi <= n; ++ hi) {
                    for (int i = 0; i <= m; ++ i) {
                        sum[i] = b[hi][i] - b[lo][i];
                    }
                    lenl = lenr = 0;
                    for (int i = 0; i <= m; ++ i) {
                        if (lenl == 0 || stal[lenl - 1].FI > sum[i]) {
                            stal[lenl ++] = MP(sum[i], i);
                        }
                    }
                    for (int i = m; i >= 0; -- i) {
                        if (lenr == 0 || star[lenr - 1].FI < sum[i]) {
                            star[lenr ++] = MP(sum[i], i);
                        }
                    }
                    /*
                    if (lo == 0 && hi == 3) {
                        puts("lenl:");
                        for (int i = 0; i < lenl; ++ i) {
                            printf("%d %d---", stal[i].SE, stal[i].FI);
                        }
                        puts("");
                        puts("lenr");
                        for (int i = 0; i < lenr; ++ i) {
                            printf("%d %d---", star[i].SE, star[i].FI);
                        }
                        puts("");
                        }*/
                    int nw = lenl - 1;
                    for (int i = 0; i < lenr; ++ i) {
                        while (nw >= 0 && (star[i].SE <= stal[nw].SE || star[i].FI >= stal[nw].FI)) {
                            -- nw;
                        }
                        if (stal[nw + 1].SE <= star[i].SE && stal[nw + 1].FI <= star[i].FI) {
                            ans = max(ans, (star[i].SE - stal[nw + 1].SE) * (hi - lo)); 
                        }
                        //printf("%d %d----- %d %d\n", i, star[i].SE, nw, stal[nw].SE);
                        
                    }
                }
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
