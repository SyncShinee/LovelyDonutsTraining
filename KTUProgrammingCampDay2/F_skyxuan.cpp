#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
using namespace std;
const int N = 100010;
int Q;
struct node {
    int len, k, id;
}q[N];
bool operator <(const node &A, const node &B) {
    return A.len > B.len;
}
int sa[N], t1[N], t2[N], c[N];
int Rank[N];
void buildsa(char *s, int n, int m) {
    int i, k, p, a1, a2, *x = t1, *y = t2;
    memset(c, 0, m << 2);
    for (i = 0; i < n; ++ i) ++ c[x[i] = s[i]];
    for (i = 1; i < m; ++ i) c[i] += c[i - 1];
    for (i = n - 1; i >= 0; -- i) sa[--c[x[i]]] = i;
    for (k = 1, p = 0; k < n; k <<= 1, p = 0) {
	for (i = n - k; i < n; ++ i) y[p ++] = i;
	for (i = 0; i < n; ++ i) if (sa[i] >= k) y[p ++] = sa[i] - k;
	memset(c, 0, m << 2);
	for (i = 0; i < n; ++ i) ++ c[x[y[i]]];
	for (i = 1; i < m; ++ i) c[i] += c[i - 1];
	for (i = n - 1; i >= 0; -- i) sa[-- c[x[y[i]]]] = y[i];
	swap(x, y), p = 1, x[sa[0]] = 0;
	for (i = 1; i < n; ++ i) {
	    a1 = sa[i - 1] + k < n ? y[sa[i - 1] + k] : -1;
	    a2 = sa[i] + k < n ? y[sa[i] + k] : -1;
	    x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && a1 == a2) ? p - 1 : p ++;
	}
	if (p >= n) break;
	m = p;
    }
    for (i = 0; i < n; ++ i) Rank[sa[i]] = i;
}

char s[N];

int C[N];
int st[N];
int ans[N];
int main() {
    scanf("%s", s);
    int len = strlen(s);
    scanf("%d", &Q);
    for (int i = 0; i < Q; ++ i) {
	scanf("%d%d", &q[i].len, &q[i].k);
	q[i].id = i;
    }
    sort(q, q + Q);
    buildsa(s, len, 128);
    int nw = len + 1;
    for (int i = 0; i < Q; ++ i) {
	while (nw > 1 && nw > q[i].len) {
	    nw --;
	    for (int j = Rank[len - nw] + 1; j <= len; j += j & -j)
		C[j]++;
	    st[Rank[len - nw] + 1] = len - nw + 1;
	}
	int base = 0, k = q[i].k;
	for (int K = 16; K >= 0; -- K) {
	    int x = 1 << K;
	    if (base + x <= len && C[base + x] < k) {
		base += x;
		k -= C[base];
	    }
	}
	ans[q[i].id] = st[base + 1];
    }
    for (int i = 0; i < Q; ++ i) {
	printf("%d\n", ans[i]);
    }
    return 0;
}

