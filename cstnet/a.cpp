//label : work
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

const int N = 23333;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

int T;
char s1[N], s2[N], s3[N];
double x, y, z;

int main(){
	scanf("%d", &T);
	rep(cas, T){
		//scanf("%s %s %s", s1, s2, s3);
		scanf("%lf%s%lf%s%lf%s", &x, s1, &y, s2, &z, s3);
		string s;

		s = "";
		rep(i, strlen(s1)) s += s1[i];
		if (s == "m") x *= 1000;
		if (s == "dm") x *= 100;
		if (s == "cm") x *= 10;
		if (s == "mm") x *= 1;
		if (s == "um") x /= 1000;
		if (s == "nm") x /= 1000000;

		s = "";
		rep(i, strlen(s2)) s += s2[i];
		if (s == "m")  y *= 1000;
		if (s == "dm") y *= 100;
		if (s == "cm") y *= 10;
		if (s == "mm") y *= 1;
		if (s == "um") y /= 1000;
		if (s == "nm") y /= 1000000;

		printf("Case %d: %.2fpx\n", cas + 1, z * x / y);
	}
	return 0;
}
