#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 100010;
struct node {
    int id;
    ll val;
    node (int _i = 0, ll _v = 0) : id(_i), val(_v) {}
};
bool operator < (const node &A, const node &B) {
    return A.val < B.val || A.val == B.val && A.id < B.id;
}
set <node> sons[N];
set <node> all;
int parent[N];
ll people[N];
ll sonssum[N];
int sonsnum[N];
void ins(int x) {
    if (sons[x].begin() == sons[x].end()) return;
    node son = *(sons[x].begin());
    son.val += people[x] / (sonsnum[x] + 2);
    all.insert(son);
    son = *(--sons[x].end());
    son.val += people[x] / (sonsnum[x] + 2);
    all.insert(son);
}
void del(int x) {
    if (sons[x].begin() == sons[x].end()) return;
    node son = *(sons[x].begin());
    son.val += people[x] / (sonsnum[x] + 2);
    all.erase(son);
    son = *(--sons[x].end());
    son.val += people[x] / (sonsnum[x] + 2);
    all.erase(son);
}
void destroy(int x) {
    sons[parent[x]].erase(node(x, sonssum[x]));
}
void update(int x) {
    sons[parent[x]].insert(node(x, sonssum[x]));
}
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++ i) {
        scanf("%lld", &people[i]);
    }
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &parent[i]);
        sonsnum[parent[i]] ++;
    }
    for (int i = 1; i <= n; ++ i) {
        ll sz = sonsnum[i];
        sonssum[i] += people[i] - people[i] / (sz + 2) * (sz + 1);
        sonssum[parent[i]] += people[i] / (sz + 2);
    }
    for (int i = 1; i <= n; ++ i) {
        sons[parent[i]].insert(node(i, sonssum[i]));
    }
    
    for (int i = 1; i <= n; ++ i) {
        ins(i);
    }
    
    while (q --) {
        int type, u, v;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d", &v, &u);
            int oldu = parent[v];
            
            // delete node from set all
            
            del(u);
            del(oldu);
            del(parent[u]);
            del(parent[oldu]);
            del(parent[parent[u]]);
            del(parent[parent[oldu]]);
            
            // destroy previous influence

            destroy(u);
            destroy(oldu);
            destroy(parent[u]);
            destroy(parent[oldu]);

            sonssum[u] -= people[u] - people[u] / (sonsnum[u] + 2) * (sonsnum[u] + 1);
            sonssum[oldu] -= people[v] / (sonsnum[v] + 2);
            sonssum[oldu] -= people[oldu] - people[oldu] / (sonsnum[oldu] + 2) * (sonsnum[oldu] + 1);
            sonssum[parent[u]] -= people[u] / (sonsnum[u] + 2);
            sonssum[parent[oldu]] -= people[oldu] / (sonsnum[oldu] + 2);
            
            // modify the parent of v

            parent[v] = u;
            sonsnum[u] ++;
            sonsnum[oldu] --;
            sons[u].insert(node(v, sonssum[v]));
            sons[oldu].erase(node(v, sonssum[v]));
            
            // recover the influnce

            sonssum[u] += people[v] / (sonsnum[v] + 2);
            sonssum[u] += people[u] - people[u] / (sonsnum[u] + 2) * (sonsnum[u] + 1);
            sonssum[oldu] += people[oldu] - people[oldu] / (sonsnum[oldu] + 2) * (sonsnum[oldu] + 1);
            sonssum[parent[u]] += people[u] / (sonsnum[u] + 2);
            sonssum[parent[oldu]] += people[oldu] / (sonsnum[oldu] + 2);
            
            update(u);
            update(oldu);
            update(parent[u]);
            update(parent[oldu]);
            
            // insert new node into set all
            
            ins(u);
            ins(oldu);
            ins(parent[u]);
            ins(parent[oldu]);
            ins(parent[parent[u]]);
            ins(parent[parent[oldu]]);
            
        } else if (type == 2) {
            int x;
            scanf("%d", &x);
            printf("%lld\n", sonssum[x] + people[parent[x]] / (sonsnum[parent[x]] + 2));
            
        }else {
            printf("%lld %lld\n", all.begin()->val, (--all.end())->val);
        }
    }
}
