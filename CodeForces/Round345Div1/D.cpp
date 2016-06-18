#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int N = 4e5 + 7;
struct node {
    int x, v, id;
    node (int _x = 0, int _v = 0, int _i = 0) : x(_x), v(_v), id(_id) {}
}q[N];
bool operator < (const node &A, const node &B) {
    return A.x < B.x;
}
int a[N];
int main() {
    int n, Q;
    scanf("%d%d", &n, &Q);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < Q; ++ i) {
        scanf("%d%d", &q[i].x, &q[i].v);
        q[i].id = i;
    }
    sort(q, q + Q);
    for (int i = 1; i <= n; ++ i) {
        
    }
    return 0;
}
