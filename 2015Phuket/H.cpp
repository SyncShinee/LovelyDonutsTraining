#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e4 + 100;

int gpa[maxn], n, p;
int num[maxn], tot;
int fen[maxn];

void solve() {
    int ans = 0;
    for(int gpas = 250; gpas <= 400; gpas++) {
        for(int gpad = 1; gpad + gpas - 1 < 400; gpad++) {
            tot = 0;
            int l = gpas, r;
            for(int i = 0; l <= 400; i++) {
                //printf("***  %d\n", l);
                tot = i + 1;
                r = l + gpad - 1;
                r = min(400, r);
                num[i] = fen[r] - fen[l - 1];
                l = r + 1;
            }
            int sum = 0, sumr = 0;
            for(int i = 0; i < tot; i++) {
                sum += i * num[i];
                sumr += num[i];
            }            
            for(int d = 1; d * sum <= p && d <= 100; d++) {
                if(sumr == 0) {
                    if(p == 0) {
                        int maxa = d * (tot - 1);
                        if(maxa <= 100)
                            ans += 100 - maxa + 1;
                    }   
                } else {
                    int lft = p - d * sum;
                    if(lft > 0 && lft % sumr == 0) {
                        int maxa = d * (tot - 1) + lft / sumr;
                        if(maxa <= 100)
                            ans++;
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
}

int main() {
    freopen("H.txt", "r", stdin);
    while(scanf("%d%d", &n, &p)) {
        if(!n && !p) break;
        for(int i = 0; i <= 400; i++) fen[i] = 0;
        for(int i = 0; i < n; i++) {
            double t;
            scanf("%lf", &t);
            t *= 100 + 0.2;
            gpa[i] = t;
            fen[gpa[i]]++;
        }
        for(int i = 1; i <= 400; i++) {
            fen[i] = fen[i] + fen[i - 1];
        }
        //        sort(gpa, gpa + n);
        solve();
    }
    return 0;
}
