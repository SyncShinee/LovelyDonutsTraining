#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 5e5 + 7;
char s[N];
int l[N], r[N];
int main() {
    int n, a, b, t;
    scanf("%d%d%d%d", &n, &a, &b, &t);
    scanf("%s", s);
    int ans = 0;
    l[0] = s[0] == 'h' ? 1 : b + 1;
    if (l[0] <= t) ans = 1;
    for (int i = 1; i < n; ++ i) {
        l[i] = l[i - 1] + a + (s[i] == 'h' ? 1 : b + 1);
        if (l[i] <= t) ans = max(ans, i + 1);
    }
    r[0] = s[0] == 'h' ? 1 : b + 1;
    for (int i = 1; i < n; ++ i) {
        r[i] = r[i - 1] + a + (s[n - i] == 'h' ? 1 : b + 1);
        if (r[i] <= t) ans = max(ans, i + 1);
    }
    for (int i = 0; i < n; ++ i) {
        if (l[i] + i * a >= t) break;
        int pos = upper_bound(r, r + n, t + r[0] - l[i] - i * a) - r - 1;
        ans = max(ans, i + pos + 1);
    }
    for (int i = 0; i < n; ++ i) {
        if (r[i] + i * a >= t) break;
        int pos = upper_bound(l, l + n, t + l[0] - r[i] - i * a) - l - 1;
        ans = max(ans, i + pos + 1);
    }
    printf("%d\n", min(ans, n));
    return 0;
}
