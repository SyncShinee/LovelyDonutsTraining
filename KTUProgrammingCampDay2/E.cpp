#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
using namespace std;
const int N = 200010;
struct node {
    int x, y, val;
    node (int _x = 0, _y = 0, _v = 0) : x(_x), y(_y), val(_v) {}
}e[N << 1];
operator < (const node &A, const int &B) {
    return A.val < B.val;
}
vector <string> ans;
int f[N], Rank[N];
int gf(int x) {
    return x == f[x] ? x : f[x] = gf(f[x]);
}
int merge(int x, int y) {
    int i = gf(x), j = gf(y);
    if (Rank[i] < Rank[j]) {
	
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
	f[i] = i;
	Rank[i] = 1;
    }
    for (int i = 0; i < m; ++ i) {
	scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].val);
    }
    sort(e, e + m);
    
    return 0;
}
