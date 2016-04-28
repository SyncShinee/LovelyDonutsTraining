#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const double eps = 1e-8;
const double Pi = acos(-1.0);

int a1, b1, a2, b2;



int calcu(double x) {
    double t1 = a1 * 1.0 * cos(x) + b1 * 1.0 * sin(x);
    double t2 = a1 * 1.0 * sin(x) + b1 * 1.0 * cos(x);
    if(t1 - eps < a2 && t2 - eps < b2)
	return 1;
    return 0;
}
int main() {
    freopen("A.txt", "r", stdin);
    scanf("%d%d%d%d", &a1, &b1, &a2, &b2);
    //printf("ttt\n");
    if (a1 * b1 > a2 * b2) {
	swap(a1, a2);
	swap(b1, b2);
    }
    int flag = 0;
    if (a1 <= a2 && b1 <= b2) {
	flag = 1;
    }
    else if (a1 <= b2 && b1 <= a2) {
	flag = 1;
    }
    else {
	//printf("5dfa\n");
	for(double x = 0; x < Pi / 2; x += (Pi / 2) / (1e6)) {
	    if(calcu(x) == 1) {
		flag = 1;
		break;
	    }
       }
    }
    if(flag) {
	printf("Yes\n");
    }
    else {
	printf("No\n");
    }
    return 0;
}
