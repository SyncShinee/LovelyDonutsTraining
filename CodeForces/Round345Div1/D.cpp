#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 7;
const int INF = 1e9 + 7;
int a[N];
struct node {
    int x, val, id;
}query[N];
bool operator < (const node &A, const node &B) {
    return A.x < B.x;
}
int l[N], ans[N], dp[N], id[N], tag[N];
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
    for (int i = 0; i < q; ++ i) {
        scanf("%d%d", &query[i].x, &query[i].val);
        query[i].id = i;
    }
    sort(query, query + q);
    fill(dp, dp + n, INF);
    int point = 0;
    for (int i = 1; i <= n; ++ i) {
        while (point < q && query[point].x <= i) {
            ans[query[point].id] = lower_bound(dp, dp + i, query[point].val) - dp;
            ++ point;
        }
        dp[l[i] = lower_bound(dp, dp + i, a[i]) - dp] = a[i];
    }
    point = q - 1;
    int len = lower_bound(dp, dp + n, INF) - dp;
    fill(dp, dp + n, INF);
    for (int i = n; i > 0; -- i) {
        while (point >= 0 && query[point].x >= i) {
            ans[query[point].id] += lower_bound(dp, dp + n - i, -query[point].val) - dp + 1;
            -- point;
        }
        int pos = lower_bound(dp, dp + n - i, -a[i]) - dp;
        dp[pos] = -a[i];
        if (pos + l[i] + 1 == len) {
            if (id[pos] == 0) id[pos] = i;
            else id[pos] = -1;
        }
    }
    for (int i = 0; i < len; ++ i) {
        if (id[i] > 0) tag[id[i]] = 1;
    }
    for (int i = 0; i < q; ++ i) ans[query[i].id] = max(ans[query[i].id], len - tag[query[i].x]);
    for (int i = 0; i < q; ++ i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
