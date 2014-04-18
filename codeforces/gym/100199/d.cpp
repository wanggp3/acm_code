//label : graph
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

int n, m;
int d[N];

int main(){
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	while(~scanf("%d%d", &n, &m)){
		rep(i, n){
			d[i] = 0;
		}
		rep(i, m){
			int x, y;
			scanf("%d%d", &x, &y);
			x--, y--;
			d[x]++;
			d[y]++;
		}
		LL ret = 0;
		rep(i, n) ret += (LL)d[i] * d[i];
		printf("%I64d\n", ret);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
