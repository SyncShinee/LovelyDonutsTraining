#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 1e3 + 100;

ll a[maxn][maxn], sl[maxn][maxn], sr[maxn][maxn], w;
int n;

int calcu1(int x) {
    if(x == 0) {
	return 1;
    }
    x *= 2;
    for(int i = 1; i + x - 1 <= n; i++) {
	for(int j = 1; j + x - 1 <= n; j++) {
	    ll t = sl[i + x - 1][j + x - 1] - sl[i - 1][j - 1];
	    t += sr[i + x - 1][j] - sr[i - 1][j + x - 1 + 1];
	    if(t <= w) {
		return 1;
	    }
	}
    }
    return 0;
}
int calcu2(int x) {
    if(x == 0) {
	for(int i = 1; i <= n; i++) {
	    for(int j = 1; j <= n; j++) {
		if(a[i][j] <= w) {
		    return 1;
		}
	    }
	}
	return 0;
    }
    else {
	x = 2 * x + 1;
	//printf("111  %d\n", x);
	for(int i = 1; i + x - 1 <= n; i++) {
	    for(int j = 1; j + x - 1 <= n; j++) {
		ll t = sl[i + x - 1][j + x - 1] - sl[i - 1][j - 1];
		t += sr[i + x - 1][j] - sr[i - 1][j + x - 1 + 1];
		t -= a[(i + i + x - 1) / 2][(j + j + x - 1) / 2];
		if(t <= w) {
		    return 1;
		}
	    }
	}
	return 0;
    }
}
void solve() {
    memset(sl, 0, sizeof(sl));
    memset(sr, 0, sizeof(sr));
    for(int i = 1; i <= n; i++) {
	for(int j = 1; j <= n; j++) {
	    sl[i][j] = sl[i - 1][j - 1] + a[i][j];
	}
    }
    for(int i = 1; i <= n; i++) {
	for(int j = n; j >= 1; j--) {
	    sr[i][j] = sr[i - 1][j + 1] + a[i][j];
	}
    }
    int res = 0;
    int l = 0, r = n / 2 + 2;
    while(l < r) {
	int m = (l + r) / 2;
	if(calcu1(m)) {
	    l = m + 1;
	}
	else {
	    r = m;
	}
    }
    res = 2 * (r - 1);
    l = 0, r = n / 2 + 2;
    while(l < r) {
	int m = (l + r) / 2;
	if(calcu2(m)) {
	    l = m + 1;
	}
	else {
	    r = m;
	}
    }
    //printf("--%d\n", r - 1);
    if(r - 1 == 0) {
	res = max(res, 1);
    }
    else {
	res = max(res, 2 * (r - 1) + 1);
    }
    //    res = max(res, r - 1);
    printf("%d\n", res);
}

int main() {
    freopen("L.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    while(ncase--) {
        scanf("%d%I64d", &n, &w);
	for(int i = 1; i <= n; i++) {
	    for(int j = 1; j <= n; j++) {
		scanf("%I64d", &a[i][j]);
	    }
	}
	solve();
    }
    return 0;
}
