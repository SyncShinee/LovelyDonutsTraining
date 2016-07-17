#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 5e5 + 1000;
const int M = 500000;

int fa[maxn], ran[maxn], c[maxn];

int getfa(int x) {
    if(x == fa[x]) return x;
    return fa[x] = getfa(fa[x]);
}
void getUnion(int a, int b) {
    a = getfa(a);
    b = getfa(b);
    if(a == b) return;
    if(ran[a] < ran[b]) {
        fa[a] = b;
        c[b] += c[a];
    } else {
        fa[b] = a;
        if(ran[a] == ran[b]) {
            ran[a]++;
        }
        c[a] += c[b];
    }
}
int n;
int vis[maxn];

void solve() {
    int all = 0;
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; i++) {
        int num, x;
        scanf("%d", &num);
        vector<int> vec;
        int ans = 0;
        for(int j = 0; j < num; j++) {
            scanf("%d", &x);
            x = getfa(x);
            if(vis[x] == 0) {
                ans += c[x];
                vec.push_back(x);
                vis[x] = 1;
            }
        }
        if(ans == num) {
            all++;
            for(int j = 0; j < vec.size(); j++) {
                int t = vec[j];
                getUnion(vec[0], t);
            }
            vis[getfa(vec[0])] = 0;
        } else {
            for(int j = 0; j < vec.size(); j++) {
                vis[getfa(vec[j])] = 0;
            }
        }
    }
    printf("%d\n", all);
}

int main() {
    freopen("C.txt", "r", stdin);
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i <= M; i++) {
            ran[i] = 1;
            fa[i] = i;
            c[i] = 1;
        }
        solve();
    }
    return 0;
}
