#include <bits/stdc++.h>
#define FI first
#define SE second
#define MP make_pair
#define PB push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
const int MOD = 1e9 + 7.1;
typedef pair <int, int> PII;
typedef pair <long double, int> PDI;
char s[1024];
vector <int> p;
vector <PII> P;
vector <PDI> fac1, fac2;
int num[128];
long double logm;
int m;
int pow_mod(int x, int p) {
    int ret = 1;
    while (p) {
        if (p & 1) {
            ret = 1ll * ret * x % MOD;
        }
        x = 1ll * x * x % MOD;
        p >>= 1;
    }
    return ret;
}
void dfs(long double logn, int nw, int l, int r, vector <PDI> &V) {
    if (l == r) {
        V.PB(MP(logn, nw));
        return;
    }
    for (int i = 0; i <= P[l].SE; ++ i) {
        dfs(logn + (long double)i * log(P[l].FI), 1ll * nw * pow_mod(P[l].FI, i) % MOD, l + 1, r, V);
    }
}
int main() {
    while (~scanf("%s", s)) {
        memset(num, 0 , sizeof num);
        logm = 0.;
        m = 1;
        p.clear(), P.clear(), fac1.clear(), fac2.clear();
        int len = strlen(s);
        for (int i = 0; i < len; i += 2) {
            p.PB((s[i] - '0') * 10 + s[i + 1] - '0');
        }
        len /= 2;
        for (int i = 0; i < len; ++ i) {
            num[p[i]]++;
            logm += log(p[i]);
            m = 1ll * m * p[i] % MOD;
        }
        logm /= 2.;
        for (int i = 2; i < 100; ++ i) {
            if (num[i]) {
                P.PB(MP(i, num[i]));
            }
        }
        long long sum = 1;
        int broken = 0;
        while (broken < P.size() && sum < 1e5) {
            sum *= (1 + P[broken].SE);
            broken ++;
        }
        broken--;
        dfs(0., 1, 0, broken, fac1);
        dfs(0., 1, broken, P.size(), fac2);
        sort(all(fac1));
        sort(all(fac2));
        
        long double mx = 0.;
        int ans = 1;
        for (int p1 = 0, p2 = fac2.size() - 1; p1 < fac1.size(); ++ p1) {
            while (p2 >= 0 && fac1[p1].FI + fac2[p2].FI > logm) {
                -- p2;
            }
            if (p2 < 0) break;
            if (p2 >= 0 && mx < fac1[p1].FI + fac2[p2].FI) {;
                mx = fac1[p1].FI + fac2[p2].FI;
                ans = 1ll * fac1[p1].SE * fac2[p2].SE % MOD;
            }
        }
        printf("%d\n", (int)((ans + 1ll * m * pow_mod(ans, MOD - 2) % MOD) % MOD));
    }
    return 0;
}
