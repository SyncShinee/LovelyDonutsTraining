#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 7;
typedef long long ll;
struct node {
    int x, y, id;
    node(int _x = 0, int _y = 0, int _i = 0) : x(_x), y(_y), id(_i) {}
}p[N], f[N], line[N];
bool operator < (const node &A, const node &B) {
    return A.y < B.y;
}
int len;
int Hash[N << 1];
ll C[N << 1], hl;
void upd(int x, int val) {
    while (x <= hl) {
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
int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        hl = 0;
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d", &p[i].x, &p[i].y);
            p[i].id = i + 1;
            Hash[hl ++] = p[i].x;
        }
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", &f[i].x, &f[i].y);
            Hash[hl ++] = f[i].x;
        }
        sort(Hash, Hash + hl);
        hl = unique(Hash, Hash + hl) - Hash;
        for (int i = 0; i < n; ++ i) {
            p[i].x = lower_bound(Hash, Hash + hl, p[i].x) - Hash + 1;
        }
        for (int i = 0; i < m; ++ i) {
            f[i].x = lower_bound(Hash, Hash + hl, f[i].x) - Hash + 1;
        }
        len = 0;
        for (int i = 0; i < m; ++ i) {
            int j = (i + 1) % m;
            if (f[i].x == f[j].x) {
                line[len ++] = node(f[i].x, min(f[i].y, f[j].y), 1);
                line[len ++] = node(f[i].x, max(f[i].y, f[j].y), -1);
            }
        }
        sort(p, p + n);
        int point = 0;
        ll ans = 0;
        memset(C, 0, sizeof C);
        sort(line, line + len);
        //for (int i = 0; i < len; ++ i) printf("%d ", line[i].y);puts("");
        
        for (int i = 0; i < n; ++ i) {
            while (point < len && line[point].y <= p[i].y) {
                upd(line[point].x, line[point].id);
                ++ point;
            }
            if (!(get(p[i].x) & 1)) {
                ans += p[i].id;
            }
            //  printf("%d---%d\n",p[i].id, get(p[i].x));
            // printf("%lld\n", ans);
        }
        
        printf("%lld\n", ans);
    }
    return 0;
}
