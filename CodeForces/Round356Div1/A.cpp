#include <bits/stdc++.h>
using namespace std;
const int N = 101;
int n, m;
int p[N], len;
bool vis[N];
char s[8];
int main() {
    len = 0;
    for (int i = 2; i < N; ++ i) {
        if (!vis[i]) {
            p[len ++] = i;
        }
        for (int j = i; j < N; j += i) {
            vis[j] = true;
        }
    }
    int num = 0;
    int nw = 1;
    for (int i = 0; i < 4; ++ i) {
        printf("%d\n", p[i]);
        fflush(stdout);
        scanf("%s", s);
        if (s[0] == 'y') {
            num ++;
            nw = p[i];
        }
    }
    if (num > 1) {
        puts("composite");
        fflush(stdout);
    } else if (num == 0) {
        puts("prime");
        fflush(stdout);
    } else {
        printf("%d\n", nw * nw);
        fflush(stdout);
        scanf("%s", s);
        if (s[0] == 'y') {
            num ++;
        }
        for (int i = 4; i < len && p[i] * nw < N; ++  i) {
            printf("%d\n", p[i]);
            fflush(stdout);
            scanf("%s", s);
            if (s[0] == 'y') {
                num ++;
                break;
            }
        }
        if (num > 1) {
            puts("composite");
            fflush(stdout);
        } else {
            puts("prime");
            fflush(stdout);
        }
    }
    return 0;
}
