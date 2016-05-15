#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
const int N = 5010;
int a[N], sum[N], ans[N];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
    }
    memset(ans, 0, sizeof ans);
    for (int i = 1; i <= n; ++ i) {
        memset(sum, 0, sizeof sum);
        int mx = 0;
        int pos = 0;
        for (int j = i; j <= n; ++ j) {
            sum[a[j]]++;
            if (sum[a[j]] > mx || sum[a[j]] == mx && a[j] < pos) {
                mx = sum[a[j]];
                pos = a[j];
            }
            ans[pos]++;
        }
    }
    for (int i = 1; i <= n; ++ i) {
        printf("%d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}
