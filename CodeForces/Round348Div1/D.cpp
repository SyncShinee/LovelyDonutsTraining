#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int N = 100010;
int V[N];
map<int, int> C[N];
int len;
struct node {
    int a, t, x;
}q[N];
void update(int x, int val, int num) {
    while (x < len) {
        C[x][val] += num;
        x += x & -x;
    }
}
int getsum(int x, int val) {
    int ret = 0;
    while (x) {
        if (C[x].count(val)) ret += C[x][val];
        x -= x & -x;
    }
    return ret;
}
int main() {
    int n;
    len = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", &q[i].a, &q[i].t, &q[i].x);
        V[++ len] = q[i].t;
    }
    
    sort(V + 1, V + len + 1);
    len = unique(V + 1, V + len + 1) - V;
    for (int i = 0; i < n; ++ i) {
        if (q[i].a == 1) {
            int pos = lower_bound(V + 1, V + len, q[i].t) - V;
            update(pos, q[i].x, 1);
        } else if (q[i].a == 2) {
            int pos = lower_bound(V + 1, V + len, q[i].t) - V;
            update(pos, q[i].x, -1);
        } else {
            int pos = lower_bound(V + 1, V + len, q[i].t) - V;
            printf("%d\n", getsum(pos, q[i].x));
        }
    }
    return 0;
}
