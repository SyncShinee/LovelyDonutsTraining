#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    freopen("hamilton-clique.in", "r", stdin);
    freopen("hamilton-clique.out", "w", stdout);
    int n;
    vector <int> a;
    scanf("%d", &n);
    for (int i = 2; i <= n; ++ i) {
	a.push_back(i);
    }
    puts("Yes");
    for (int i = 0; i < (n / 2); ++ i) {
	printf("1");
	for (int j = 0;j < n / 2; ++ j) {
	    printf(" %d %d", a[j], a[n - j - 2]);
	}
	puts("");
	rotate(a.begin(), a.begin() + 1, a.end());
    }
    
    return 0;
}
