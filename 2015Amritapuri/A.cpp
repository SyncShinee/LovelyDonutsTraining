#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

const int maxn = 1e5 + 100;

map<pair<int, string>, int> mp;
vector<int> G[maxn];
int vis[maxn], n, tot;
int f[maxn][2];
char s[100];
char str[maxn];

int add(int now, string t) {
    int no = mp[make_pair(now, t)];
    if(no == 0) {
        mp[make_pair(now, t)] = tot;
        //printf("--add %d  %d\n", now, tot);
        G[now].push_back(tot);
        G[tot].push_back(now);
        tot++;
        return tot - 1;
    } else {
        return no;
    }
}

void dfs(int u, int fa) {
    int sum = 0;
    for(int i = 0; i < G[u].size(); i++) {
        if(G[u][i] != fa) sum++;
    }
    if(sum == 0) {
        if(vis[u] == 1) {
            f[u][0] = 1;
            f[u][1] = 0;
        } else {
            f[u][0] = 0;
            f[u][1] = 1;
        }
        return;
    }
    int sum0 = 0, sum1 = 0;
    for(int i = 0; i < G[u].size(); i++) {
        int v =G[u][i];
        if(v == fa) continue;
        dfs(v, u);
        sum0 += f[v][0];
        sum1 += f[v][1];
    }
    f[u][0] = min(1 + sum1, sum0);
    f[u][1] = min(1 + sum0, sum1);
}

int main() {
    freopen("A.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--) {
        for(int i = 0; i <= 100000; i++) G[i].clear();
        memset(vis, 0, sizeof(vis));
        mp.clear();
        tot = 1;
        scanf("%d", &n);
        //printf("nn %d\n", n);
        for(int i = 0; i < n; i++) {
            scanf("%s %s", s, str);
            int tag;
            if(s[0] == 's') {
                tag = 1;
            } else {
                tag = 2;
            }
            int now = 0;
            int pos = 1;
            int len = strlen(str);
            string t = "";
            while(1) {
                if(pos == len || str[pos] == '/') {
                    now = add(now, t);
                    //cout << t << endl;
                    vis[now] = tag;
                    t = "";
                    if(pos == len) break;
                    pos++;
                } else {
                    t = t + str[pos];
                    pos++;
                }
            }
            //            printf("%d---\n", tot);
        }
        dfs(0, -1);
        printf("%d\n", f[0][0]);
    }
    return 0;
}
