#include <bits/stdc++.h>

using namespace std;

const int N = 100;
const int maxn = 300 + 10;
typedef long double ld;
const ld eps = 1e-8;

int l[N], r[N], n;
int xa[maxn], xn;

void pre() {
    xn = 0;
    for(int i = 0; i < n; i++) {
	xa[xn] = l[i];
	xn++;
	xa[xn] = r[i];
	xn++;
    }
    sort(xa, xa + xn);
    xn = unique(xa, xa + xn) - xa;
}

ld f(ld x, int i, int j) {
    ld ans = x;
    for(int k = 0; k < n; k++) {
	if(k == i) {
	    if(x < l[k]) {
		ans *= 1;
	    }
	    else if(x > r[k]) {
		ans = 0;
	    }
	    else {
		ans *= (r[k]*1.0 - x) / (r[k]*1.0 - l[k]*1.0);
	    }
	}
	else if(k == j) {
	    if(x < l[k] || x > r[k]) {
		ans *= 0;
	    }
	    else {
		ans /= (r[k] * 1.0 - l[k] * 1.0);
	    }
	}
	else {
	    if(x < l[k]) {
		ans = 0;
	    }
	    else if(x > r[k]) {
		ans *= 1;
	    }
	    else {
		ans *= (x - l[k] * 1.0) / (r[k] * 1.0 - l[k] * 1.0);
	    }
	}
    }
    return ans;
}

ld simpson(ld a, ld b, int i, int j) {
    ld m = a + (b - a) / 2;
    return (b - a) * (f(a, i, j) + 4 * f(m, i, j) + f(b, i, j)) / 6;
}
ld asr(ld a, ld b, ld e, ld A, int i, int j) {
    ld m = a + (b - a) / 2;
    ld L = simpson(a, m, i, j), R = simpson(m, b, i, j);
    if(fabs(L + R - A) <= 15 * e) return L + R + (L + R - A) / 15;
    return asr(a, m, e / 2, L, i, j) + asr(m, b, e / 2, R, i, j);
}
ld asr(ld a, ld b, ld e, int i, int j) {
    return asr(a, b, e, simpson(a, b, i, j), i, j);
}



void solve() {
    pre();
    ld ans = 0;
    for(int i = 0; i < n; i++) {
	for(int j = 0; j < n; j++) {
	    if(i == j) continue;
	    for(int k = 0; k < xn - 1; k++) {
		ld la = xa[k], rb = xa[k + 1];
		ans += asr(la, rb, eps, i, j);
	    }
	}
    }
    printf("%.15f\n", (double)ans);
}


int main(){
    // freopen("H.txt", "r", stdin);
	freopen("secondmax.in", "r", stdin);
	freopen("secondmax.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i){
	scanf("%d %d", &l[i], &r[i]);
    }
    solve();
    return 0;
}
