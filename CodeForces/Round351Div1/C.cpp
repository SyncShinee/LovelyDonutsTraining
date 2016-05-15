#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
struct line {
    double k, b;
    double at(double x) {
        return k * x + b;
    }
    line(double _k = 0., double _b = 0.) : k(_k), b(_b) {}
};
const int N = 200010;
int n, k, a[N];
double sum[N], pre[N], rev[N];
double f[N][51];

line sta[51][N];
int nw[51], sta_len[51];

bool check(const line &u, const line &v, const line &w) {
    return (v.b - u.b) / (u.k - v.k) < (w.b - v.b) / (v.k - w.k);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
        pre[i] = pre[i - 1] + sum[i] / a[i];
        rev[i] = rev[i - 1] + 1. / a[i];
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= min(i, k); ++ j) {
            if (j == 1) {
                f[i][j] = pre[i];
            } else {
                while (nw[j - 1] + 1 < sta_len[j - 1] &&
                       sta[j - 1][nw[j - 1]].at(rev[i]) > sta[j - 1][nw[j - 1] + 1].at(rev[i])) {
                    nw[j - 1]++;
                }
                f[i][j] = sta[j - 1][nw[j - 1]].at(rev[i]) + pre[i];
            }
            line nl = line(-sum[i], f[i][j] - pre[i] + sum[i] * rev[i]);
            while (sta_len[j] > nw[j] + 1 &&
                   !check(sta[j][sta_len[j] - 2], sta[j][sta_len[j] - 1], nl)) {
                sta_len[j]--;
            }
            sta[j][sta_len[j]++] = nl;
        }
    }
    printf("%.10f\n", f[n][k]);
    return 0;
}
