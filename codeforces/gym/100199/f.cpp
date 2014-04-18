//label : geometry
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

const int N = 555;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

struct Circle{
	Point o;
	double r;
	void read(){
		double x, y;
		scanf("%lf%lf%lf", &x, &y, &r);
		o = Point(x, y);
	}
};

int n;
Circle c[N], o;
double dist[N][N], graph[N][N];

double cross(Point a, Point b){
	return a.X * b.Y - a.Y * b.X;
}

double cross(Point a, Point b, Point c){
	return cross(b - a, c - a);
}

int main(){
	freopen("out.in", "r", stdin);
	freopen("out.out", "w", stdout);
	while(~scanf("%d", &n)){
		rep(i, n){
			c[i].read();
		}
		o.read();
		rep(i, n){
			rep(j, n){
				dist[i][j] = INF;
				if (i == j) continue;
				//cout << i << ' ' << j << ' ' << sign(cross(o.o, c[i].o, c[j].o)) << endl;
				if (sign(abs(c[i].o - c[j].o) - c[i].r - c[j].r - 2 * o.r) < 0){
					dist[i][j] = asin(cross(o.o, c[i].o, c[j].o) / abs(c[i].o - o.o) / abs(c[j].o - o.o));
				//	cout << i << ' ' << j << ' ' << dist[i][j] << endl;
				}
			}
		}
		rep(i, n){
			rep(j, n){
				graph[i][j] = dist[i][j];
			}
		}
		double ret = INF;
		rep(k, n){
			rep(i, k){
				rep(j, k){
					if (i == j) continue;
					if (sign(dist[i][k] + dist[k][j] + graph[j][i] - ret) < 0){
						ret = dist[i][k] + dist[k][j] + graph[j][i];
					}
				}
			}
			rep(i, n){
				rep(j, n){
					if (sign(graph[i][k] + graph[k][j] - graph[i][j]) < 0){
						graph[i][j] = graph[i][k] + graph[k][j];
					}
				}
			}
		}
		if (sign(ret) < 0){
			puts("NO");
		}
		else{
			puts("YES");
		}
	}
	return 0;
}
