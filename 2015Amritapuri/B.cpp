#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 1000;
const double Pi = acos(-1.0);
const double PI = Pi;

int dx[] = {0, -1, -1, 0};
int dy[] = {0, 0, -1, -1};

map<pair<int, int>, int> mp;
int n, m, c, a;
double S[10];

void calcu(int x, int y, int pos) {
    if(x >= 0 && x + 1 <= n && y >= 0 && y + 1 <= m) {
        mp[make_pair(x, y)] |= (1 << pos);
    }
}

void add(int x, int y) {
    calcu(x, y, 0);
    calcu(x, y - 1, 3);
    calcu(x - 1, y - 1, 2);
    calcu(x - 1, y, 1);
}
void insert(int x, int y, int pos) {
    mp[make_pair(x, y)] |= (1 << pos);
}


double calc(int x, int n) {
    if (x < 0 || x >= n) return 0;
    int l = max(a, x + 1);
    int r = min(n, x + a);
    if (l > r) return 0;
    return r - l + 1;
}

double area(int sta) {
    int tmp = 0;
    for (int i = 0; i < 4; ++ i) {
        if (sta & (1 << i)) {
            ++ tmp;
            if (i - 2 >= 0) {
                if (sta & (1 << (i - 2))) {
                    return 1.;
                }
            }
        }
    }
    return S[tmp == 2];
}


int main() {
    freopen("B.txt", "r", stdin);
    int x, y;
    S[0] = PI / 4.;
    S[1] = PI / 6. + sqrt(3.) / 4.;
    while(scanf("%d%d%d%d", &n, &m, &tot, &a) != EOF) {
        mp.clear();
         for (int i = 0; i < tot; ++ i) {
            scanf("%d%d", &x, &y);
            for (int j = 0; j < 4; ++ j) {
                insert(x + dx[j], y + dy[j], j);
            }
        }
        double ans = 0.;
        for (auto node : mp) {
            int x, y;
            x = node.first.first;
            y = node.first.second;
            int sta = node.second;
            ans += calc(x, n) * calc(y, m) * area(sta);
        }
        printf("%.8f\n", ans / (n - a + 1) / (m - a + 1));
    }
    return 0;
}
