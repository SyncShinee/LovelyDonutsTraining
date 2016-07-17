#include <bits/stdc++.h>
using namespace std;
int main() {
    int n = 38;
    printf("%d\n", n * 5 + 2);
    printf("vv<<<^^^>>");
    
    for (int i = 10; i < n * 5 + 2; i += 2) {
        printf("v^");
    }
    puts("");
    
    for (int i = 0; i < n * 5 + 2; ++ i) printf("#");
    puts("");

    printf("##");
    for (int i = 0; i < n; ++ i) {
        printf(".####");
    }
    puts("");

    printf("##");
    for (int i = 0; i < n; ++ i) {
        printf("....#");
    }
    puts("");

    for (int i = 3; i < (n - 1) * 5 + 2; ++ i) {
        if (i & 1) {
            for (int j = 0; j < n; ++ j) {
                printf("#..#.");
            }
            puts("##");
        } else {
            for (int j = 0; j < n; ++ j) {
                printf("##.#.");
            }
            puts("##");
        }
    }
    
    printf("#");
    for (int i = 0; i < n; ++ i) {
        printf("..#..");
    }
    puts("#");

    printf("##.");
    for (int i = 0; i <= (n - 1) * 5; ++ i) {
        printf("#");
    }
    puts(".##");

    printf("#..");
    for (int i = 0; i <= (n - 1) * 5; ++ i) {
        printf(".");
    }
    puts("R##");

    printf("##");
    for (int i = 0; i < n * 5 / 2 - 1; ++ i) {
        printf("#.");
    }
    puts("##");

    for (int i = 0; i < n * 5 + 2; ++ i) printf("#");
    puts("");
    return 0;
}
