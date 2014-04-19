//label : math
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
const double EPS = 1E-12;

int T;
int n;
Point v[N];

double get(double x){
	Point p = Point(x, 0);
	double ret = 0;
	rep(i, n){
		ret += sqrt(Sqr(x - v[i].X) + Sqr(v[i].Y));
	}
	return ret;
}

int main(){
	scanf("%d", &T);
	rep(cas, T){
		scanf("%d", &n);
		rep(i, n){
			double x, y;
			scanf("%lf%lf", &x, &y);
			v[i] = Point(x, y);
		}
		double l = -1E6, r = 1E6;
		while(r - l > 1E-7){
			double ll = l + (r - l) / 3.0;
			double rr = r - (r - l) / 3.0;
			double ans_l = get(ll), ans_r = get(rr);
			if (sign(ans_l - ans_r) > 0){
				l = ll;
			}
			else{
				r = rr;
			}
		}
		printf("Case %d: %.12lf\n", cas + 1, l);
	}
	return 0;
}
