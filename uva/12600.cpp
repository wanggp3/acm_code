//label : math
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
typedef pair<int, int> pii;
//typedef complex<double> Comp;

const int N = 1000000;
const int M = 10000;
const int D = 3 * 3;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

struct Matrix{
	int n, m;
	LL v[D][D];
}tmp, ans, now;

int n, m;
LL p;
LL ret;

bool vis[M];
vector<int> prime;
vector<pii> fac;

LL multi(LL x, LL y){
	LL T = floor(sqrt(p) + 0.5);
	LL t = T * T - p;
	LL a = x / T, b = x % T;
	LL c = y / T, d = y % T;
	LL e = a * c / T, f = a * c % T;
	LL v = ((a * d + b * c) % p + e * t) % p;
	LL g = v / T, h = v % T;
	LL ret = (((f + g) * t % p + b * d) % p + h * T) % p;
    return (ret % p + p) % p;
}

Matrix operator*(const Matrix &a, const Matrix &b){
	tmp.n = a.n, tmp.m = b.m;
	rep(i, tmp.n){
		rep(j, tmp.m){
			tmp.v[i][j] = 0;
			rep(k, a.m){
				tmp.v[i][j] = (tmp.v[i][j] + multi(a.v[i][k], b.v[k][j])) % p;
			}
		}
	}
	return tmp;
}

void make_prime(){
	prime.clear();
	memset(vis, 0, sizeof vis);
	for(int i = 2; i < M; i++){
		if (vis[i]) continue;
		prime.push_back(i);
		for(int j = 2; j * i < M; j++){
			vis[j * i] = true;
		}
	}
}

void init(){
	m %= p;
	now.n = now.m = 7;
	rep(i, now.n){
		rep(j, now.m){
			now.v[i][j] = 0;
		}
	}
	now.v[0][0] = m - 4, now.v[0][3] = m - 3, now.v[0][5] = m - 3;
	now.v[1][0] = 1, now.v[1][5] = 1;
	now.v[2][0] = 1, now.v[2][3] = 1;
	now.v[3][1] = m - 3, now.v[3][6] = m - 2;
	now.v[4][1] = 1;
	now.v[5][2] = m - 3, now.v[5][4] = m - 2;
	now.v[6][2] = 1;
	
	ans.n = 7, ans.m = 1;
	rep(i, ans.n){
		rep(j, ans.m){
			ans.v[i][j] = 0;
		}
	}
	ans.v[4][0] = multi(m, m - 1);
}

LL g(int m){
	if (m <= 2) return 0;
	init();
	while(m){
		if (m & 1) ans = now * ans;
		m >>= 1;
		now = now * now;
	}
	return ans.v[4][0];
}

void dfs(int lev, int num, int phi){
	if (lev == fac.size()){
		ret = (ret + multi(phi, g(num))) % p;
//		cout << n / num << ' ' << phi << ' ' << num << endl;
		return;
	}
	int now = 1;
	rep(i, fac[lev].S){
		dfs(lev + 1, num, phi / fac[lev].F * (fac[lev].F - 1));
		num *= fac[lev].F;
		phi /= fac[lev].F;
	}
	dfs(lev + 1, num, phi);
}

int main(){
//	freopen("12600.in", "r", stdin);
//	freopen("12600.out", "w", stdout);
	make_prime();
	int T;
	scanf("%d", &T);
	rep(cas, T){
		scanf("%d%d%lld", &n, &m, &p);
		p *= n;
		ret = 0;
		fac.clear();
		int nn = n;
		for(int i = 0; i < prime.size() && prime[i] * prime[i] <= n; i++){
			if (n % prime[i]) continue;
			int num = prime[i];
			int cnt = 0;
			while(n % prime[i] == 0){
				cnt++;
				n /= prime[i];
			}
			fac.PB(MP(prime[i], cnt));
		}
		if (n != 1) fac.PB(MP(n, 1));
		n = nn;
		dfs(0, 1, n);
		printf("Case %d: %d\n", cas + 1, (int)(ret / n));
	}
	return 0;
}
