#include <bits/stdc++.h>
#define FI first
#define SE second
using namespace std;
typedef long long ll;
typedef pair <int, ll> PIL;
const int N = 1e5 + 7;
ll m;
ll a[N];
int len;
map < ll, PIL > mp;
PIL solve(ll x) {
    PIL ret;
    if (x <= 1) {
        ret.FI = 1;
        ret.SE = 1;
        return ret;
    }
    if (mp.count(x)) {
        return mp[x];
    }
    int pos = upper_bound(a, a + N, x) - a - 1;
    PIL t1 = solve(x - a[pos]);
    PIL t2 = max(ret, solve(a[pos] - 1));
    t1.FI += 1;
    t1.SE += a[pos];
    return mp[x] = max(t1, t2);
}
int main() {
    for (int i = 1; i < N; ++ i) {
        a[i] = 1ll * i * i * i;
    }
    cin >> m;
    PIL ans = solve(m);
    cout << ans.FI << " " << ans.SE << endl;
    return 0;
}

