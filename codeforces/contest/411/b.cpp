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

const int N = 233;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

int n, m, k;
int v[N][N];

int dead[N];
bool lock[N];

int main(){
	while(~scanf("%d%d%d", &n, &m, &k)){
		rep(i, n) dead[i] = -1;
		rep(i, k) lock[i] = false;
		rep(i, n){
			rep(j, m){
				scanf("%d", &v[i][j]);
			}
		}
		rep(i, m){
			rep(j, n){
				if (dead[j] != -1) continue;
				if (v[j][i] == 0) continue;
				rep(k, j){
					if (dead[k] != -1) continue;
					if (v[k][i] == 0) continue;
					if (v[j][i] == v[k][i]){
						lock[v[j][i]] = true;
					}
				}
			}
			rep(j, n){
				if (dead[j] != -1) continue;
				if (v[j][i] == 0) continue;
				if (!lock[v[j][i]]) continue;
				dead[j] = i;
			}
		}
		rep(i, n){
			printf("%d\n", dead[i] + 1);
		}
	}
	return 0;
}
