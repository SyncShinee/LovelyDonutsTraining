#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, x0, y0, a, b;
    scanf("%d%d%d", &n, &x0, &y0);
    while (n --) {
	scanf("%d%d", &a, &b);
	printf("%d %d\n", a + b - y0, x0 + y0 - a);
    }
    return 0;
}
