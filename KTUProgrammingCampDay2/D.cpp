#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int maxn = 2e5 + 100;

struct node{
    int val, id;
    node(int _val = 0, int _id = 0) {
	val = _val;
	id = _id;
    }
    
};
int cmp(node a, node b) {
    return a.val < b.val;
}
node a[maxn];
int n;
queue<int> q;
vector<int> aa, b;
int solve() {
    while(!q.empty()) {
	q.pop();
    }
    aa.clear();
    b.clear();
    sort(a + 1, a + 1 + n, cmp);
    int key = -1;
    for(int i = 1; i <= n; i++) {
	if(a[i].val == 1) {
	    q.push(a[i].id);
	    key = i;
	}
    }
    key++;
    for(int i = n; i >= key; i--) {
	if(a[i].val == 1) {
	    q.push(a[i].id);
	}
	else {
	    if(i == key) {
		if(q.size() != a[i].val) {
		    return 0;
		}
		while(!q.empty()) {
		    int t = q.front();
		    aa.push_back(a[i].id);
		    b.push_back(t);
		    q.pop();
		}
		return 1;
	    }
	    else {
		if(q.size() < a[i].va- 1) {
		    return 0;
		}
		for(int j = 1; j <= a[i].val - 1; j++) {
		    int t = q.front();
		    aa.push_back(t);
		    b.push_back(a[i].id);
		    q.pop();
		}
		q.push(a[i].id);
	    }
	}
    }
}

int main() {
    freopen("D.txt", "r", stdin);
    while(scanf("%d", &n) != EOF) {
	for(int i = 1; i <= n; i++) {
	    scanf("%d", &a[i].val);
	    a[i].id = i;
	}
	if(solve()) {
	    for(int i = 0; i < aa.size(); i++) {
		printf("%d %d\n", aa[i], b[i]);
	    }
	    
	}
	else {
	    printf("-1\n");
	}
    }
    return 0;
}
