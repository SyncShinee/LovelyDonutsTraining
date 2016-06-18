#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 5e5 + 100;

int a, b, t, n;
int r[maxn], l[maxn];
int tim[maxn];

int solve() {
    int ans = 0;
    if(t < tim[0]) {
        return 0;
    } else {
        t -= tim[0];
        r[0] = 0;
        for(int i = 1; i < n; i++) {
            r[i] = r[i - 1] + tim[i];
            //printf("%d -- %d\n", i, r[i]);
        }
        if(r[n - 1] <= t) {
            return n;
        }

        l[0] = 0;
        for(int i = 1; i < n; i++) {
            int pos = -i;
            pos = (pos % n + n) % n;
            //printf("%d\n", pos);
            l[i] = l[i - 1] + tim[pos];
        }

        for(int i = 1; i < n; i++) {
            if(r[i] <= t) {
                int res = i;
                int tmp = t - r[i];
                if(tmp >= a * i) {
                    tmp -= a * i;
                    int pos = upper_bound(l, l + n, tmp) - l;
                    pos--;
                    res += pos;
                }

                ans = max(ans, res + 1);
            }
        }
        for(int i = 1; i < n; i++) {
            if(l[i] <= t) {
                int res = i;
                int tmp = t - l[i];
                if(tmp >= a * i) {
                    tmp -= a * i;
                    int pos = upper_bound(r, r + n, tmp) - r;
                    pos--;
                    res += pos;
                }

                ans = max(ans, res + 1);
            }
        }
        return ans;
    }
}

char ch[maxn];

int main() {
    //freopen("B.txt", "r", stdin);
    while(scanf("%d%d%d%d", &n, &a, &b, &t) != EOF) {
        scanf("%s", ch);
        for(int i = 0; i < n; i++) {
            tim[i] = 1;
            if(ch[i] == 'w') {
                tim[i] += b;
            }
            if(i != 0) {
                tim[i] += a;
            }
        }
        int ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}
