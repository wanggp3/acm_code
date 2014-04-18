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

const int N = 500000 + 1000;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

int n;
int v[N];
vector<int> E[N];

bool del[N];
int dp[N][2];
vector<int> ans;

void dfs(int x, int f){
	dp[x][0] = dp[x][1] = 0;
	v[x] = -1;
	rep(i, E[x].size()){
		int y = E[x][i];
		if (y == f) continue;
		dfs(y, x);
		if (dp[x][0] + dp[y][0] + 1 > dp[x][1] + max(dp[y][0], dp[y][1])){
			dp[x][1] = dp[x][0] + dp[y][0] + 1;
			v[x] = y;
		}
		else{
			dp[x][1] = dp[x][1] + max(dp[y][0], dp[y][1]);
		}
		dp[x][0] += max(dp[y][0], dp[y][1]);
	}
}

void go(int x, int f){
	if (!del[x] && dp[x][1] > dp[x][0]){
		del[x] = del[v[x]] = true;
		ans.PB(v[x]);
	}
	rep(i, E[x].size()){
		int y = E[x][i];
		if (y == f) continue;
		go(y, x);
	}
}

int main(){
	freopen("grant.in", "r", stdin);
	freopen("grant.out", "w", stdout);
	while(~scanf("%d", &n)){
		ans.clear();
		rep(i, n){
			E[i].clear();
			del[i] = false;
		}
		rep(i, n - 1){
			int x;
			scanf("%d", &x);
			x--;
//			E[i + 1].PB(x);
			E[x].PB(i + 1);
		}
		dfs(0, -1);
		go(0, -1);
		sort(ans.begin(), ans.end());
		printf("%d\n", 1000 * ans.size());
		rep(i, ans.size()){
			if (i) putchar(' ');
			printf("%d", 1 + ans[i]);
		}
		puts("");
	}
	return 0;
}
