//label : datastructure
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

const int N = 101000;
const int M = 1 << 17;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

typedef pair<int, int> pii;

int n;
pii v[N];
int id[N];
int y[N];

int len[N];
int pre[N];
int t[M << 1];
vector<int> ans;

int ask(int l, int r){
	l++, r++;
	int ret = n;
	for(l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1){
		if ((~l & 1) && len[t[l ^ 1]] > len[ret]) ret = t[l ^ 1];
		if (( r & 1) && len[t[r ^ 1]] > len[ret]) ret = t[r ^ 1];
	}
	return ret;
}

void insert(int x, int id){
	x++;
	x += M;
	if (len[t[x]] > len[id]) return;
	t[x] = id;
	for(x >>= 1; x; x >>= 1){
		if (len[t[x << 1]] > len[t[x << 1 ^ 1]]){
			t[x] = t[x << 1];
		}
		else{
			t[x] = t[x << 1 ^ 1];
		}
	}
}

bool cmp(int a, int b){
	return v[a] < v[b];
}

void dfs(int now){
	if (now == n) return;
	dfs(pre[now]);
	ans.PB(now);
}

int main(){
	freopen("people.in", "r", stdin);
	freopen("people.out", "w", stdout);
	while(~scanf("%d", &n)){
		rep(i, n){
			id[i] = i;
		}
		rep(i, n){
			scanf("%d%d", &v[i].F, &v[i].S);
			y[i] = v[i].S;
		}
		sort(y, y + n);
		int m = unique(y, y + n) - y;
		rep(i, n) v[i].S = upper_bound(y, y + m, v[i].S) - y;
		sort(id, id + n, cmp);
		len[n] = 0;
		rep(i, M << 1) t[i] = n;
		rep(i, n){
			int j = i;
			while(j < n && v[id[j]].F == v[id[i]].F) j++;
			REP(k, i, j){
				int tmp = ask(0, v[id[k]].S - 1);
				len[id[k]] = len[tmp] + 1;
				pre[id[k]] = tmp;
			}
			REP(k, i, j){
				insert(v[id[k]].S, id[k]);
			}
			i = j - 1;
		}
		int pos = n;
		rep(i, n){
			if (len[i] > len[pos]) pos = i;
		}
		ans.clear();
		dfs(pos);
		printf("%d\n", ans.size());
		rep(i, ans.size()){
			if (i) putchar(' ');
			printf("%d", ans[i] + 1);
		}
		puts("");
	}
	return 0;
}
