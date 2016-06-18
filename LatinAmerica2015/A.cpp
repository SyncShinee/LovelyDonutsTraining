#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

const int maxn = 100 + 10;

char str[maxn];
int s[maxn], len;
int num[maxn];
int a[maxn];
ll ans;

void dfs(int pos, int limit, int first) {
    if(pos >= len) {
        ll tmp = 0;
        for(int i = 0; i < len; i++) {
            tmp = tmp * 10 + (ll)a[i];
        }
        ans = max(ans, tmp);
        return;
    }
    if(limit) {
        int cnt = 0;
        for(int i = s[pos]; i >= 0; i--) {
            if(num[i] < 2) {
                cnt++;
                num[i]++;
                a[pos] = i;
                int t = 0;
                if(i == s[pos]) t = 1;
                dfs(pos + 1, t, 0);
                num[i]--;
            }
            if(cnt >= 2) break;
        }
    } else {
        int cnt = 0;
        for(int i = 9; i >= 0; i--) {
            if(num[i] < 2) {
                cnt++;
                num[i]++;
                a[pos] = i;
                int t = 0;
                if(first && i == 0) {
                    t = 1;
                }
                dfs(pos + 1, 0, t);
                num[i]--;
            }
            if(cnt >= 1) break;
        }
    }
}
void solve() {
    ans = 0;
    memset(num, 0, sizeof(num));
    dfs(0, 1, 1);
    printf("%lld\n", ans);
}

int main() {
    freopen("A.txt", "r", stdin);
    while(scanf("%s", str) != EOF) {
        len = strlen(str);
        for(int i = 0; i < len; i++) s[i] = str[i] - '0';
        solve();
    }
    return 0;
}
