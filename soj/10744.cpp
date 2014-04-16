// label : data struct
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

const int N = 233333;
const int M = 1 << 17;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;
const bool ISMAX = true;
const bool ISMIN = false;

typedef pair<int, int> pii;

int n, m;
int tot;
vector<int> E[N];

int d_in[N];
int d_out[N];;

int v[N];
pii edge[N];

char s[10];

int mi[M << 1], ma[M << 1];

void change(int x, int val, int t[], bool ma){
	x += M + 1;
	t[x] = val;
	for(x >>= 1; x; x >>= 1){
		if (ma) t[x] = max(t[x << 1], t[x << 1 ^ 1]);
		else t[x] = min(t[x << 1], t[x << 1 ^ 1]);
	}
}

int ask(int l, int r, int t[], bool ma){
	l++, r++;
	int ret = (ma) ? -INF : INF;
	for(l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1){
		if (~l & 1){
			if (ma) ret = max(ret, t[l ^ 1]);
			else ret = min(ret, t[l ^ 1]);
		}
		if (r & 1){
			if (ma) ret = max(ret, t[r ^ 1]);
			else ret = min(ret, t[r ^ 1]);
		}
	}
	return ret;
}

void dfs(int x, int f){
	d_in[x] = tot++;
	change(d_in[x], v[x], mi, ISMIN);
	change(d_in[x], v[x], ma, ISMAX);
	rep(i, E[x].size()){
		int y = E[x][i];
		if (y == f) continue;
		dfs(y, x);
	}
	d_out[x] = tot;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		rep(i, n){
			E[i].clear();
		}
		rep(i, n){
			scanf("%d", &v[i]);
		}
		rep(i, n - 1){
			int x, y;
			scanf("%d%d", &x, &y);
			x--, y--;
			edge[i] = MP(x, y);
			E[x].PB(y);
			E[y].PB(x);
		}
		tot = 0;
		rep(i, M << 1) mi[i] = INF, ma[i] = -INF;
		dfs(0, -1);
		rep(i, m){
			scanf("%s", s);
			if (s[0] == 'Q'){
				int k;
				scanf("%d", &k);
				k--;
				int x = edge[k].F, y = edge[k].S;
				if (d_in[x] < d_in[y]) x = y;
				LL min_val_1 = ask(d_in[x], d_out[x] - 1, mi, ISMIN);
				LL max_val_1 = ask(d_in[x], d_out[x] - 1, ma, ISMAX);
				LL min_val_2 = min(ask(0, d_in[x] - 1, mi, ISMIN), ask(d_out[x], tot, mi, ISMIN));
				LL max_val_2 = max(ask(0, d_in[x] - 1, ma, ISMAX), ask(d_out[x], tot, ma, ISMAX));
				printf("%lld\n", min_val_1 * max_val_1 + min_val_2 * max_val_2);
			}
			else if (s[0] == 'C'){
				int x, y;
				scanf("%d%d", &x, &y);
				x--;
				change(d_in[x], y, mi, ISMIN);
				change(d_in[x], y, ma, ISMAX);
			}
		}
	}
	return 0;
}
