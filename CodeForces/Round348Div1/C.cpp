#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 100010;
double mx[N], smx[N], mn[N], smn[N], p1[N], p2[N];
int main() {
    int n;
    scanf("%d", &n);
    smx[0] = 0.;
    for (int i = 1; i <= n; ++ i) {
        scanf("%lf", &mx[i]);
        smx[i] = smx[i - 1] + mx[i];
    }
    for (int i = 1; i <= n; ++ i) {
        scanf("%lf", &mn[i]);
    }
    smn[n + 1] = 0.;
    for (int i = n; i > 0; -- i) {
        smn[i] = smn[i + 1] + mn[i];
    }
    p1[n] = p2[n] = 1.;
    for (int i = n - 1; i > 0; -- i) {
        double amb = smx[i];
        double aab = 1. + amb - smn[i + 1];
        double det = max(aab * aab - 4. * amb, 0.);
        p1[i] = (aab - sqrt(det)) / 2;
        p2[i] = (aab + sqrt(det)) / 2;
    }
    for (int i = 1; i <= n; ++ i) {
        printf("%f%c", p1[i] - p1[i - 1], " \n"[i == n]);
    }
    
    for (int i = 1; i <= n; ++ i) {
        printf("%f%c", p2[i] - p2[i - 1], " \n"[i == n]);
    }
    return 0;
}
