//label : math
//By myf
//#i
//#pragma comment(linker, "/STACK:16777216")  //C++
#include <cstdio>
#include <assert.h>
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

const int M = (1 << 5) + 1;

struct Matrix{
	int n, m;
	int v[M][M];
}c, ans, tmp;

int l, m, p;
int n[N];
int len;
char s[N];

Matrix operator*(const Matrix &a, const Matrix &b){
	assert(a.m == b.n);
	c.n = a.n, c.m = b.m;
	rep(i, c.n){
		rep(j, c.m){
			c.v[i][j] = 0;
			rep(k, a.m){
				c.v[i][j] = (c.v[i][j] + a.v[i][k] * b.v[k][j]) % p;
			}
		}
	}
	return c;
}

int div(int n[], int d, int &len){
	int pre = 0;
	for(int i = len - 1; i >= 0; i--){
		n[i] += pre * 10;
		pre = n[i] % d;
		n[i] = n[i] / d;
	}
	while(len > 0 && n[len - 1] == 0) len--;
	return pre;
}

void init(){
	static int tmp[N];
	len = strlen(s);
	reverse(s, s + len);
	rep(i, len) tmp[i] = s[i] - '0';
	int tmp_len = 0;
	while(len){
		n[tmp_len++] = div(tmp, 2, len);
	}
	len = tmp_len;
	//rep(i, len) cout << n[i]; cout << endl;
}

void make_matrix(int m){
	tmp.n = tmp.m = (1 << m) + 1;
	int top = (1 << m);
	rep(i, top){
		rep(j, top){
			int x = i, y = j;
			bool ok = true;
			rep(k, m - 1){
				if ((x & 3) == 3 && (y & 3) == 3 || (x & 3) == 0 && (y & 3) == 0){
					ok = false;
				}
				x >>= 1, y >>= 1;
			}
			tmp.v[i][j] = ok;
		}
	}
	rep(i, top + 1){
		tmp.v[top][i] = 1;
	}
	rep(i, top + 1){
		tmp.v[i][top] = 0;
	}
}

void solve(){
	ans.n = 1, ans.m = (1 << m) + 1;
	rep(i, ans.n){
		rep(j, ans.m){
			ans.v[i][j] = 0;
		}
	}
	ans.v[0][ans.m - 1] = 1;
	rep(i, len){
		if (n[i] == 1) ans = ans * tmp;
		tmp = tmp * tmp;
	}
	int ret = 0;
	rep(i, ans.n){
		rep(j, ans.m){
			ret = (ret + ans.v[i][j]) % p;
		}
	}
	printf("%d\n", ret);
}

int main(){
	freopen("nice.in", "r", stdin);
	freopen("nice.out", "w", stdout);
	while(~scanf("%s%d%d", s, &m, &p)){
		init();
		make_matrix(m);
		solve();
	}
	return 0;
}
