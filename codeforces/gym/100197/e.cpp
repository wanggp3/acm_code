//label : dp
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

const int N = 2333;
const int M = 1 << 8;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

typedef pair<int, int> pii;

int n, m, s;
int x[N];
int v[N][N];

int dp[N][M];
pii pre[N][M];

vector<int> ans;

void dfs(int lev, int pos){
	if (lev == 0) return;
	dfs(lev - 1, pre[lev][pos].F);
	ans.PB(pre[lev][pos].S);
}

int main(){
	freopen("quant.in", "r", stdin);
	freopen("quant.out", "w", stdout);
	while(~scanf("%d", &n)){
		rep(i, n){
			scanf("%d", &x[i]);
		}
		scanf("%d%d", &m, &s);
		rep(i, m){
			rep(j, s){
				scanf("%d", &v[i][j]);
			}
		}
		memset(dp, 0x3f, sizeof dp);
		dp[0][0] = 0;
		rep(i, n){
			rep(j, m){
//				if (dp[i][j] >= INF) continue;
				rep(k, s){
					if (dp[i][j] + abs(v[j][k] - x[i]) < dp[i + 1][k & (m - 1)]){
						dp[i + 1][k & (m - 1)] = dp[i][j] + abs(v[j][k] - x[i]);
						pre[i + 1][k & (m - 1)] = MP(j, k);
					}
				}
			}
		}
		int ret = INF, pos = -1;
		rep(i, m){
			if (dp[n][i] < ret){
				ret = dp[n][i];
				pos = i;
			}
		}
		printf("%d\n", ret);
		ans.clear();
		dfs(n, pos);
		rep(i, ans.size()){
			if (i) putchar(' ');
			printf("%d", ans[i]);
		}
		puts("");
	}
	return 0;
}
