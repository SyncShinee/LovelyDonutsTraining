#include <bits/stdc++.h>

using namespace std;
typedef pair <int, int> pii;
const int N = 1e5 + 10;
int n, m;
int E[N], c[N], s[N], pos[N];
vector <int> store[N];
int f[N], h[N];
int main(){
    while (~scanf("%d %d", &n, &m)){
        for (int i = 1; i <= n; ++ i) {
            store[i].clear();
            scanf("%d", &E[i]);
            s[i] = s[i - 1] + E[i];
        }
        for (int i = 1; i <= m; ++ i) {
            scanf("%d %d %d", &pos[i], &h[i], &c[i]);
            store[pos[i]].push_back(i);
        }
        set <pii> s1, s2;
        for (auto &p: store[1]){
            s1.insert(make_pair(c[p], p));
            s2.insert(make_pair(h[p], p));
        }
        f[n] = -1;
        for (int i = 1; i <= n; ++ i){
            while (s2.size() && s2.begin()->first < s[i]){
                int id = s2.begin()->second;
                s1.erase(make_pair(f[pos[id] - 1] + c[id], id));
                s2.erase(make_pair(s2.begin()->first, id));
            }
            if (s1.size()) f[i] = s1.begin()->first;
            else
                break;
            for (auto &p : store[i + 1]){
                s1.insert(make_pair(f[i] + c[p], p));
                s2.insert(make_pair(h[p] + s[i], p));
            }
        }
        printf("%d\n", f[n]);
    }
}
