#include <bits/stdc++.h>
using namespace std;
const int N = 450;
struct node {
    int x, y;
    node(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};
vector <node> line;
vector <node> point;
bool cmp1(const node &A, const node &B) {
    if (A.y * B.x == B.y * A.x){
        if (A.y != B.y) return A.y < B.y;
        return A.x < B.x;
    }
    return A.y * B.x > B.y * A.x;
}
bool cmp2(const node &A, const node &B) {
    return A.y * B.x == B.y * A.x;
}
bool cmp3(const node &A, const node &B) {
    return A.x < B.x;
}
long long cross(node A, node B, node C) {
    return 1ll * (B.x - A.x) * (C.y - A.y) - 1ll * (B.y - A.y) * (C.x - A.x);
}
int main() {
    int n;
    for (int i = 1; i < N; i ++) {
        for (int j = i + 1; j < N; j ++) {
            line.push_back(node(i, j));
        }
    }
    
    sort(line.begin(), line.end(), cmp1);
    line.erase(unique(line.begin(), line.end(), cmp2), line.end());
    sort(line.begin(), line.end(), cmp3);
    line.erase(line.begin() + 50002, line.end());
    sort(line.begin(), line.end(), cmp1);
    /*
      long long x = 0, y = 0;
      for (int i = 0; i < line.size() && i <= 50000; ++ i) {
      x += line[i].x, y += line[i].y;
      }
    */
    //printf("%d %lld %lld\n", (int)line.size(), x, y);
    while (~scanf("%d", &n)) {
        point.clear();
        int remain = n % 8;
        n += (8 - remain) % 8;
        int num = n / 8;
        num --;
        int nx = 0, ny = 2e7 + 0.1;
        point.push_back(node(nx, ny));
        for (int i = 0; i < num; ++ i) {
            nx += line[i].x, ny += line[i].y;
            point.push_back(node(nx, ny));
        }
        //  printf("-------%d %d\n", point[1].x, point[1].y);
        nx += 1, ny += 1;
        point.push_back(node(nx, ny));
        for (int i = num - 1; i >= 0; -- i) {
            nx += line[i].y, ny += line[i].x;
            point.push_back(node(nx, ny));
        }
        nx ++;
        point.push_back(node(nx, ny));
        for (int i = 0; i < num; ++ i) {
            nx += line[i].y, ny -= line[i].x;
            point.push_back(node(nx, ny));
        }
        nx += 1, ny -= 1;
        point.push_back(node(nx, ny));
        for (int i = num - 1; i >= 0; -- i) {
            nx += line[i].x, ny -= line[i].y;
            point.push_back(node(nx, ny));
        }
        ny --;
        point.push_back(node(nx, ny));
        for (int i = 0; i < num; ++ i) {
            nx -= line[i].x, ny -= line[i].y;
            point.push_back(node(nx, ny));
        }
        nx --, ny --;
        point.push_back(node(nx, ny));
        for (int i = num - 1; i >= 0; -- i) {
            nx -= line[i].y, ny -= line[i].x;
            point.push_back(node(nx, ny));
        }
        nx --;
        point.push_back(node(nx, ny));
        for (int i = 0; i < num; ++ i) {
            nx -= line[i].y, ny += line[i].x;
            point.push_back(node(nx, ny));
        }
        nx --, ny ++;
        point.push_back(node(nx, ny));
        for (int i = num - 1; i >= 0; -- i) {
            nx -= line[i].x, ny += line[i].y;
            point.push_back(node(nx, ny));
        }
        point.erase(point.end() - (8 - remain) % 8, point.end());
        
        for (int i = 0; i < point.size(); ++ i) {
            printf("%d %d\n", point[i].x, point[i].y);
        }
        
    }
    return 0;
}
