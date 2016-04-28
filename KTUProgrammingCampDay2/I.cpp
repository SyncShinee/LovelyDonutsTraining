#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#include <vector>
#include <set>
using namespace std;
const int N = 100010;
int n, k, ans;
vector <int> gra[N];
int f[N][2];
struct node {
    int id, val;
    node (int _i = 0, int _v = 0) : id(_i), val(_v) {}
};
bool operator < (const node &A, const node &B) {
    return A.val > B.val;
}
void dfs(int x) {
    priority_queue <node> qk;
    priority_queue <int> qk1;
    set <int> st;
    int sumk1 = 0, sumk = 0;
    f[x][0] = f[x][1] = 1;
    for (int i = 0; i < gra[x].size(); ++ i) {
	dfs(gra[x][i]);
	qk1.push(f[gra[x][i]][0]);
	sumk1 += f[gra[x][i]][0];
	if (qk1.size() > k - 1) {
	    sumk1 -=  qk1.top();
	    qk1.pop();
	}
	qk.push(node(gra[x][i], f[gra[x][i]][0]));
	sumk += f[gra[x][i]][0];
	if (qk.size() > k) {
	    node tmp = qk.top();
	    qk.pop();
	    sumk -= tmp.val;
	}
    }
    f[x][0] += sumk1;
    f[x][1] += sumk;
    while (!qk.empty()) {
	st.insert(qk.top().id);
	qk.pop();
    }
    for (int i = 0; i < gra[x].size(); ++ i) {
	if (st.find(gra[x][i]) != st.end()) {
	    f[x][1] = max(f[x][1], 1 + sumk - f[gra[x][i]][0] + f[gra[x][i]][1]);
	}
	else {
	    f[x][1] = max(f[x][1], 1 + sumk1 + f[gra[x][i]][1]);
	}
    }
    //printf("%d %d\n", sumk, sumk1);
    //printf("%d ----- %d %d\n", x, f[x][0], f[x][1]);
}
int Rank[N];
void dfs2(int x) {
    vector <node> V;
    for (int i = 0; i < gra[x].size(); ++ i) {
	dfs2(gra[x][i]);
	V.push_back(node(gra[x][i], f[gra[x][i]][0]));
    }
    sort(V.begin(), V.end());
    for (int i = 0; i < V.size(); ++ i) {
	Rank[V[i].id] = i;
    }
    int limit = k;
    int sum = 0, sum1 = 0;
    for (int i = 0; i < limit - 1 && i < V.size(); ++ i) {
	sum += V[i].val;
    }
    f[x][0] = sum + 1;
    for (int i = 0; i < limit && i < V.size(); ++ i) {
	sum1 += V[i].val;
    }
    f[x][1] = sum1 + 1;
    for (int i = 0; i < gra[x].size(); ++ i) {
	if (Rank[gra[x][i]] >= limit - 1) {
	    f[x][1] = max(f[x][1], 1 + sum + f[gra[x][i]][1]);
	}
	else {
	    f[x][1] = max(f[x][1], 1 + sum1 - f[gra[x][i]][0] + f[gra[x][i]][1]);
	}
    }
}
int main() {
    int num, x;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++ i) {
	scanf("%d", &num);
	for (int j = 0; j < num; ++ j) {
	    scanf("%d", &x);
	    gra[i].push_back(x);
	}
    }
    dfs2(1);
    printf("%d\n", max(f[1][0], f[1][1]));
    return 0;
}
