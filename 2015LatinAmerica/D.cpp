#include <cstdio>
#include <algorithm>
using namespace std;
int a[5] = {10000, 1000, 100, 10, 1};
int main() {
    int n, m, B, x, ans, A;
    while (~scanf("%d%d", &n, &m)) {
        ans = 0;
        for (int i = 0; i < m; ++ i) {
            scanf("%d", &B);
            int sum = 0;
            scanf("%d", &A);
            for (int j = 1; j < n; ++ j) {
                scanf("%d", &x);
                sum += x;
            }
            if (A + sum <= B) ans -= A;
            for (int i = 0; i < 5; ++ i) {
                if (a[i] + sum <= B) {
                    ans += a[i];
                    break;
                }
            }
        }
        printf("%d\n", ans);
    }
    
    return 0;
}
