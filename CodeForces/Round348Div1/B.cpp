#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
deque <int> V;
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    int total = 0, flag = 0, rec = 0;
    for (int i = 1; i <= n; ++ i) {
        V.push_back(i);
    }
    while (q --) {
        int tp, x;
        scanf("%d", &tp);
        if (tp == 1) {
            scanf("%d", &x);
            if (x & 1) {
                total = (total + x + 1) % n;
                rec ++;
            } else {
                total = (total + x) % n;
            }
        } else {
            if ((total + rec) & 1) {
                rec ++;
                int t = V[n - 1];
                V.pop_back();
                V.push_front(t);
            }
            flag ^= 1;
        }
        /*
          for (int i = 0; i < n; ++ i) {
          printf("%d%c", V[i], " \n"[i == n - 1]);
        
          }
        */
    }
    total = (total + n) % n;
    while (total) {
        int t = V[n - 1];
        V.pop_back();
        V.push_front(t);
        total --;
    }
    if (flag) {
        for (int i = 0; i < n; i += 2) {
            swap(V[i], V[i + 1]);
        }
    }
    rec = (rec + n) % n;
    while (rec) {
        int t = V[0];
        V.pop_front();
        V.push_back(t);
        rec --;
    }
    for (int i = 0; i < n; ++ i) {
        printf("%d%c", V[i], " \n"[i == n - 1]);
        
    }
    return 0;
}
