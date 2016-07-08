#include <bits/stdc++.h>
using namespace std;
int a[10010];
int main() {
    int T, f, h, w, x;
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d%d", &f, &h, &w);
        int mn = 1e9;
        for (int i = 0; i < f; ++ i) {
            scanf("%d", &a[i]);
        }
        sort(a, a + f);
        int la = 0;
        for (int i = 0; i < f; ++ i) {
            int x = a[i];
            if (x - la < mn) mn = x - la;
            la = x;
        }
        if (w - la < mn) mn = w - la;
        printf("%d\n", mn * h);
    }
    return 0;
}
