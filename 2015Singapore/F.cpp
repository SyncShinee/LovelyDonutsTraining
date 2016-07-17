#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 200 + 100;

struct node {
    int a, b;
    node(int _a = 0, int _b = 0) {
        a = _a;
        b = _b;
    }
    bool operator < (const node o) {
        if(b == o.b) return a < o.a;
        return b < o.b;
    }
};
node a[maxn], b[maxn];
int n;
int vis[maxn];

void solve() {
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                if((a[i].a < a[j].a && a[i].b >= a[j].b) || (a[i].a <= a[j].a && a[i].b > a[j].b)) {
                    vis[i] = 1;
                }
            }
        }
    }
    int bn = 0;
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            b[bn] = a[i];
            bn++;
        }
    }
    sort(b, b + bn);
    int now = -1, num = 0;
    for(int i = 0; i < bn; i++) {
        //printf("--- %d  %d\n", num, now);
        if(!(now >= b[i].a && now <= b[i].b)) {
            num++;
            now = b[i].b;
        }
    }
    printf("%d\n", num);
}

int main() {
    freopen("F.txt", "r", stdin);
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; i++) scanf("%d%d", &a[i].a, &a[i].b);
        solve();
    }
    return 0;
}
