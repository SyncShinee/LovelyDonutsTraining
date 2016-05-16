#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int N = 500010;
const int H = 64;
double f[N][H];
int pre[N];
int main() {
    int q, type, x;
    scanf("%d", &q);
    int num = 1;
    for (int i = 0; i < H; ++ i) {
        f[1][i] = 1.;
    }
    pre[1] = 0;
    while (q --) {
        scanf("%d%d", &type, &x);
        if (type == 1) {
            int nw = ++ num;
            pre[nw] = x;
            for (int i = 0; i < H; ++ i) {
                f[nw][i] = 1.;
            }
            double oldp = 1, newp = 0;
            for (int i = 0; i < H; ++ i) {
                nw = pre[nw];
                if (!nw) break;
                double tmp = f[nw][i];
                f[nw][i] = f[nw][i] / (.5 + .5 * oldp) * (.5 + .5 * newp);
                oldp = tmp;
                newp = f[nw][i];
            }
        } else {
            double ans = 0;
            for (int i = 1; i < H; ++ i) {
                ans += i * (f[x][i] - f[x][i - 1]);
            }
            printf("%.10f\n", ans);
        }
    }
    return 0;
}
