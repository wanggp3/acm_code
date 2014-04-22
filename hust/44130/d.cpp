//label : unfinished
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

typedef pair<int, int> pii;

int n;
vector<int> E[N];
bool cen[N];
int pre[N];
int dist[N];

pii bfs(int s){
	pii ret;
	rep(i, n){
		dist[i] = -1;
	}
	pre[s] = -1;
	dist[s] = 0;
	deque<int> Q;
	Q.PB(s);
	while(!Q.empty()){
		int x= Q.front(); Q.pop_front();
		ret = MP(x, dist[x]);
		rep(i, E[x].size()){
			int y = E[x][i];
			if (dist[y] != -1) continue;
			dist[y] = dist[x] + 1;
			pre[y] = x;
			Q.PB(y);
		}
	}
	return ret;
}

void go(int now, int lev){
	if (lev == 0){
		cen[now] = true;
		return;
	}
	go(pre[now], lev - 1);
}

int main(){
	while(~scanf("%d", &n)){
		rep(i, n){
			E[i].clear();
			cen[i] = false;
		}
		rep(i, n - 1){
			int x;
			scanf("%d", &x);
			x--;
			E[i + 1].PB(x);
			E[x].PB(i + 1);
		}
		pii ret = bfs(0);
		ret = bfs(ret.F);
		go(ret.F, ret.S / 2);
		if (ret.S & 1){
			go(ret.F, (ret.S + 1)/ 2);
		}
		bool first = true;
		rep(i, n){
			if (!cen[i]) continue;
			if (first) first = false;
			else putchar(' ');
			printf("%d", i + 1);
		}
		puts("");
	}
	return 0;
}
