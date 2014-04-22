//label : unfinished
//By myf
//#pragma comment(linker, "/STACK:16777216")  //C++
#include <cstdio>
#include <assert.h>
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

const int N = 3600;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-12;

Point unit(Point v){
	return v / abs(v);
}

int n;
double h, d, alpha;
double l, r;
vector<Point> p;
Point st, ed, now, f;
bool ok;

int main(){
	while(~scanf("%lf%lf%lf", &h, &d, &alpha)){
		ok = false;
		p.clear();

		while(sign(n * d - h) < 0) n++;
		double tot_len = n * d;

		r = h * tan(alpha / 2.0);
		l = h / cos(alpha / 2.0);

		double now_alpha = 0;
		double delta = alpha / 2 / N;
		int cnt = 0;

		ok = false;
		rep(i, N - 1){
			p.clear();
			st = Point(0, h);
			if (cnt == 0){
				ed = Point(0, 0);
			}
			else{
				ed = Point(h * tan(now_alpha), 0);
			}
			cnt++;
			now_alpha += delta;
			f = unit(ed - st);
			int tim = -1;
			for(int i = 0; i <= n; i++){
				now = st + f * (double)i * d;
				double tmp_len = (n - i) * d;
				double y = now.X - sqrt(Sqr(tmp_len) - Sqr(now.Y));
				if (sign(y - r) > 0){
					continue;
				}
				tim = i;
				break;
			}
			if (tim == -1){
				continue;
			}
			now = st;
			for(int i = 1; i <= tim; i++){
				now = now + f * d;
				p.PB(now);
			}
			double tmp_len = (n - tim) * d;
			double y = now.X - sqrt(Sqr(tmp_len) - Sqr(now.Y));
			ed = Point(y, 0);
			f = unit(ed - now);
			for(int i = 1; i <= n - tim; i++){
				now = now + f * d;
				p.PB(now);
			}
			assert(sign(abs(now - ed)) == 0);
			ok = true;
			break;
		}
		if (!ok){
			puts("-1");
		}
		else{
			printf("%d\n", p.size());
			rep(i, p.size()){
				printf("0 %.12f %.12f\n", p[i].X, p[i].Y);
			}
		}
	}
	return 0;
}
