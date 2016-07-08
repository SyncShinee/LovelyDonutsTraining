#include <bits/stdc++.h>

using namespace std;
int n;
int num[4];
int main(){
    int t; scanf("%d", &t);
    while (t--){
        memset(num, 0, sizeof num);
        scanf("%d", &n);
        for (int i = 1; i <= n; ++ i){
            char s[4]; scanf("%s", s);
            if (s[0] == 'a' && s[1] == 'a') num[0]++;
            if (s[0] == 'a' && s[1] == 'b') num[1]++;
            if (s[0] == 'b' && s[1] == 'a') num[2]++;
            if (s[0] == 'b' && s[1] == 'b') num[3]++;
        }
        int m = min(num[1], num[2]);
        for (int i = 1; i <= num[0]/2; ++ i) printf("aa");
        for (int i = 1; i <= m; ++ i) printf("ab");
        for (int i = 1; i <= num[3]/2; ++ i) printf("bb");
        if (num[0] & 1) printf("aa");
        else if (num[3] & 1) printf("bb"); 
        for (int i = 1; i <= num[3]/2; ++ i) printf("bb");
        for (int i = 1; i <= m; ++ i) printf("ba");
        for (int i = 1; i <= num[0]/2; ++ i) printf("aa");
        puts("");
    }
}
