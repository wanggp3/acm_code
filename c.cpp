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

const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

const int N = 101000;

typedef pair<int, int> pii;

int n, k;

int tot, top, mi, root;
vector<pii> E[N];
int v[N];

bool use[N];
int size[N];

int tot_p, tot_q;
pii p[N];
pii q[N];
pii tmp[N];

LL ans;

void get_val(int x,LL val,int fa){
	q[tot_q++] = MP(v[x], val);
    rep(i, E[x].size()){
        int y = E[x][i].F, cost = E[x][i].S;
		if (use[y] || y == fa) continue;
		get_val(y, val + cost, x);
    }
}

void get_root(int x,int fa){
    int big=-1;
    size[x]=1;
    rep(i,E[x].size()){
        int y=E[x][i].F;
        if (use[y]||y==fa) continue;
        get_root(y,x);
        size[x]+=size[y];
        big=max(big,size[y]);
    }
    big=max(big,tot-size[x]);
    if (big<mi) mi=big,root=x;
}

void go(pii a[], int cnt_a, pii b[], int cnt_b){
	/*
	cout << " ### " << endl;
	rep(i, cnt_a){
		cout << "(" << a[i].F << ' ' << a[i].S << ")" << ' ';
	}
	cout << endl;
	rep(i, cnt_b){
		cout << "(" << b[i].F << ' ' << b[i].S << ")" << ' ';
	}
	cout << endl;
	*/
	int fa = cnt_a - 1, fb = cnt_b - 1;
	int ma = -INF;
	while(fa >= 0){
		while(fb >= 0 && b[fb].F >= a[fa].F){
			ma = max(ma, b[fb].S);
			fb--;
		}
		//cout << a[fa].F << ' ' << ma + a[fa].F << endl;
		ans = max(ans, a[fa].F * (LL)(ma + a[fa].S));
		fa--;
	}
}

void dfs(int x){
	tot = mi = size[x];
	get_root(x, -1);
	x = root;
	use[x] = true;
	tot_p = 0;
	p[tot_p++] = MP(v[x], 0);
	rep(i, E[x].size()){
		int y = E[x][i].F, cost = E[x][i].S;
		if (use[y]) continue;
		tot_q = 0;
		get_val(y, cost, x);
		sort(q, q + tot_q);
		go(p, tot_p, q, tot_q);
		go(q, tot_q, p, tot_p);
		int cnt = 0;
		int fp = 0, fq = 0;
		while(fp < tot_p || fq < tot_q){
			pii now;
			if (fp == tot_p){
				now = q[fq++];
			}
			else if (fq == tot_q){
				now = p[fp++];
			}
			else if (p[fp].F < q[fq].F) {
				now = p[fp++];
			}
			else{
				now = q[fq++];
			}
			tmp[cnt++] = now;
		}
		rep(j, cnt) p[j] = tmp[j];
		tot_p = cnt;
	}
#ifdef OUT
	cout << root << endl;
	rep(i, tot_p){
		cout << "(" << p[i].F << ' ' << p[i].S << ")" << ' ';
	}
	cout << endl;
#endif
	rep(i, E[x].size()){
		int y = E[x][i].F;
		if (use[y]) continue;
		dfs(y);
	}
}

int main(){
	std::ios::sync_with_stdio(false);
	int T;
	cin >> T;
	rep(cas, T){
		cin >> n;
        rep(i, n){
			E[i].clear();
			use[i] = false;
		}
		rep(i, n){
			cin >> v[i];
		}
        rep(i, n - 1){
            int x, y, c;
			cin >> x >> y >> c;
            x--,y--;
            E[x].PB(MP(y, c));
            E[y].PB(MP(x, c));
        }
        size[0] = n;
        ans = 0;
        dfs(0);
		cout << "Case " << cas + 1 << ": " << ans << endl;
    }
    return 0;
}
