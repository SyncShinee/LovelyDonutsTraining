#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const double Pi = acos(-1.0);

double R, V;

void solve() {
    printf("%f\n", 0.15707963 * 2);
}

int main() {
    freopen("I.txt", "r", stdin);
    //solve();
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
        printf("Case %d: ", _);
        scanf("%lf%lf", &R, &V);
        printf("%.10f\n", R / V * Pi / 2);
    }
    return 0;
}
