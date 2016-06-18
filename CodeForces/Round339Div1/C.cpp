#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
int gcd(int x, int y) {return y == 0 ? x : gcd(y, x % y);}
char s[N];
int a[32];
int main() {
    int n, ans = 0, tot = 0, len = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", &a[i]);
        tot += a[i] & 1;
        len += a[i];
        ans = gcd(ans, a[i]);
    }
    len /= ans;
    if (tot > 1) {
        puts("0");
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < a[i]; ++ j) {
                putchar('a' + i);
            }
        }
        puts("");
    } else {
        int nw = 0;
        for (int i = 0; i < n; ++ i) {
            int tmp = a[i] / ans;
            if (ans & 1) {
                for (int j = 0; j < tmp / 2; ++ j) {
                    s[nw] = s[len - nw - 1] = 'a' + i;
                    ++ nw;
                }
                if (tmp & 1) s[len / 2] = 'a' + i;
            } else {
                for (int j = 0; j < tmp; ++ j) s[nw ++] = 'a' + i; 
            }
        }
        printf("%d\n", ans);
        for (int i = 0; i < ans; ++ i) {
            if (i & 1) {
                for (int j = len - 1; j >= 0; -- j) putchar(s[j]);
            } else {
                for (int j = 0; j < len; ++ j) putchar(s[j]);
            }
        }
        puts("");
    }
    return 0;
}
