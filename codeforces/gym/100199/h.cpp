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
//typedef complex<double> Comp;

const int N = 233;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

struct Bignum{
	int len;
	int v[N];

	Bignum(){
		clear();
	}

	void clear(){
		len = 1;
		memset(v, 0, sizeof v);
	}

	void multi(int d){
		rep(i, len) v[i] *= d;
		rep(i, len){
			v[i + 1] += v[i] / 10;
			v[i] %= 10;
			if (v[len]) len++;
		}
	}

	void dec(int d){
		v[0] -= d;
		rep(i, len){
			if (v[i] >= 0) break;
			v[i + 1]--;
			v[i] += 10;
		}
		while(len && v[len - 1] == 0) len--;
	}

	void print(){
		if (len == 0){
			puts("0");
			return;
		}
		rep(i, len){
			printf("%d", v[len - 1 - i]);
		}
		puts("");
	}
}ans;

int n, m;
vector<int> prime;

int v[N][N];

void init(){
	int now = 2;
	while(prime.size() < 100){
		bool is_prime = true;
		REP(i, 2, now - 1){
			if (now % i == 0) is_prime = false;
		}
		if (is_prime) prime.PB(now);
		now++;
	}
}

int gauss(int n, int m, int p[N][N]){
	static int tmp[N][N];
    static int *b[N];
	int ret = 0;
	rep(i, n){
		rep(j, m){
			tmp[i][j] = p[i][j];
		}
	}
	rep(i, n){
		b[i] = tmp[i];
	}
	int now = 0;
    rep(i, n){
		while(now < m){
			REP(j, i, n){
				if (b[j][now] - b[i][now] > 0) swap(b[i], b[j]);
			}
			if (b[i][now] == 0){
				now++;
				continue;
			}
			break;
		}
		if (now == m) break;
		ret++;
		rep(j, n){
			if (i == j) continue;
			int rate = b[j][now];
			rep(k, m) b[j][k] = (b[j][k] + b[i][k] * rate) % 2;
		}
		//int rate = b[i][now];
		//rep(j, m) b[i][j] /= rate;
		now++;
	}
	rep(i, n){
		rep(j, m){
			p[i][j] = b[i][j];
		}
	}
	return ret;
}

int main(){
	freopen("rsa.in", "r", stdin);
	freopen("rsa.out", "w", stdout);
	init();
	while(~scanf("%d%d", &n, &m)){
		int r = n, c = m;
		rep(i, r){
			rep(j, c){
				v[i][j] = 0;
			}
		}
		rep(i, m){
			int x;
			scanf("%d", &x);
			rep(j, n){
				int cnt = 0;
				while(x % prime[j] == 0){
					x /= prime[j];
					cnt ^= 1;
				}
				v[j][i] = cnt;
			}
		}
		int ret = m - gauss(r, c, v);
		ans.clear();
		ans.v[0] = 1;
		rep(i, ret) ans.multi(2);
		ans.dec(1);
		ans.print();
	}
	return 0;
}
