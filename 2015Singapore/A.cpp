#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

const int maxn = 200 + 10;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int mp[maxn][maxn], vis[maxn][maxn][maxn], s[maxn * maxn * maxn], sn, dir[maxn];
int n, len, now;
int a[maxn * maxn * maxn], an;

void dfs(int x, int y, int t, int pos) {
    //printf("nnn  %d %d\n", x, y);
    t %= len;
    if(vis[x][y][t] != -1) {
        
        sn = 0;
        for(int i = vis[x][y][t]; i < pos; i++) {
            s[sn] = s[i];
            sn++;
        }
        an = 0;
        for(int i = 0; i < sn; i++) {
            if(i == 0 || s[i] != s[i - 1]) {
                a[an] = s[i];
                an++;
            }
        }
        if(an > 1 && a[0] == a[an - 1]) {
            an--;
        }
        return;
    }
    
    vis[x][y][t] = pos;
    s[pos] = x * n + y;
   

    int nx = x + dx[dir[t]], ny = y + dy[dir[t]];
    if(mp[nx][ny]) {
        dfs(nx, ny, t + 1, pos + 1);
    } else {
        dfs(x, y, t + 1, pos + 1);
    }
}

struct Hash {
    int base;
    int M;
    int hash[maxn * maxn * maxn];
    int p[maxn * maxn * maxn];
    void init() {
        base = 40000 + 711;
        M = 1e9 + 7.1;
        hash[0] = a[0] % M;
        for(int i = 1; i < an; i++) {
            hash[i] = ((ll)hash[i - 1] * (ll)base % M + (ll)a[i]) % M;
        }
        p[0] = 1;
        for(int i = 1; i <= an + 10; i++) {
            p[i] = (ll)p[i - 1] * (ll)base % M;
        }
    }

    int getVal(int i, int j) {
        if(i == 0) return hash[j];
        int ans = hash[j];
        int tmp = (ll)hash[i - 1] * (ll)p[j - i + 1] % M;
        ans = ((ans - tmp) % M + M) % M;
        return ans;
    }
};
Hash hs;

void solve() {
    memset(vis, -1, sizeof(vis));
    dfs(now / n, now % n, 0, 0);
    hs.init();
    int ans = -1;
    for(int d = 1; d <= an; d++) {
        if(an % d == 0) {
            int tag = 1;
            int i = 0, j = d - 1;
            while(j < an) {
                if(hs.getVal(i, j) != hs.getVal(0, d - 1)) {
                    tag = 0;
                    break;
                } else {
                    i += d;
                    j += d;
                }
            }
            if(tag) {
                ans = d;
                break;
            }
        }
    }
    
    printf("%d\n", ans);
}

char str[maxn];
int main() {
    freopen("out.txt", "r", stdin);
    while(scanf("%d", &n) != EOF) {
        scanf("%s", str);
        len = strlen(str);
        for(int i = 0; i < len; i++) {
            if(str[i] == '^') dir[i] = 0;
            else if(str[i] == 'v') dir[i] = 2;
            else if(str[i] == '>') dir[i] = 1;
            else if(str[i] == '<') dir[i] = 3;
        }
        for(int i = 0; i < n; i++) {
            scanf("%s", str);
            for(int j = 0; j < n; j++) {
                if(str[j] == '#') {
                    mp[i][j] = 0;
                } else if(str[j] == '.') {
                    mp[i][j] = 1;
                } else {
                    mp[i][j] = 1;
                    now = i * n + j;
                }
            }
        }
        solve();
    }
    return 0;
}
