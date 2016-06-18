#include <bits/stdc++.h>
#define FI first
#define SE second
using namespace std;
const int N = 1e5 + 7;
const double PI = acos(-1.0);
const double EPS = 1e-8;
pair <int, int> V[N], P;
double dis(pair<int, int> A, pair<int, int> B) {
    return 1ll * (A.FI - B.FI) * (A.FI - B.FI) + 1ll * (A.SE - B.SE) * (A.SE - B.SE);
}
double dist(pair<int, int> A, pair<int, int> B) {
    return sqrt(1ll * (A.FI - B.FI) * (A.FI - B.FI) + 1ll * (A.SE - B.SE) * (A.SE - B.SE));
}
double cross(pair <int, int> A, pair <int, int> B, pair <int, int> C) {
    return 1ll * (C.FI - A.FI) * (B.SE - A.SE) - 1ll * (C.SE - A.SE) * (B.FI - A.FI);
}
bool judge(pair <int, int> A, pair <int, int> B, pair <int, int> C) {
    return dis(A, B) + dis(B, C) - dis(A, C) >= -EPS &&
        dis(A, C) + dis(B, C) - dis(A, B) >= -EPS;
}
int main() {
    int n;
    scanf("%d%d%d", &n, &P.FI, &P.SE);
    double mn = -1., mx = -1.;
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &V[i].FI, &V[i].SE);
        mx = max(mx, dist(V[i], P));
        mn = mn < -0.5 ? dist(V[i], P) : min(mn, dist(V[i], P));
    }
    for (int i = 0; i < n; ++ i) {
        int j = (i + 1) % n;
        if (judge(P, V[i], V[j])) {
            mn = min(mn, fabs(cross(P, V[i], V[j])) / dist(V[i], V[j]));
        }
    }
    printf("%.10f\n", mx * mx * PI - mn * mn * PI);
    return 0;
}
