#include <iostream>
#include <cstdio>
#include <cstring>
#include <bitset>
#include <vector>
#include <stack>

#define lrt (rt << 1)
#define rrt (rt << 1 | 1)
#define lson lrt, l, mid
#define rson rrt, mid + 1, r

using namespace std;

const int maxn = 3e5 + 1000;
const int MAXNODE = 4 * maxn + 100;

stack<int> st;
int iter[maxn];
bitset<110> tree[MAXNODE];
int n, q;
vector<int> G[maxn];
int no[maxn], en[maxn], color[maxn], fanno[maxn];
int tot;
void dfs(int u, int fa) {
    tot++;
    no[u] = tot;
    fanno[tot] = u;
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(v != fa) {
            dfs(v, u);
        }
    }
    en[u] = tot;
}

void dfs() {
    while(!st.empty()) {
        st.pop();
    }
    tot = 0;
    st.push(1);
    memset(iter, 0, sizeof(iter));
    while(!st.empty()) {
        int u = st.top();
        if(iter[u] == 0) {
            tot++;
            no[u] = tot;
            fanno[tot] = u;
        }
        if(iter[u] < G[u].size()) {
            st.push(G[u][iter[u]]);
            iter[u]++;
        } else {
            en[u] = tot;
            st.pop();
        }
    }
}

void pushUp(int rt) {
    tree[rt] = (tree[lrt] ^ tree[rrt]);
}

void initail(int rt, int l, int r) {
    if(l == r) {
        tree[rt].reset();
        tree[rt].set(color[fanno[l]]);
        return;
    }
    int mid = (l + r) / 2;
    initail(lson);
    initail(rson);
    pushUp(rt);
}

bitset<110> query(int L, int R, int rt, int l, int r) {
    if(L <= l && R >= r) {
        return tree[rt];
    }
    int mid = (l + r) / 2;
    bitset<110> tmp;
    tmp.reset();
    if(L <= mid) {
        tmp ^= query(L, R, lson);
    }
    if(R >= mid + 1) {
        tmp ^= query(L, R, rson);
    }
    return tmp;
}

void change(int pos, int val, int rt, int l, int r) {
    if(l == r) {
        tree[rt].reset();
        tree[rt].set(val);
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) {
        change(pos, val, lson);
    } else {
        change(pos, val, rson);
    }
    pushUp(rt);
}

void solve() {
    tot = 0;
    //    dfs(1, 0);
    dfs();
    
    initail(1, 1, n);
    for(int i = 1; i <= q; i++) {
        int k, x;
        scanf("%d%d", &k, &x);
        if(k == 0) {
            bitset<110> tmp = query(no[x], en[x], 1, 1, n);
            int num = 0;
            for(int i = 1; i <= 100; i++) {
                if(tmp[i] == 1) num++;
            }
            printf("%d\n", num);
        } else {
            change(no[x], k, 1, 1, n);
        }
    }
}

int main() {
    freopen("J.txt", "r", stdin);
    while(scanf("%d%d", &n, &q) != EOF) {
        for(int i = 1; i <= n; i++) G[i].clear();
        for(int i = 1; i <= n; i++) scanf("%d", &color[i]);
        for(int i = 2; i <= n; i++) {
            int t;
            scanf("%d", &t);
            //zhiyoufuqinlianbian
            G[t].push_back(i);
        }
        solve();
    }
    return 0;
}
