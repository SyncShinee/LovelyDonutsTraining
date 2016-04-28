#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 100010;
int a[N];
ll b[N];
int d, n;
bool check(ll k) {
    b[0] = a[0];
    b[0] += 1ll * k * d;
    for (int i = 1; i < n; ++ i) {
	b[i] = a[i];
	ll diff = b[i - 1] - b[i];
	if (diff <= 0) {
	    if (b[i] - 1ll * k * d >= b[i - 1]) {
		return 0;
	    }
	    ll num = ((-diff) / d) + 1;
	    if (num > k) {
		return 0;
	    }
	    else if ((num ^ k) & 1) {
		b[i] -= 1ll * (num + 1) * d;
	    }
	    else {
		b[i] -= 1ll * num * d;
	    }
	}
	else {
	    ll num = (diff - 1) / d;
	    if (num >= k) {
		b[i] += 1ll * k * d;
	    }
	    else if ((num ^ k) & 1){
		b[i] += 1ll * (num - 1) * d;
	    }
	    else {
		b[i] += 1ll * num * d;
	    }
	}
    }
}
int main() {
    scanf("%d%d", &n, &d);
    for (int i = 0; i < n; ++ i) {
	scanf("%d", &a[i]);
    }
    ll l = 0, r = (1ll << 60) / d + 10;
    while (l <= r) {
	ll mid = (l + r) >> 1;
	if (check(mid)) {
	    r = mid - 1;
	}
	else {
	    l = mid + 1;
	}
    }
    printf("%I64d\n", l);
    return 0;
}
