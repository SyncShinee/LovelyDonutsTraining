#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int Gra[16][16];
int color[128][2];
int letter[40] = {0, 1, 3, 2, 3, 2, 1, 5, 5,
		  1, 2, 2, 2, 2, 1, 1, 2,
		  2, 2, 2, 3, 10, 5, 10, 5,
		  10, 10, 10, 5, 5, 10, 10, 3
                  };
int ans[8];
bool flag[16][16];
int main() {
    //freopen("input001.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int n, w, num, tot, x, y, xx, dx, dy;
    char ch;
    color['w'][0] = color['w'][1] = color['s'][0] = color['s'][1] = 1;
    color['g'][0] = color['b'][1] = 2;
    color['g'][1] = color['b'][0] = color['r'][0] = color['y'][1] = 1;
    color['y'][0] = color['r'][1] = 3;
    for (int i = 1; i < 16; ++ i) {
	for (int j = i; j < 16; ++ j) {
	    Gra[i][j] = 'w';
	}
    }
    Gra[1][1] = Gra[1][15] = Gra[15][1] = Gra[15][15] = 'r';
    Gra[8][1] = Gra[1][8] = Gra[8][15] = Gra[15][8] = 'r';
    Gra[1][4] = Gra[1][12] = 'g';
    Gra[2][6] = Gra[2][10] = 'y';
    Gra[3][7] = Gra[3][9] = Gra[4][8] = Gra[4][15]= 'g';
    Gra[6][14] = Gra[10][14] = 'y';
    Gra[7][9] = Gra[7][13] = Gra[8][12] = Gra[9][13] = 'g';
    Gra[12][15] = Gra[7][7] = Gra[9][9] = 'g';
    Gra[8][8] = 's';
    for (int i = 2; i < 6; ++ i) {
	Gra[i][i] = Gra[16 - i][16 - i] = Gra[i][16 - i] = Gra[16 - i][i] = 'b';
    }
    for (int i = 1; i < 16; ++ i) {
	for (int j = 1; j < i; ++ j) {
	    Gra[i][j] = Gra[j][i];
	}
    }
    
    scanf("%d%d", &n, &w);
    for (int i = 0; i < w; ++ i) {
	int nw = i % n;
	int sum = 0;
	scanf("%d", &num);
	for (int j = 0; j < num; ++ j) {
	    scanf("%d %c", &tot, &ch);
	    scanf("%d%d", &y, &x);
	    if (ch == 'h') {
		dx = 0, dy = 1;
	    }
	    else {
		dx = 1, dy = 0;
	    }
	    int tmp = 0, xx, tmp1 = 1;
	    //printf("%d------------------------\n", nw);
	    for (int i = 0; i < tot; ++ i) {
		if (!flag[x][y]) {
		    flag[x][y] = true;
		    sum++;
		}
		scanf("%d", &xx);
		//printf("%d %d\n", x, y);
		tmp += color[Gra[x][y]][0] * letter[xx];
		tmp1 *= color[Gra[x][y]][1];
		x += dx;
		y += dy;
	    }
	    //printf("sum of letter %d product of word %d\n", tmp, tmp1);
	    ans[nw] += tmp * tmp1;
	}
	if (sum == 7) ans[nw] += 15;
    }
    for (int i = 0; i < n; ++ i) {
	printf("%d\n", ans[i]);
    }
    return 0;
}
