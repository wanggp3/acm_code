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

const int N = 500;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

typedef pair<int, int> pii;
typedef pair<int, pii> piii;

struct KM{
	int n, m;
	int graph[N][N];
	int lx[N], ly[N];
	bool vx[N], vy[N];
	int slack[N];
	int cx[N], cy[N];

	void init(int _n, int _m){
		n = _n;
		m = _m;
		rep(i, n){
			rep(j, m){
				graph[i][j] = 0;
			}
		}
	}

	bool find(int x){
		vx[x] = true;
		rep(y, m){
			if (vy[y]) continue;
			if (lx[x] + ly[y] == graph[x][y]){
				vy[y] = true;
				if (cy[y] == -1 || find(cy[y])){
					cy[y] = x;
					cx[x] = y;
					return true;
				}
			}
			else{
				slack[y] = min(slack[y], lx[x] + ly[y] - graph[x][y]);
			}
		}
		return false;
	}

	int max_match(){
#ifdef OUT_GRAPH
		rep(i, n){
			rep(j, m){
				cout << graph[i][j] << ' ' ;
			}
			cout << endl;
		}
#endif
		rep(i, n){
			lx[i] = *max_element(graph[i], graph[i] + m);
			cx[i] = -1;
		}
		rep(i, m){
			ly[i] = 0;
			cy[i] = -1;
		}
		rep(x, n){
			if (cx[x] != -1) continue;
			memset(slack, 0x3f, sizeof slack);
			while(true){
				memset(vx, 0, sizeof vx);
				memset(vy, 0, sizeof vy);
				if (find(x)) break;
				int sub = INF;
				rep(i, m){
					if (!vy[i]){
						sub = min(sub, slack[i]);
					}
				}
	//			if (sub == 0) break;
				rep(i, n){
					if (vx[i]){
						lx[i] -= sub;
					}
				}
				rep(i, m){
					if (vy[i]){
						ly[i] += sub;
					}
				}
			}
		}
		int ret = 0;
		rep(i, n){
			if (cx[i] == -1) continue;
			ret += graph[i][cx[i]];//graph[match[i]][i];
		}
#ifdef OUT_L
		rep(i, n){
			cout << lx[i] << ' ';
		}
		cout << endl;
		rep(j, m){
			cout << ly[j] << ' ';
		}
		cout << endl;
#endif
		return ret;
	}
}km;

int n, m;
int deep[N];
pii fa[N];
vector<piii> E[N];
vector<piii> edge;

void dfs(int x, int f){
	rep(i, E[x].size()){
		int y = E[x][i].F, cost = E[x][i].S.F, id = E[x][i].S.S;
		if (y == f || id >= n - 1) continue;
		fa[y] = MP(x, id);
		deep[y] = deep[x] + 1;
		dfs(y, x);
	}
}

void calc(int x, int y, int add_id, int add_cost){
	while(x != y){
		if (deep[x] < deep[y]) swap(x, y);
		int id = fa[x].S;
		if (edge[id].F >= add_cost){
			km.graph[id][add_id] = edge[id].F - add_cost;
		}
		x = fa[x].F;
	}
}

void init(){
	scanf("%d%d", &n, &m);
	//km.init(n - 1, m - (n - 1));
	km.init(m, m);
	rep(i, n){
		E[i].clear();
	}
	edge.clear();
	rep(i, m){
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		x--, y--;
		edge.PB(MP(c, MP(x, y)));
		E[x].PB(MP(y, MP(c, i)));
		E[y].PB(MP(x, MP(c, i)));
	}
}

void make_graph(){
	deep[0] = 0;
	fa[0] = MP(-1, -1);
	dfs(0, -1);
#ifdef OUT_FA
	rep(i, n){
		cout << deep[i] << ' ' << fa[i].F << ' ' << fa[i].S << endl;
	}
#endif
	REP(i, n - 1, m){
		int x = edge[i].S.F, y = edge[i].S.S, cost = edge[i].F;
		//calc(x, y, i - (n - 1), cost);
		calc(x, y, i, cost);
	}
}

int main(){
	freopen("roads.in", "r", stdin);
	freopen("roads.out", "w", stdout);
	init();
	make_graph();
	km.max_match();
	rep(i, m){
		if (i < n - 1){
			printf("%d\n", edge[i].F - km.lx[i]);
		}
		else{
			printf("%d\n", edge[i].F + km.ly[i]);
		}
	}
	return 0;
}
