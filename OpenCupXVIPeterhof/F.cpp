#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

const ll INF = 7e18;
ll ans, a, b;

int check(ll x, ll y) {
    if(!(x >= -INF && x <= INF))
	return 0;
    if(!(y >= -INF && y <= INF))
	return 0;
    return 1;
}

ll gcd(ll x, ll y) {
    return y == 0 ? x : gcd(y, x % y);
}
int exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
	x = 1;
	y = 0;
	return a;
    }
    ll ret = exgcd(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return ret;
}
void calcu(ll x, ll y, ll n, ll m) {
    if(x < 0)
	x = -x;
    if(y < 0)
	y = -y;
    if(n < 0)
	n = -n;
    if(m < 0)
	m = -m;
    
    if(x % 2 == n % 2 && y % 2 == m % 2) {
	ll tmp = max(x, n) + max(y, m);
	if(ans == -1) {
	    ans = tmp;
	}
	else {
	    ans = min(ans, tmp);
	}
    }
    return;
}

void tryval(ll key) {
    ll x, y;
    exgcd(a, b, x, y);
    ll cx = x, cy = y;
    ll t = (-x + key) / b;
    x = x + t * b;
    y = y - t * a;
    ll tx = x, ty = y;
    for(ll k = 0; k <= 1000000; k++) {
	calcu(tx, ty, 0, 0);
	calcu(tx, ty, a, -b);
	if(check(tx, ty) == 0)
	    break;
	tx -= b;
	ty += a;
    }
    tx = x, ty = y;
    for(ll k = 0; k <= 1000000; k++) {
	calcu(tx, ty, 0, 0);
	calcu(tx, ty, a, -b);
	if(check(tx, ty) == 0)
	    break;
	tx += b;
	ty -= a;
    }
    x = cx;
    y = cy;
    t = (-y + key) / a;
    x = x - t * b;
    y = y + t * a;
    tx = x;
    ty = y;
    for(ll k = 0; k <= 1000000; k++) {
	calcu(tx, ty, 0, 0);
	calcu(tx, ty, a, -b);
	if(check(tx, ty) == 0)
	    break;
	tx += b;
	ty -= a;
    }
    tx = x;
    ty = y;
    for(ll k = 0; k <= 1000000; k++) {
	calcu(tx, ty, 0, 0);
	calcu(tx, ty, a, -b);
	if(check(tx, ty) == 0)
	    break;
	tx -= b;
	ty += a;
    }
}

void solve() {
    ans = -1;
    if(a == 0 || b == 0) {
	if(a == 0 && b == 0) {
	    printf("-1\n");
	    return;
	}
	if(a == 1 || b == 1) {
	    printf("1\n");
	    return;
	}
	else {
	    printf("-1\n");
	    return;
	}
    }
    else {
	ll g = gcd(a, b);
	if(g != 1 || (a + b) % 2 == 0) {
	    printf("-1\n");
	    return;
	}
	else {
	    /*ll x, y;
	    exgcd(a, b, x, y);
	    ll cx = x, cy = y;
	    ll t = (-x) / b;
	    x = x + t * b;
	    y = y - t * a;
	    ll tx = x, ty = y;
	    for(ll k = 0; k <= 1000000; k++) {
		calcu(tx, ty, 0, 0);
		calcu(tx, ty, a, -b);
		if(check(tx, ty) == 0)
		    break;
		tx -= b;
		ty += a;
	    }
	    tx = x, ty = y;
	    for(ll k = 0; k <= 100000000; k++) {
		calcu(tx, ty, 0, 0);
		calcu(tx, ty, a, -b);
		if(check(tx, ty) == 0)
		    break;
		tx += b;
		ty -= a;
	    }
	    x = cx;
	    y = cy;
	    t = (-y) / a;
	    x = x - t * b;
	    y = y + t * a;
	    tx = x;
	    ty = y;
	    for(ll k = 0; k <= 1000000; k++) {
		calcu(tx, ty, 0, 0);
		calcu(tx, ty, a, -b);
		if(check(tx, ty) == 0)
		    break;
		tx += b;
		ty -= a;
	    }
	    tx = x;
	    ty = y;
	    for(ll k = 0; k <= 1000000; k++) {
		calcu(tx, ty, 0, 0);
		calcu(tx, ty, a, -b);
		if(check(tx, ty) == 0)
		    break;
		tx -= b;
		ty += a;
		}*/
	    tryval(0);
	    //tryval(a);
	    //tryval(b);
	    //tryval(-a);
	    //tryval(-b);
	    printf("%lld\n", ans);
	}
    }
}
int main() {
    //freopen("F.txt", "r", stdin);
    freopen("pqknight.in", "r", stdin);
    freopen("pqknight.out", "w", stdout);
    while(scanf("%lld %lld", &a, &b) != EOF) {
	solve();
    }
    return 0;
}
