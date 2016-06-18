#include <bits/stdc++.h>
#define FI first
#define SE second
using namespace std;
typedef pair <int, int> PII;
const int N = 1e5 + 7;
PII p[N];
int f[N];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d%d", &p[i].FI, &p[i].SE);
    }
    sort(p + 1, p + n + 1);
    f[0] = 0;
    int mx = 0;
    for (int i = 1; i <= n; ++ i) {
        int pos = lower_bound(p + 1, p + n + 1, make_pair(p[i].FI - p[i].SE, 0)) - p - 1;
        f[i] = f[pos] + 1;
        mx = max(mx, f[i]);
    }
    printf("%d\n", n - mx);
    return 0;
}
