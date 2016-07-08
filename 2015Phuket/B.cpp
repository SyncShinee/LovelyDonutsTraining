#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 30 + 10;

int t[maxn], n, l;
int num, tot, last;

void solve() {
    sort(t, t + n);
    last = 0;
    num = 0;
    tot = 0;
    for(int i = 0; i < n; i++) {
        if(last + t[i] <= l) {
            last += t[i];
            tot += last;
            num++;
        } else {
            break;
        }
    }
    printf("%d %d %d\n", num, last, tot);
}

int main() {
    freopen("B.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
        printf("Case %d: ", _);
        scanf("%d%d", &n, &l);
        for(int i = 0; i < n; i++) scanf("%d", &t[i]);
        solve();
    }
    return 0;
}
