#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
using namespace std;
const int N = 150001;
int a[N];
int K;
struct TreeNode {
    int tag;
    int color[5];
    int count[5];
}T[N << 2];
TreeNode pushUp(TreeNode A, const TreeNode &B) {
    for (int i = 0; i < K; ++ i) {
        if (B.count[i]) {
            int j, mn = 0;
            for (j = 0; j < K; ++ j) {
                if (A.count[j] < A.count[mn]) {
                    mn = j;
                }
                if (A.color[j] == B.color[i]) {
                    break;
                }
            }
            if (j < K) {
                A.count[j] += B.count[i];
                continue;
            }
            if (A.count[mn] < B.count[i]) {
                int tmp = A.count[mn];
                for (j = 0; j < K; ++ j) {
                    A.count[j] -= tmp;
                }
                A.count[mn] = B.count[i] - tmp;
                A.color[mn] = B.color[i];
            } else {
                for (j = 0; j < K; ++ j) {
                    A.count[j] -= B.count[i];
                }
            }
        }
    }
    A.tag = 0;
    return A;
}
void pushDown(int l, int r, int rt) {
    int mid = l + r >> 1;
    memset(&T[rt << 1], 0, sizeof T[rt << 1]);
    memset(&T[rt << 1 | 1], 0, sizeof T[rt << 1 | 1]);
    T[rt << 1].tag = T[rt << 1 | 1].tag = T[rt].tag;
    T[rt << 1].color[0] = T[rt << 1 | 1].color[0] = T[rt].tag;
    T[rt].tag = 0;
    T[rt << 1].count[0] = mid - l + 1;
    T[rt << 1 | 1].count[0] = r - mid;
}
void build(int l, int r, int rt) {
    if (l == r) {
        T[rt].color[0] = a[l];
        T[rt].count[0] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(lson);
    build(rson);
    T[rt] = pushUp(T[rt << 1], T[rt << 1 | 1]);
}
void update(int cl, int cr, int col, int l, int r, int rt) {
    if (cl <= l && r <= cr) {
        memset(&T[rt], 0, sizeof T[rt]);
        T[rt].tag = col;
        T[rt].color[0] = col;
        T[rt].count[0] = r - l + 1;
        return;
    }
    if (T[rt].tag) {
        pushDown(l, r, rt);
    }
    int mid = l + r >> 1;
    if (cl <= mid) {
        update(cl, cr, col, lson);
    }
    if (mid + 1 <= cr) {
        update(cl, cr, col, rson);
    }
    T[rt] = pushUp(T[rt << 1], T[rt << 1 | 1]);
}
TreeNode query(int cl, int cr, int l, int r, int rt) {
    if (cl <= l && r <= cr) {
        return T[rt];
    }
    if (T[rt].tag) {
        pushDown(l, r, rt);
    }
    int mid = l + r >> 1;
    if (cr <= mid) {
        return query(cl, cr, lson);
    }
    if (cl >= mid + 1) {
        return query(cl, cr, rson);
    }
    return pushUp(query(cl, cr, lson), query(cl, cr, rson));
}
int main() {
    int n, q, p, type, l, r, id;
    scanf("%d%d%d", &n, &q, &p);
    K = 100 / p;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
    }
    build(1, n, 1);
    while (q --) {
        scanf("%d%d%d", &type, &l, &r);
        if (type == 1) {
            scanf("%d", &id);
            update(l, r, id, 1, n, 1);
        } else {
            TreeNode ans = query(l, r, 1, n, 1);
            printf("%d", K);
            for (int i = 0; i < K; ++ i) {
                printf(" %d", ans.color[i]);
            }
            puts("");
        }
    }
    return 0;
}
