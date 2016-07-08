#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 200000 + 100;

char s[maxn], ans[maxn];
int len;

int change(char ch) {
    if(ch >= '0' && ch <= '9') return ch - '0';
    return ch - 'A' + 10;
}

void solve() {
    for(int i = 0; i < len; i += 2) {
        int num = change(s[i]) * 16 + change(s[i + 1]);
        ans[i / 2] = (char)num;
    }
    for(int i = 0; i < len / 2; i++) {
        printf("%c", ans[i]);
    }
    printf("\n");
}

int main() {
    freopen("A.txt", "r", stdin);
    while(scanf("%s", s) != EOF) {
        len = strlen(s);
        solve();
    }
    return 0;
}
