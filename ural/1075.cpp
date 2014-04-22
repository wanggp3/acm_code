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
	void read(){
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	void print(){
		printf("(%lf,%lf,%lf)\n", x, y, z);
	}
};
typedef Point3 Vector3;

struct Line{
	Point3 p, q;
	Line(){}
	Line(Point3 p, Point3 q) : p(p), q(q) {}
};

Point3 operator + (const Point3 &a, const Point3 &b){
	return Point3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point3 operator - (const Point3 &a, const Point3 &b){
	return Point3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point3 operator * (const Point3 &a, const double &p){
	return Point3(a.x * p, a.y * p, a.z * p);
}

Point3 operator * (const double &p, const Point3 &a){
	return Point3(a.x * p, a.y * p, a.z * p);
}

Point3 operator / (const Point3 &a, const double &p){
	return Point3(a.x / p, a.y / p, a.z / p);
}

double operator^(Vector3 a, Vector3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double len2(Vector3 a){
    return a ^ a;
}

double len(Vector3 a){
    return sqrt(a ^ a);
}

Point3 cross(const Point3 &a, const Point3 &b){
	return Point3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Point3 cross(Point3 a, Point3 b, Point3 c){
	return cross(b - a, c - a);
}

double r;
Point3 a, b, c;

Point3 project(Line l, Point3 a){
    double t = ((l.q - l.p) ^ (a - l.p)) / ((l.q - l.p) ^ (l.q - l.p));
    return l.p + t * (l.q - l.p);
}

int ip_ball_line(Point3 o, double r, Line l, Point3 &p, Point3 &q, Point3 &d){
    Vector3 v;
    d = project(l, o);
    if (len2(o - d) > r * r) return 0;
    v = sqrt((r * r - len2(o - d)) / len2(l.q - l.p)) * (l.p - l.q);
    p = d + v;
    q = d - v;
    return 1;
}

int main(){
	a.read();
	b.read();
	c.read();
	scanf("%lf", &r);
	Point3 v = b - a;
	double dis = fabs(len(cross(c, a, b))) / len(b - a);
	if (sign(dis - r) >= 0){
		printf("%.2f\n", len(v));
	}
	else{
		Point3 p, q, ret;
		int flag = ip_ball_line(c, r, Line(a, b), p, q, ret);
		Point3 tmp = ret - c;
		tmp = tmp / len(tmp);
		ret = c + tmp * r;
		ret.print();
		cout << len(ret - c) << endl;
		cout << len(ret - a) + len(ret - b) << endl;
		//double dis = len(p - q);
		//double real_dis = 2 * asin(dis / 2 / r) * r;
		//cout << len(v) << endl;
	}
	return 0;
}
