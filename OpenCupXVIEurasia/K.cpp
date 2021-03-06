#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

int n, S;
map<int, int> mp;
int a[100010], len;
int main() {
    int x, y;
    scanf("%d%d", &n, &S);
    for (int i = 0; i < n; ++ i) {
	scanf("%d%d", &x, &y);
	if (mp.find(x) == mp.end()) {
	    mp[x] = y;
	}
	else {
	    mp[x] = min(mp[x], y);
	}
    }
    len = 0;
    for (map<int, int> ::iterator it = mp.begin(); it != mp.end(); it++) {
	a[len++] = (*it).second;
    }
    sort(a, a + len);
    int ans = 0;
    for (int i = 0; i < len; ++ i) {
	if (S - a[i] >= 0) {
	    ans++;
	    S -= a[i];
	}
	else {
	    break;
	}
    }
    printf("%d\n", ans);
    return 0;
}
