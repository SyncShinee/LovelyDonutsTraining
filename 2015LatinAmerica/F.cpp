#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
struct node {
    int x, y, id;
};
bool operator < (const node &A, const node &B) {
    return A.y < B.y;
}
const int N = 1e5 + 7;
node p[N], f[N];
int Hash[N << 1], len;
ll C[N << 1];
ll sum[N], sum1[N];
void upd(int x, int val) {
    while (x < len) {
        C[x] += val;
        x += x & -x;
    }
}
ll get(int x) {
    ll ret = 0;
    while (x) {
        ret += C[x];
        x -= x & -x;
    }
    return ret;
}
bool cmp(const node &A, const node &B) {
    return A.id < B.id;
}
int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        len = 0;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d%d", &p[i].x, &p[i].y);
            p[i].id = i;
            Hash[++ len] = p[i].x;
        }
        for (int i = 1; i <= m; ++ i) {
            scanf("%d%d", &f[i].x, &f[i].y);
            f[i].id = i;
            Hash[++ len] = f[i].x;
        }
        sort(Hash + 1, Hash + len + 1);
        len = unique(Hash + 1, Hash + len + 1) - Hash;
        for (int i = 1; i <= n; ++ i) {
            p[i].x = lower_bound(Hash + 1, Hash + len, p[i].x) - Hash;
        }
        for (int i = 1; i <= m; ++ i) {
            f[i].x = lower_bound(Hash + 1, Hash + len, f[i].x) - Hash;
        }
        memset(C, 0, sizeof C);
        sort(p + 1, p + n + 1);
        sort(f + 1, f + m + 1);
        int point = 1;
        for (int i = 1; i <= m; ++ i) {
            while (point <= n && p[point].y <= f[i].y) {
                upd(p[point].x, p[point].id);
                ++ point;
            }
            sum[f[i].id] = get(f[i].x);
            sum1[f[i].id] = get(f[i].x - 1);
        }
        sort(f + 1, f + m + 1, cmp);
        ll ans = 0;
        for (int i = 1; i <= n; ++ i) ans += i;
        for (int i = 1; i <= m; ++ i) {
            int j = i == m ? 1 : i + 1;
            if (f[i].y == f[j].y) {
                if (f[i].x < f[j].x) {
                    ans -= sum1[i] - sum[j];
                } else {
                    ans -= sum[i] - sum1[j];
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
