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
const int M = 1 << 17;
const int MD = 1000000007;
const int BASE = 12347;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

typedef pair<int, int> pii;
typedef pair<pii, int> piii;

int T;
int n;
vector<int> E[N];
vector<piii> ask[N];

int deep[N];

LL ans[N];
LL t[M << 1];

LL ask_val(int x){
	LL ret = 0;
	x += M;
	while(x){
		ret += t[x];
		ret %= MD;
		x >>= 1;
	}
	return ret;
}

void add(int l, int r, int d){
	for(l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1){
		if (~l & 1) t[l ^ 1] += d, t[l ^ 1] %= MD;
		if ( r & 1) t[r ^ 1] += d, t[r ^ 1] %= MD;
	}
}

void dfs(int now){
	rep(i, ask[now].size()){
		int l = ask[now][i].F.F, r = ask[now][i].F.S, d = ask[now][i].S;
		add(l, r, d);
	}
	ans[now] = ask_val(deep[now]);
	rep(i, E[now].size()){
		int y = E[now][i];
		deep[y] = deep[now] + 1;
		dfs(y);
	}
	rep(i, ask[now].size()){
		int l = ask[now][i].F.F, r = ask[now][i].F.S, d = ask[now][i].S;
		add(l, r, -d);
	}
}

int main(){
	scanf("%d", &T);
	rep(cas, T){
		scanf("%d", &n);
		rep(i, n){
			E[i].clear();
			ask[i].clear();
		}
		rep(i, n - 1){
			int x;
			scanf("%d", &x);
			x--;
			E[x].PB(i + 1);
		}
		rep(i, M << 1) t[i] = 0;
		int q;
		scanf("%d", &q);
		rep(i, q){
			int u, l, r, d;
			scanf("%d%d%d%d", &u, &l, &r, &d);
			u--;
			ask[u].PB(MP(MP(l, r), d));
		}
		deep[0] = 1;
		dfs(0);
		LL ret = 0;
		rep(i, n){
			ret = (ret * BASE % MD + ans[i]) % MD;
		}
		printf("Case %d: %d\n", cas + 1, (int)((ret % MD + MD) % MD));
	}
	return 0;
}
