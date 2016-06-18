#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#include <map>
using namespace std;
const int N = 128;
struct Point {
    int x, y;
}a[N][N];
int ans[N][N];
int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            a[i][j].x = i;
            a[i][j].y = j;
        }
    }
    while(q --) {
        int type, x, y, z;
        scanf("%d%d", &type, &x);
        if (type == 1) {
            Point nw = a[x][1];
            for (int j = 1; j < m; ++ j) {
                a[x][j] = a[x][j + 1];
            }
            a[x][m] = nw;
        } else if (type == 2){
            Point nw = a[1][x];
            for (int j = 1; j < n; ++ j) {
                a[j][x] = a[j + 1][x];
            }
            a[n][x] = nw;
        } else {
            scanf("%d%d", &y, &z);
            ans[a[x][y].x][a[x][y].y] = z;
        }
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            printf("%d%c", ans[i][j], " \n"[j == n]);
        }
    }
    return 0;
}
