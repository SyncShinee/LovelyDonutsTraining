#include <bits/stdc++.h>

using namespace std;
#define CLR(x) memset(x, 0, sizeof x)
const int N = 20;
int f[110];
int n, k, c, m;
int kw[N][N];
int a[110][N];
const int maxn = 20;
const int INF = 1e9;
int w[maxn][maxn];
int lx[maxn], ly[maxn];
int linky[maxn];
int visx[maxn], visy[maxn];
int slack[maxn];
int nx, ny;
int find(int x)
{
    visx[x] = 1;
    for (int y = 1; y <= ny; y++)
	{
	    if (visy[y])
		continue;
	    int t = lx[x] + ly[y] - w[x][y];
	    if (t == 0)
		{
		    visy[y] = 1;
		    if (linky[y] == -1 || find(linky[y]))
			{
			    linky[y] = x;
			    return 1;
			}
		}
	    else if (slack[y] > t)
		{
		    slack[y] = t;
		}
	}
    return 0;
}
int KM()
{
    memset(linky, -1, sizeof(linky));
    CLR(ly);
    for (int i = 1; i <= nx; i++)
	{
	    lx[i] = -INF;
	    for (int j = 0; j < ny; j++)
		{
		    if (w[i][j] > lx[i])
			{
			    lx[i] = w[i][j];
			}
		}
	}
    for (int x = 1; x <= nx; x++)
	{
	    for (int i = 1; i <= ny; i++)
		slack[i] = INF;
	    while (1)
		{
		    CLR(visx);
		    CLR(visy);
		    if (find(x))
			{
			    break;
			}
		    int d = INF;
		    for (int i = 1; i <= ny; i++)
			{
			    if (!visy[i] && d > slack[i])
				d = slack[i];
			}
		    for (int i = 1; i <= nx; i++)
			{
			    if (visx[i])
				lx[i] -= d;
			}
		    for (int i = 1; i <= ny; i++)
			{
			    if (visy[i])
				{
				    ly[i] += d;
				}
			    else
				{
				    slack[i] -= d;
				}
			}
		}
	}
    int res = 0;
    for (int i = 1; i <= ny; i++)
	{
	    if (linky[i] > -1)
		{
		    res += w[linky[i]][i];
		}
	}
    return res;
}
int g(int L, int R){
    for (int i = 1; i <= k; ++ i){
	for (int j = 1; j <= n; ++ j){
	    w[i][j] = -kw[i][j] * (a[R][i] - a[L - 1][i]);
	    //printf("%d%c", w[i][j], " \n"[j == n]);
	    if (kw[i][j] == -1 && a[R][i] != a[L - 1][i]) w[i][j] = -10000000;
	}
    }
    nx = k; ny = n;
    return -KM();
}
int q;
int main(){
    //  freopen("in.txt", "r", stdin);
    scanf("%d %d %d", &n, &k, &c);
    scanf("%d", &m);
    for (int i = 1; i <= 15; ++ i){
	for (int j = 1; j <= 15; ++ j){
	    kw[i][j] = -1;
	}
    }
    for (int i = 1; i <= m; ++ i){
	int u, v, z; scanf("%d %d %d", &u, &v, &z);
	if (kw[v][u] == -1) kw[v][u] = z;
	else
	    kw[v][u] = min(kw[v][u], z);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++ i){
	for (int j = 1; j <= k; ++ j){
	    scanf("%d", &a[i][j]);
	    a[i][j] += a[i - 1][j];
	}
    }
    for (int i = 1; i <= q; ++ i) f[i] = INF;
    for (int i = 1; i <= q; ++ i){
	for (int j = 0; j < i; ++ j){
	    f[i] = min(f[i], f[j] + g(j + 1, i) + c);
	}
    }
    printf("%d\n", f[q]);
}
