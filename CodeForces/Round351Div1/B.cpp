#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int p[1024];
int main() {
    int n, k, a, b, x, y;
    scanf("%d%d", &n, &k);
    scanf("%d%d%d%d", &a, &b, &x, &y);
    if (n + 1 > k || n == 4) {
        puts("-1");
        return 0;
    }
    if (n == 5) {
        int mid = 15 - a - b - x - y;
        p[0] = a, p[1] = x, p[2] = mid, p[3] = y, p[4] = b;
        for (int i = 0; i < 5; ++ i) {
            printf("%d%c", p[i], " \n"[i == 4]);
        }
        printf("%d", x);
        printf(" %d", a);
        printf(" %d", mid);
        printf(" %d %d\n", b, y);
        return 0;
    }
    p[0] = a, p[n - 1] = b, p[1] = x, p[n - 3] = y;
    int nw = 1;
    for (int i = 2; i < n - 1; ++ i) {
        if (i == n - 3) continue;
        while (nw == a || nw == b || nw == x || nw == y) nw ++;
        p[i] = nw++;
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d%c", p[i], " \n"[i == n - 1]);
    }
    printf("%d", p[1]);
    printf(" %d", p[0]);
    printf(" %d", p[n - 2]);
    printf(" %d", p[n - 1]);
    for (int i = 2; i < n - 2; ++ i) {
        printf(" %d", p[i]);
    }
    puts("");
    return 0;
}
