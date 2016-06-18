#include <bits/stdc++.h>
using namespace std;
const int N = 512;
int n;
int a[N], f[N][N];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
    }
    for (int i = n; i >= 1; -- i) {
        for (int j = i; j <= n; ++ j) {
            if (i == j) f[i][j] = 1;
            else {
                f[i][j] = f[i][j - 1] + 1;
                if (a[j] == a[j - 1]) {
                    f[i][j] = min(f[i][j], f[i][j - 2] + 1);
                }
                for (int t = i; t < j - 1; ++ t) {
                    if (a[t] == a[j]) {
                        f[i][j] = min(f[i][j], f[i][t - 1] + f[t + 1][j - 1]);
                    }
                }
            }
        }
    }
    printf("%d\n", f[1][n]);
    return 0;
}
