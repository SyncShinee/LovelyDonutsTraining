#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;

const double eps = 1e-8;

ll a, b, p;


int calcu(ll m) {
    double ans = a * pow(double(m), 1.0 / 3.0) + b * sqrt(double(m));
    if(ans + eps >= p) {
	return 1;
    }
    return 0;
}

void solve() {
    ll l = 1, r = 2e18;
    while(l < r) {
	ll m = (l + r) / 2;
	int t = calcu(m);
	if(t) {
	    r = m;
	}
	else{
	    l = m + 1;
	}
    }
    //    printf("%I64d\n", r);
    cout << r << endl;
}


int main() {
    freopen("K.txt", "r", stdin);
    while(cin >> a >> b >> p) {
	solve();
    }
    return 0;
}
