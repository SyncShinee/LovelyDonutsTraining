#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[8];
int main() {
    printf("1\n");
    fflush(stdout);
    scanf("%s", s);
    if (s[0] == 'y') {
	return 0;
    }
    for (int i = 2; i <= 30000; ++ i) {
	printf("%d\n", i);
	fflush(stdout);
	scanf("%s", s);
	if (s[0] == 'n') {
	    continue;
	}
	else {
	    printf("1\n");
	    fflush(stdout);
	    scanf("%s", s);
	    if (s[0] == 'n') {
		continue;
	    }
	    else break;
	}
    }
    return 0;
}
