//label : string, graph
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

//typedef long long LL;
typedef unsigned long long LL;
typedef complex<double> Point;
typedef Point Vec;
typedef pair<Point, Point> Line;
//typedef complex<double> Comp;

const int N = 1010;
const int M = 26;
const int L = 60;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

struct Bignum{
	const static int BASE = 10000;
	int len;
	int v[100];
	Bignum(){
		len = 1;
		memset(v, 0, sizeof v);
	}
	void print(){
		if (len == 0){
			puts("0");
			return;
		}
		printf("%d", v[len - 1]);
		for(int i = len - 2; i >= 0; i--){
			printf("%04d", v[i]);
		}
		puts("");
	}
	void operator +=(Bignum &a){
		len = max(len, a.len);
		for(int i = 0; i < len; i++){
			v[i + 1] += (v[i] + a.v[i]) / BASE;
			v[i] = (v[i] + a.v[i]) % BASE;
			if (v[len]) len++;
		}
	}
};

int n, m, len, tot;
int st;
char s[N];
bool is_end[N];

int go[N][M];

int graph[N][M];
int del[N][M];

Bignum dp[61][N];

int check(int x, int y){
	if (go[x][y] != -2) return go[x][y];
	if (del[x][y] == 0) return go[x][y] = graph[x][y];
	go[x][y] = -1;
	return go[x][y] = check(graph[x][y], y);
}

void init(){
	scanf("%s", s);
	tot = strlen(s);
	scanf("%d", &n);
	rep(i, n){
		is_end[i] = false;
	}
	scanf("%d", &st);
	st--;
	scanf("%d", &m);
	rep(i, m){
		int x;
		scanf("%d", &x);
		x--;
		is_end[x] = true;
	}
	rep(i, n){
		rep(j, tot){
			scanf("%d", &graph[i][j]);
			graph[i][j]--;
		}
	}
	rep(i, n){
		rep(j, tot){
			scanf("%d", &del[i][j]);
		}
	}
	scanf("%d", &len);
}

void make_graph(){
	rep(i, n){
		rep(j, tot){
			go[i][j] = -2;
		}
	}
	rep(i, n){
		rep(j, tot){
			check(i, j);
		}
	}
}

void solve(){
	dp[0][st].v[0] = 1;
	rep(i, len){
		rep(j, n){
			rep(k, tot){
				if (go[j][k] == -1) continue;
				dp[i + 1][go[j][k]] += dp[i][j];
			}
		}
	}
	Bignum ret;
	rep(i, n){
		if (!is_end[i]) continue;
		ret += dp[len][i];
	}
	ret.print();
}

int main(){
	freopen("dfa.in", "r", stdin);
	freopen("dfa.out", "w", stdout);
	init();
	make_graph();
	solve();
	return 0;
}
