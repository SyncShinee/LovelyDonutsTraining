
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n;
int main(){
    scanf("%d", &n);
    ll tota = 0, totb = 0, totc = 0;
    while (n--){
        ll a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        tota += a; totb += b; totc += c;
        ll mn = min(tota, totb); mn = min(mn, totc);
        if (mn < 30){
            puts("NO");
        }else{
            printf("%lld\n", mn);
            tota -= mn; totb -= mn; totc -= mn;
        }
    }
}
