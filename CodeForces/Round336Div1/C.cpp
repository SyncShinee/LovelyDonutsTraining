#include <bits/stdc++.h>
using namespace std;
char rev[128];
const int N = 2e6 + 7;
char s1[N], s2[N];
int nxt[N];
int main() {
    rev['N'] = 'S';
    rev['S'] = 'N';
    rev['W'] = 'E';
    rev['E'] = 'W';
    int n;
    scanf("%d", &n);
    n--;
    scanf("%s", s1);
    scanf("%s", s2);
    for (int i = 0, j = n - 1; i <= j; ++ i, -- j) {
        s1[i] = rev[s1[i]];
        if (i != j) {
            s1[j] = rev[s1[j]];
            swap(s1[i], s1[j]);
        }
    }
    strcat(s1, s2);
    int j = -1;
    nxt[0] = -1;
    for (int i = 0; i < 2 * n; ++ i) {
        while(j > -1 && s1[i] != s1[j]) {
            j = nxt[j];
        }
        nxt[i + 1] = ++ j;
    }
    puts(nxt[2 * n] == 0 ? "YES" : "NO");
    return 0;
}
