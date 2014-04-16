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

const int N = 222;
const int M = 3 * N * N;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

int n, m;
int id[N][N];
int mi[N][N];
int ans[M];

struct Cla{
	struct Edge{
		int t, u;
		Edge *nx, *op;
	}*e[N], mem[M], *C;
	int n, S, T;
	int vh[N], h[N];

	void init(int num){
		n = num;
		C = mem;
		rep(i, n) e[i] = NULL;
	}

	void add_edge(int u, int v, int c){
		C->t = v, C->u = c, C->nx = e[u], e[u] = C++;
		C->t = u, C->u = 0, C->nx = e[v], e[v] = C++;
		e[u]->op = e[v];
		e[v]->op = e[u];
	}

	int aug(int p, int m){
		if (p == T) return m;
		int d = m;
		for(Edge *i = e[p]; i; i = i->nx){
			if (i->u && h[p] == h[i->t] + 1){
				int f = aug(i->t, min(i->u, d));
				i->u -= f, i->op->u += f, d-= f;
				if (h[S] == n || !d) return m - d;
			}
		}
		int w = d < m ? min(n, h[p] + 2) : n;
		for(Edge *i = e[p]; i; i = i->nx){
			if (i->u) w = min(w, h[i->t] + 1);
		}
		++vh[w];
		--vh[h[p]] ? h[p] = w : h[S] = n;
		return m - d;
	}

	int maxflow(int s, int t){
		S = s, T = t;
		rep(i, n) vh[i] = 0, h[i] = 0;
		vh[0] = n;
		int ret = 0;
		while(h[S] != n) ret += aug(S, INF);
		return ret;
	}

	void make_graph(){
		rep(x, n){
			for(Edge *i = e[x]; i; i = i->nx){
				int y = i->t;
				if (id[x][y] == -1){
					continue;
				}
				ans[id[x][y]] = mi[x][y] + i->op->u;
			}
		}
	}
}graph;

int main(){
	freopen("cooling.in", "r", stdin);
	freopen("cooling.out", "w", stdout);
	scanf("%d%d", &n, &m);
	graph.init(n + 2);
	int S = n, T = S + 1;
	rep(i, n + 2){
		rep(j, n + 2){
			id[i][j] = -1;
		}
	}
	int sum = 0;
	rep(i, m){
		int x, y, c, d;
		scanf("%d%d%d%d", &x, &y, &c, &d);
		x--, y--;
		id[x][y] = i;
		mi[x][y] = c;
		graph.add_edge(S, y, c);
		graph.add_edge(x, T, c);
		graph.add_edge(x, y, d - c);
		sum += c;
	}
	if (graph.maxflow(S, T) >= sum){
		puts("YES");
		graph.make_graph();
		rep(i, m){
			printf("%d\n", ans[i]);
		}
	}
	else{
		puts("NO");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
