#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const ll M = 1e9 + 0.1;
int main() {
    int n;
    scanf("%d", &n);
    ll N = n;
    int ans = 1;
    if (n < 5) {
	puts("-1");
	return 0;
    }
    ll t = N / 2;
    while (t * (N - t) < M) {
	N = t * (N - t);
	t = N / 2;
	ans ++;
    }
    printf("%d\n", ans);
    return 0;
}
