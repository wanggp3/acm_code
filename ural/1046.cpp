// label : geometry, math
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

const int N = 55;
const int M = N * 2 + 1;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

int n;
double alg[N];
Point v[N];

double p[M][M];

void gauss(int n, int m, double p[M][M]){
	static double tmp[M][M];
    static double *b[M];
	rep(i, n){
		rep(j, m){
			tmp[i][j] = p[i][j];
		}
	}
    rep(i, n) b[i] = tmp[i];
    rep(i, n){
        REP(j, i, n){
            if (sign(fabs(b[j][i]) - fabs(b[i][i])) > 0) swap(b[i], b[j]);
        }
        rep(j, n){
            if (i == j) continue;
            double rate = b[j][i] / b[i][i];
            rep(k, m) b[j][k] -= b[i][k] * rate;
        }
        double rate = b[i][i];
        rep(j, m) b[i][j] /= rate;
    }
    rep(i, n){
		rep(j, m){
			p[i][j] = b[i][j];
		}
	}
}

int main(){
	while(~scanf("%d", &n)){
		rep(i, n){
			double x, y;
			scanf("%lf%lf", &x, &y);
			v[i] = Point(x, y);
		}
		rep(i, n){
			scanf("%lf", &alg[i]);
			alg[i] = alg[i] / 180 * PI;
		}
		int r = 2 * n, c = 2 * n + 1;
		rep(i, r){
			rep(j, c){
				p[i][j] = 0;
			}
		}
		rep(i, n){
			int id = 2 * i, x = 2 * i, y = 2 * i + 1, xx = 2 * ((i + 1) % n), yy = 2 * ((i + 1) % n) + 1;
			double co = cos(alg[i]), si = sin(alg[i]);
			p[id][x] = co;
			p[id][y] = -si;
			p[id][xx] = -1;
			p[id][c - 1] = v[i].X * co - v[i].Y * si - v[i].X;

			id++;
			p[id][x] = si;
			p[id][y] = co;
			p[id][yy] = -1;
			p[id][c - 1] = v[i].X * si + v[i].Y * co - v[i].Y;
		}
		gauss(r, c, p);
		rep(i, n){
			printf("%.2f %.2f\n", p[2 * i][c - 1], p[2 * i + 1][c - 1]);
		}
	}
	return 0;
}
