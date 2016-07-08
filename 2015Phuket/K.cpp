#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-8;
const int maxn = 100 + 10;

int dcmp(double x) {
    if(fabs(x) <= eps) return 0;
    if(x > eps) return 1;
    return -1;
}

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) {
        x = _x;
        y = _y;
    }
    Point operator + (const Point &b) const {
        Point t = Point(x + b.x, y + b.y);
        return t;
    }
    Point operator - (const Point &b) const {
        Point t = Point(x - b.x, y - b.y);
        return t;
    }
    double operator ^ (const Point &b) const {
        double ans = x * b.y - y * b.x;
        return ans;
    }
    double operator * (const Point &b) const {
        double ans = x * b.x + y * b.y;
        return ans;
    }
    Point operator * (const double b) const {
        Point t = Point(b * x, b * y);
        return t;
    }
    Point operator / (const double b) const {
        Point t = Point(x / b, y / b);
        return t;
    }
    double mo() {
        return sqrt(x * x + y * y);
    }
    double mo2() {
        return x * x + y * y;
    } 
    void unit() {
        double t = mo();
        x /= t;
        y /= t;
    }
    bool operator == (const Point &b) const {
        return (dcmp(x - b.x) == 0 && dcmp(y - b.y) == 0);
    }
};

struct Circle{
    Point o;
    double r;
};
double dist(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
void getCircle(Point A, Point B, Circle C[], int &num) {
    double d = dist(A, B);
    Point BA = A - B;
    Point BAh1 = Point(BA.y, -BA.x), BAh2 = Point(-BA.y, BA.x);
    BA.unit();
    BAh1.unit();
    BAh2.unit();
    Point o1 = B + BA * (d / 2.0) + BAh1 * (d / 2.0 * tan(65.0 / 180.0 * pi));
    Point o2 = B + BA * (d / 2.0) + BAh2 * (d / 2.0 * tan(65.0 / 180.0 * pi));
    double  r = dist(o1, B);
    C[0].r = C[1].r = r;
    C[0].o = o1;
    C[1].o = o2;
    num = 2;
}
void getPoint(Circle a, Circle b, Point p[], int &num) {
    double d = dist(a.o, b.o);
    double co = (a.r * a.r + d * d - b.r * b.r) / (2.0 * a.r * d);
    double d1 = a.r * co, d2 = sqrt(a.r * a.r - d1 * d1);
    Point OO = b.o - a.o;
    OO.unit();
    Point OOh1 = Point(OO.y, -OO.x);
    OOh1.unit();
    p[0] = a.o + OO * d1 + OOh1 * d2;
    p[1] = a.o + OO * d1 - OOh1 * d2;
    num = 2;
}
Point A, B, C;
double V, th;
Point p[maxn];
int n;

void calcu(Point D) {
    double vyvx = 0;
    if(D == B) {
        Point BA = A - B;
        Point BC = C - B;
        double co = (BA * BC) / (BA.mo() * BC.mo());
        co = acos(co);
        if(dcmp(co - 50.  / 180. * pi) != 0) return;
        double vx, vy;
        BA.unit();
        BC.unit();
        vx = (BA + BC).x;
        vy = (BA + BC).y;
        if(dcmp(vx) <= 0) return;
        vyvx = vy / vx;
    } else {
        double vx, vy;
        vx = (B - D).x;
        vy = (B - D).y;
        if(dcmp(vx) <= 0) return;
        vyvx = vy / vx;
    } 
    double g = 9.8;
    double t = (D.x * D.x * g) / (2 * (D.y - vyvx * D.x));
    if(dcmp(t) <= 0) return;
    t = sqrt(t);
    double vx0 = t;
    double vy0 = vyvx * vx0 + g * (D.x / vx0);
    double tmpth = atan(vy0 / vx0);
    if(tmpth >= 10.0 / 180.0 * pi - eps && tmpth <= 80.0 / 180.0 * pi + eps) {
        double tmpV = sqrt(vx0 * vx0 + vy0 * vy0);
        if(tmpV >= 50.0 - eps && tmpV <= 5000.0 + eps) {
            if(tmpV < V) {
                V = tmpV;
                th = tmpth;
            }
        }
    }
}

void solve() {
    n = 0;
    Circle a[4];
    int an = 0;
    getCircle(A, B, a, an);
    
    Circle b[4];
    int bn = 0;
    getCircle(B, C, b, bn);
    for(int i = 0; i < an; i++) {
        for(int j = 0; j < bn; j++) {
            Point c[4];
            int cn;
            getPoint(a[i], b[j], c, cn);
            for(int k = 0; k < cn; k++) {
                Point AB = B - A;
                Point BC = B - C;
                Point OA = c[k] - A;
                Point OB = c[k] - B;
                Point OC = c[k] - C;
                if (OA.mo2() < eps || OC.mo2() < eps) continue;
                double cos1 = OA.mo2() + OB.mo2() - AB.mo2();
                double cos2 = OB.mo2() + OC.mo2() - BC.mo2();
                if (dcmp(cos1) < 0 || dcmp(cos2) < 0 ) {
                    continue;
                }
                if (dcmp((OB ^ OA) * (OB ^ OC)) >=0) {
                    continue;
                }
                p[n] = c[k];
                n++;
            }
        }
    } 
    for(int i = 0; i < n; i++) {
        calcu(p[i]);
    }
}

int main() {
    //freopen("K.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
        printf("Case %d: ", _);
        scanf("%lf%lf%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);
        th = 0;
        V = 1000000;
        solve();
        swap(A, B);
        solve();
        swap(B, C);
        solve();
        printf("%.6f\n", th / pi * 180.0);
    }
    return 0;
}
