//by myf
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <complex>

using namespace std;

#define foreach(it,s) for (__typeof(s.begin()) it = s.begin(); it != s.end(); ++it)
#define rep(i, n) for(int i = 0; i < n; i++)
#define REP(i, l, r) for(int i = (l); i < (r); i++)
#define MP make_pair
#define PB push_back
#define X real()
#define Y imag()
#define Cls(x) memset(x, 0, sizeof x)
#define sign(x) ((x < -EPS) ? -1 : x > EPS)

typedef long long LL;
typedef complex<double> Point;

const int MAX_N = 100001;
const int N = 23333;
const double INF = 1E18;
const double EPS = 1e-8;
const double PI = acos(-1.0);
const double pi = PI;

double cross(Point a, Point b){
    return a.X * b.Y - a.Y * b.X;
}

double cross(Point a, Point b, Point c){
    return cross(b - a, c - a);
}

double fix(double a, double b = 0) {
  a -= b;
  if (sign(a) < 0) a += 2 * pi;
  if (sign(a - 2 * pi) >= 0) a -= 2 * pi;
  return a;
}

double angle(Point a, Point b){
    return fix(arg(b - a));
}

Point o;

bool cmp_p(Point a, Point b){
    int f = sign(a.X - b.X);
    if (f) return f < 0;
    return sign(a.Y - b.Y) < 0;
}

bool cmp(Point a, Point b){
    int f = sign(cross(o, a, b));
    if (f) return f > 0;
    return sign(abs(a - o) - abs(b - o)) < 0;
}

Point stack[N];

int find_convex(Point p[], int n){
    o = *min_element(p, p + n, cmp_p);
    sort(p, p + n, cmp);
    int top = 0;
    rep(i, n){
        while(top >= 2 && sign(cross(stack[top - 2], stack[top - 1], p[i])) <= 0) top--;
        stack[top++] = p[i];
    }
    rep(i, top) p[i] = stack[i];
    return top;
}

double shadow_length(double alpha, Point a, Point b){
    double dx = a.X - b.X;
    double dy = a.Y - b.Y;
    double c = cos(alpha);
    double s = sin(alpha);
    return fabs(dx * c + dy * s);
}

void rotate_calipers(Point ps[], int n, double &area, double &peri){
    area = peri = INF;
    n = find_convex(ps, n);
    ps[n] = ps[0];
    Point *q[4] = {NULL, NULL, NULL, NULL};
    for(int i = 0; i < n; i++){
        Point *p = &ps[i];
        if (!q[0] || q[0]->Y > p->Y || q[0]->Y == p->Y && q[0]->X > p->X) q[0] = p;
        if (!q[1] || q[1]->X < p->X || q[1]->X == p->X && q[1]->Y > p->Y) q[1] = p;
        if (!q[2] || q[2]->Y < p->Y || q[2]->Y == p->Y && q[2]->X < p->X) q[2] = p;
        if (!q[3] || q[3]->X > p->X || q[3]->X == p->X && q[3]->Y < p->Y) q[3] = p;
    }
    double alpha = 0;
    for(int k = 0; k < n + 5; k++){
        int bi = -1;
        double gap_min = INF;
        for(int i = 0; i < 4; i++){
            double gap = fix(angle(q[i][0], q[i][1]), alpha + i * PI / 2);
            if (gap < gap_min){
                gap_min = gap;
                bi = i;
            }
        }
        if (++q[bi] == ps + n) q[bi] = ps + 0;
        alpha = fix(alpha + gap_min);
        double a = shadow_length(alpha + PI / 2, *q[0], *q[2]);
        double b = shadow_length(alpha, *q[1], *q[3]);
        area = min(area, a * b);
        peri = min(peri, a + a + b + b);
    }
}

int n;
Point p[N];

int main(){
    while(~scanf("%d", &n)){
        if (!n) break;
        rep(i, n){
            double x, y;
            scanf("%lf%lf", &x, &y);
            p[i] = Point(x, y);
        }
        p[n] = p[0];
        double area, peri;
        rotate_calipers(p, n, area, peri);
        printf("%.6f\n", peri);
    }
    return 0;
}
