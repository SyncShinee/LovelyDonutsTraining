#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 7;
const int M = 1e5 + 7;
struct node {
    int to, nxt;
}e[N << 1];
int head[N], side;
int anc[N][20], dep[N];
int in[N], out[N], cnt, n;
void build(int x, int y) {
    e[side].to = y;
    e[side].nxt = head[x];
    head[x] = side ++;
}
stack <int> sta;
void dfs() {
    anc[1][0] = -1;
    dep[1] = 0;
    in[1] = ++ cnt;
    sta.push(1);
    while (!sta.empty()) {
        int u = sta.top();
        if (head[u] == -1) {
            sta.pop();
            out[u] = cnt;
        } else {
            int &v = head[u];
            if (e[v].to != anc[u][0]) {
                dep[e[v].to] = dep[u] + 1;
                anc[e[v].to][0] = u;
                in[e[v].to] = ++ cnt;
                sta.push(e[v].to);
            }
            v = e[v].nxt;
        }
    }
}
int LCA(int x, int y) {
    int lo;
    if (dep[x] < dep[y]) swap(x, y);
    for (lo = 1; (1 << lo) <= dep[x]; ++ lo);
    -- lo;
    for (int i = lo; i >= 0; -- i) {
        if (dep[x] - (1 << i) >= dep[y]) {
            x = anc[x][i];
        }
    }
    if (x == y) return x;
    for (int i = lo; i >= 0; -- i) {
        if (anc[x][i] > 0 && anc[y][i] != anc[x][i]) {
            x = anc[x][i];
            y = anc[y][i];
        }
    }
    return anc[x][0];
}
int lenm, lenq;
struct Modify {
    int id, x, y, val;
    Modify(int _i = 0, int _x = 0, int _y = 0, int _v = 0) {
        id = _i, x = _x, y = _y, val = _v;
    }
}modify[M];
struct Query {
    int id, x, a, b, k;
    Query(int _i = 0, int _x = 0, int _s = 0, int _e = 0, int _k = 0) {
        id = _i, x = _x, a = _s, b = _e, k = _k;
    }
}query[M];
int ans[M], num[M];
bool cmpmv(const Modify &A, const Modify &B) {
    return A.val < B.val;
}
bool cmpmi(const Modify &A, const Modify &B) {
    return A.id < B.id;
}
bool cmpqv(const Query &A, const Query &B) {
    return num[A.id] - A.k > num[B.id] - B.k;
}
bool cmpqi(const Query &A, const Query &B) {
    return A.id < B.id;
}
struct Query1 {
    int id, x, l;
    Query1 (int _i = 0, int _x = 0, int _l = 0) {
        id = _i, x = _x, l = _l;
    }
}tds[M << 1], ref[M << 2];
int len_tds, len_ref;
bool operator < (const Query1 &A, const Query1 &B) {
    return A.l < B.l;
}
int C[N];
void upd(int x, int val) {
    while (x <= n) {
        C[x] += val;
        x += x & -x;
    }
}
int get(int L, int R) {
    int ret = 0;-- L;
    while (R) {
        ret += C[R];
        R -= R & -R;
    }
    while (L) {
        ret -= C[L];
        L -= L & -L;
    }
    return ret;
}
void solve(int ml, int mr, int ql, int qr) {
    int mid = ml + mr >> 1;
    sort(modify + ml, modify + mid + 1, cmpmi);
    len_tds = 0;
    for (int i = ql; i <= qr; ++ i) {
        num[query[i].id] = 0;
        tds[len_tds ++] = Query1(query[i].id, query[i].x, query[i].a - 1);
        tds[len_tds ++] = Query1(query[i].id, query[i].x, query[i].b);
    }
    sort(tds, tds + len_tds);
    int nw = ml;
    len_ref = 0;
    for (int i = 0; i < len_tds; ++ i) {
        while (nw <= mid && modify[nw].id <= tds[i].l) {
            int x = modify[nw].x, y = modify[nw].y;
            int lca = LCA(x, y);
            upd(in[x], 1);
            ref[len_ref ++] = Query1(in[x], -1);
            upd(in[y], 1);
            ref[len_ref ++] = Query1(in[y], -1);
            upd(in[lca], -1);
            ref[len_ref ++] = Query1(in[lca], 1);
            if (anc[lca][0] != -1) {
                upd(in[anc[lca][0]], -1);
                ref[len_ref ++] = Query1(in[anc[lca][0]], 1);
            }
            ++ nw;
        }
        num[tds[i].id] = get(in[tds[i].x], out[tds[i].x]) - num[tds[i].id];
    }
    for (int i = 0; i < len_ref; ++ i) {
        upd(ref[i].id, ref[i].x);
    }
    sort(query + ql, query + qr + 1, cmpqv);
    sort(modify + ml, modify + mid + 1, cmpmv);
    int midq = ql;
    while (midq <= qr && num[query[midq].id] - query[midq].k >= 0) midq ++;
    if (modify[ml].val == modify[mid].val) {
        for (int i = ql; i < midq; ++ i) {
            ans[query[i].id] = modify[ml].val;
        }
    } else {   
        if (ql < midq) solve(ml, mid, ql, midq - 1);
    }
    for (int i = midq; i <= qr; ++ i) {
        query[i].k -= num[query[i].id];
    }
    if (mid + 1 <= mr && midq <= qr) solve(mid + 1, mr, midq, qr);
}
int main() {
    int x, y, z, a;
    while (~scanf("%d", &n)) {
        memset(head, -1, sizeof head);
        side = cnt = 0;
        for (int i = 1; i < n; ++ i) {
            scanf("%d%d", &x, &y);
            build(x, y);
            build(y, x);
        }
        dfs();        
        for (int j = 1; (1 << j) <= n; ++ j) {
            for (int i = 1; i <= n; ++ i) {
                anc[i][j] = -1;
            }
        }
        for (int j = 1; (1 << j) <= n; ++ j) {
            for (int i = 1; i <= n; ++ i) {
                if (anc[i][j - 1] > 0) {
                    anc[i][j] = anc[anc[i][j - 1]][j - 1];
                }
            }
        }       
        memset(ans, -1, sizeof ans);
        int q, type;
        lenm = lenq = 0;
        scanf("%d", &q);
        for (int i = 1; i <= q; ++ i) {
            scanf("%d", &type);
            if (type == 1) {
                scanf("%d%d%d", &x, &y, &z);
                modify[lenm ++] = Modify(i, x, y, z);
            } else {
                scanf("%d%d%d%d", &a, &x, &y, &z);
                query[lenq ++] = Query(i, a, x, y, z);
            }
        }
        sort(modify, modify + lenm, cmpmv);
        solve(0, lenm - 1, 0, lenq - 1);
        sort(query, query + lenq, cmpqi);
        for (int i = 0; i < lenq; ++ i) {
            printf("%d\n", ans[query[i].id]);
        }
    }
    return 0;
}
