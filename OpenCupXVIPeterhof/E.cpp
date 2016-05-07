#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long double LD;

const int maxn = 2e5 + 100;

LD x[maxn];
int n;

LD calcu(LD start) {
    LD now = start;
    LD ans = 0;
    for(int i = 0; i < n; i++) {
	//cout << i << "  " << x[i] << endl;
	LD dx = fabs(now - x[i]);
	ans += sqrt(1 + dx * dx);
	now = now + 1;
    }
    return ans;
}

void solve() {
    LD l = -1e7, r = 1e7;
    for(int i = 0; i < 150; i++) {
	LD mid = (l + r) / 2.0;
	LD midmid = (l + mid) / 2.0;
	LD ansmid = calcu(mid);
	LD ansmidmid = calcu(midmid);
	if(ansmid < ansmidmid) {
	    l = midmid;
	}
	else {
	    r = mid;
	}
	
    }
    LD ans = calcu(l);
    double tmp = ans;
    printf("%.11f\n", tmp);
}

int main() {
    //    freopen("E.txt", "r", stdin);
    freopen("make-a-row.in", "r", stdin);
    freopen("make-a-row.out", "w", stdout);
    while(scanf("%d", &n) != EOF) {
	for(int i = 0; i < n; i++) {
	    double t;
	    scanf("%lf", &t);
	    x[i] = t;
	}
	for(int i = 0; i < n; i++) {
	    double t;
	    scanf("%lf", &t);
	    x[i + n] = t;
	}
	n = 2 * n;
	sort(x, x + n);
	solve();
    }
    return 0;
}
