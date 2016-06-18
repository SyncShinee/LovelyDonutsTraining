#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e5 + 7;
char s[32][N];
int f[32][1 << 20 + 7];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", s[i]);
    }
    for (int i = 0; i < m; ++ i) {
        int tmp = 0;
        for (int j = 0; j < n; ++ j) {
            tmp = tmp << 1 | (s[j][i] - '0');
        }
        f[0][tmp]++;
    }
    for (int k = 1; k <= n; ++ k) {
        for (int sta = 0; sta < (1 << n); ++ sta) {
            for (int p = 0; p < n; ++ p) {
                f[k][sta] += f[k - 1][sta]
            }
        }
    }
    return 0;
}
