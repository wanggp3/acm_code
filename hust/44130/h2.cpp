//label : unfinished
//By myf
//#pragma comment(linker, "/STACK:16777216")  //C++
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <bitset>
#include <stack>
#include <complex>
#include <list>
#include <iomanip>

#define rep(i, n) for(int i = 0; i < (n); i++)
#define REP(i, l, r) for(int i = (l) ; i < (r); i++)
#define MP make_pair
#define PB push_back
#define Cls(x) memset(x,0,sizeof x)
#define Print(n,x) for(int i=0;i<(n);i++) cout<<x<<" ";cout<<endl;
#define foreach(i,n) for(__typeof(n.begin()) i=n.begin();i!=n.end();i++) //G++
#define F first
#define S second
#define X real()
#define Y imag()
#define Sqr(x) (x)*(x)
#define sign(x) ((x < -EPS) ? -1 : x > EPS)

using namespace std;

typedef long long LL;
typedef complex<double> Point;
typedef Point Vec;
typedef pair<Point, Point> Line;
//typedef complex<double> Comp;

const int N = 1000000;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

struct Point3{
	double x, y, z;
	Point3(){}
	Point3(double x, double y, double z) : x(x), y(y), z(z) {}
};

Point3 operator +(Point3 a, Point3 b){
	return Point3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point3 operator -(Point3 a, Point3 b){
	return Point3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point3 operator *(Point3 a, double p){
	return Point3(a.x * p, a.y * p, a.z * p);
}

Point3 operator /(Point3 a, double p){
	return Point3(a.x / p, a.y / p, a.z / p);
}

double dot(Point3 a, Point3 b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

double len2(Point3 a){
	return dot(a, a);
}

double len(Point3 a){
	return sqrt(dot(a, a));
}

Point3 unit(Point3 v){
	return v / len(v);
}

struct Circle{
	Point o;
	double r;
	Circle(Point o = Point(), double r = 1) : o(o), r(r){}
	Circle(double x, double y, double r = 1) : o(x, y), r(r){}
};

Circle a0, b0;

int ip_circle_circle(const Circle &c1, const Circle &c2, Point &p1, Point &p2){
	double mx = c2.o.X - c1.o.X, sx = c2.o.X + c1.o.X, mx2 = Sqr(mx);
	double my = c2.o.Y - c1.o.Y, sy = c2.o.Y + c1.o.Y, my2 = Sqr(my);
	double sq = mx2 + my2, d = -(sq - Sqr(c1.r - c2.r)) * (sq - Sqr(c1.r + c2.r));
	if (!sign(sq)) return 0;
	if (d + EPS < 0) return 0;
	if (d < EPS){
		d = 0;
	}
	else{
		d = sqrt(d);
	}
	double x = mx * ((c1.r + c2.r) * (c1.r - c2.r) + mx * sx) + sx * my2;
	double y = my * ((c1.r + c2.r) * (c1.r - c2.r) + my * sy) + sy * mx2;
	double dx = mx * d, dy = my * d;
	sq *= 2;
	p1.X = (x + dy) / sq; p1.Y = (y - dx) / sq;
	p2.X = (x - dy) / sq; p2.Y = (y + dy) / sq;
	return d > EPS ? 2 : 1; 
}

void rotate(Point &v, double alpha){
	double c = cos(alpha), s = sin(alpha);
	v = Point(v.X * c - v.Y * s, v.X * s + v.Y * c);
}

double h, d, alpha;
double l, r;
vector<Point3> p;
Point3 st, ed, now, f;

int main(){
	while(~scanf("%lf%lf%lf", &h, &d, &alpha)){
		 l = h / cos(alpha / 2);
		 r = l * sin(alpha / 2);
		 p.clear();
		 st = Point3(0, 0, h);
		 ed = Point3(0, r, 0);
		 f = unit((ed - st));
		 now = st;
		 a0.o = Point(0, 0), b0.o = Point(l, 0);
		 a0.r = d, b0.r = d;
		 while(sign(len(ed - now) - 2 * d) > 0){
			 a0.o += Point(d, 0);
			 now = now + f * d;
			 p.PB(now);
		 }
		 Point p1, p2;
		 ip_circle_circle(a0, b0, p1, p2);
		 double z = (l - abs(p1)) * cos(alpha / 2);
		 double len = abs(p1 - (a0.o + b0.o) / 2.0);
		 double tmp_r = (h - z) * tan(alpha / 2.0);
		 double tmp_alpha = len / tmp_r;
		 Point tmp_point = Point(0, tmp_r);
		 rotate(tmp_point, tmp_alpha);
		 p.PB(Point3(tmp_point.X, tmp_point.Y, z));
		 p.PB(ed);
		 printf("%d\n", p.size());
		 rep(i, p.size()){
			 printf("%.6f %.6f %.6f\n", p[i].x, p[i].y, p[i].z);
		 }
	}
	return 0;
}
