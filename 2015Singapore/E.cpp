#include <bits/stdc++.h>
using namespace std;
struct node {
    int num, pen, tot;
} f[512];
int p[16];
int main() {
    int n, id;
    while (~scanf("%d%d", &n, &id)) {
        for (int i = 0; i < n; ++ i) {
            scanf("%d", &p[i]);
        }
        int m = 300 - p[id];
        swap(p[id], p[n - 1]);
        -- n;
        sort(p, p + n);
        if (m < 0) {
            puts("0 0");
        } else {
            for (int i = 0; i <= m; ++ i) {
                f[i].num = 1, f[i].pen = p[n], f[i].tot = p[n];
            }
            for (int i = 0; i < n; ++ i) {
                for (int j = m; j >= p[i]; -- j) {
                    if (f[j].num < f[j - p[i]].num + 1 || f[j].num == f[j - p[i]].num + 1 && f[j].pen > f[j - p[i]].pen + f[j - p[i]].tot + p[i]) {
                        f[j].num = f[j - p[i]].num + 1;
                        f[j].pen = f[j - p[i]].pen + f[j - p[i]].tot + p[i];
                        f[j].tot = f[j - p[i]].tot + p[i];
                    }
                }
            }
            printf("%d %d\n", f[m].num, f[m].pen);
        }
    }
    return 0;
}
