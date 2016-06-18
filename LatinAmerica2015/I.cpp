#include <cstdio>
#include <cstring>
using namespace std;
int main() {
    int n;
    while (~scanf("%d", &n)) {
        int ans = 0;
        int x;
        for (int i = 0; i < 5; ++ i) {
            scanf("%d", &x);
            if (x == n) ans ++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
