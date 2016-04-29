#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
using namespace std;
const int N = 200010;
struct node {
    int x, y, val;
    node (int _x = 0, int _y = 0, int _v = 0) : x(_x), y(_y), val(_v) {}
}e[N << 1];
bool operator < (const node &A, const node &B) {
    return A.val < B.val;
}
int f[N], Rank[N];
int gf(int x) {
    return x == f[x] ? x : f[x] = gf(f[x]);
}
int merge(int x, int y) {
    int i = gf(x), j = gf(y);
    if (Rank[i] < Rank[j]) {
	f[i] = j;
	f[x] = j;
    }
    else {
	f[j] = i;
	f[y] = i;
	if (Rank[i] == Rank[j]) {
	    Rank[i] ++;
	}
    }
}
bool judge(int x, int y) {
    return gf(x) == gf(y);
}
vector <int> G[N];
vector <int> driver[N];
int bus[N];
int deep[N];
struct comp {
    int x, id;
    comp(int _x = 0, int _i = 0) : x(_x), id(_i) {}
};
bool operator < (const comp &A, const comp &B) {
    return A.x < B.x;
}
void dfs(int x, int pre) {
    comp mx = comp(0, x);
    for (int i = 0; i < G[x].size(); ++ i) {
	if (G[x][i] == pre) continue;
	dfs(G[x][i], x);
	mx = max(mx, comp(deep[G[x][i]], G[x][i]));
	printf("Drive %d %d %d\n", bus[G[x][i]], G[x][i], x);
    }
    if (mx.id != x) {
	bus[x] = bus[mx.id];
	printf("Move %d %d %d\n", x, x, bus[x]);
    }
    deep[x] = mx.x;
    for (int i = 0; i < G[x].size(); ++ i) {
	if (G[x][i] == pre) continue;
	int v = G[x][i];
	if (bus[v] != bus[x] && deep[v] == deep[x]) {
	    deep[x] ++;
	}
	for (int j = 0; j < driver[v].size(); ++ j) {
	    driver[x].push_back(driver[v][j]);
	    if (bus[v] != bus[x]) {
		printf("Move %d %d %d\n", driver[v][j], bus[v], bus[x]);
	    }
	}
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i) {
	f[i] = i;
	Rank[i] = 1;
	driver[i].push_back(i);
	bus[i] = i;
    }
    for (int i = 0; i < m; ++ i) {
	scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].val);
    }
    sort(e, e + m);
    int ans = 0, num = 0;
    for (int i = 0; i < m; ++ i) {
	if (!judge(e[i].x, e[i].y)) {
	    merge(e[i].x, e[i].y);
	    G[e[i].x].push_back(e[i].y);
	    G[e[i].y].push_back(e[i].x);
	    ans += e[i].val;
	    num ++;
	    if (num == n - 1) {
		break;
	    }
	}
    }
    printf("%d\n", ans);
    dfs(1, -1);
    puts("Done");
    return 0;
}
