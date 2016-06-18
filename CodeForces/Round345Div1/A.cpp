#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
typedef long long ll;
map<int, int> mp1, mp2;
map<pair<int, int>, int> st;
int main() {
    int n, x, y;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &x, &y);
        mp1[x]++;
        mp2[y]++;
        pair <int, int> p = make_pair(x, y);
        st[p]++;
    }
    ll ans = 0;
    for (map<int, int> :: iterator it = mp1.begin(); it != mp1.end(); ++ it) {
        ans += 1ll * it->second * (it->second - 1) / 2;
    }
    
    for (map<int, int> :: iterator it = mp2.begin(); it != mp2.end(); ++ it) {
        ans += 1ll * it->second * (it->second - 1) / 2;
    }
    for (map<pair<int, int>, int> :: iterator it = st.begin(); it != st.end(); ++ it) {
        ans -= 1ll * it->second * (it->second - 1) / 2;
    }
    printf("%lld\n", ans);
    return 0;
}
