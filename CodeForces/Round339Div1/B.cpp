#include <bits/stdc++.h>
#define FI first
#define SE second
using namespace std;
typedef long long ll;
const int N = 1e5 + 7;
ll l[N], r[N];
ll tt[N];
struct node {
    ll val, l, r, lnum;
    node(ll a = 0, ll b = 0, ll c = 0, ll d = 0) {
        val = a, l = b, r = c, lnum = d;
    }
};
bool operator < (const node &A, const node &B) {
    return A.val < B.val;
}
pair<ll, ll> a[N];
int main() {
    ll n, A, cf, cm;
    ll m;
    scanf("%lld%lld%lld%lld%lld", &n, &A, &cf, &cm, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%lld", &a[i].FI);
        a[i].SE = i;
    }
    sort(a, a + n);
    l[0] = 0;
    for (int i = 1; i < n; ++ i) {
        l[i] = l[i - 1] + (a[i].FI - a[i - 1].FI) * i;
    }
    r[n - 1] = A - a[n - 1].FI;
    for (int i = n - 2; i >= 0; -- i) {
        r[i] = r[i + 1] + A - a[i].FI;
    }
    node ans = node(-1, 0, 0, 0);
    for (int i = 0; i <= n; ++ i) {
        if (r[i] > m) continue;
        if (i == 0) {
            ans = max(ans, node(1ll * n * cf + 1ll * A * cm, -1, 0, -1));
            continue;
        }
        int pos = upper_bound(l, l + i, m - r[i]) - l - 1;
        assert(pos >= 0);
        ans = max(ans, node(
                            1ll * (n - i) * cf + 1ll * min(A, a[pos].FI + (m - r[i] - l[pos]) / (pos + 1)) * cm,
                            pos,
                            i,
                            min(A, a[pos].FI + (m - r[i] - l[pos]) / (pos + 1))
                           )
                  );
    }
    for (int i = 0; i < n; ++ i) {
        if (i <= ans.l) tt[a[i].SE] = ans.lnum;
        else if (i >= ans.r) tt[a[i].SE] = A;
        else tt[a[i].SE] = a[i].FI;
    }
    printf("%lld\n", ans.val);
    for (int i = 0; i < n; ++ i) {
        printf("%lld%c", tt[i], " \n"[i == n - 1]);
    }
    return 0;
}
