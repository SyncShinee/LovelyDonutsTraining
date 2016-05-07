#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

const int maxn = 1000 + 10;

int f[maxn];
int a, b;

int calcu(int x, int m) {
    
    x = x % m;
    int oldx = x;
    int cnt = 1;
    x = (ll)x * (ll)x % m;
    while(1) {
	if(x == oldx) {
	    break;
	}
	cnt++;
	x = (ll)x * (ll)oldx % m;
    }
    return cnt;
}
void solve() {
    f[a] = 10;
    for(int i = a + 1; i <= b; i++) {
	f[i] = calcu(i - 1, f[i - 1]);
    }
    
    
    ll ans = b % f[b];
    for(int i = b - 1; i >= a; i--) {
	
	    ll tmp = ans;
	    ans = 1;
	    for(int j = 0; j < tmp; j++) {
		ans = ans * (ll)i % f[i];
	    }
	    if(i % f[i] == 0) {
		ans = 0;
	    }   
	
	//	printf("%d --   %lld\n", i, ans);  
    }
    //cout << a << "  " << b << "  " << ans << endl;
    if(a == 5 || a == 6) {
	cout << a << endl;
    }
    else {
	cout << ans << endl;
    }
}

int main() {
    //freopen("A.txt", "r", stdin);
    freopen("abtower.in", "r", stdin);
    freopen("abtower.out", "w", stdout);
    while(scanf("%d%d", &a, &b) != EOF) {
	solve();
	}
    return 0;
}
