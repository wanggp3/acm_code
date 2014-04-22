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

int n, m;
int k, b, l;
string p, q;

int fac[64][23];

void calc(int n, string &s){
	s = "";
	while(n){
		int tmp = n % b;
		s.insert(s.begin(), '0' + tmp);
		n /= b;
	}
	l = max(l, (int)s.length());
}

void init(int k, int b){
	fac[0][0] = 1;
	fac[1][0] = 1;
	fac[1][1] = 1;
	REP(i, 2, l + 1){
		fac[i][0] = fac[i - 1][0];
		REP(j, 1, k + 1){
			fac[i][j] = fac[i - 1][j] + fac[i - 1][j - 1];
		}
	}
//#define OUT
#ifdef OUT
	rep(i, l + 1){
		rep(j, k + 1){
			cout << i << ' ' << j << ' ' << fac[i][j] << endl;
		}
	}
#endif
}

int go(string s){
	int len = s.length();
	int now_len = s.length();
	int now_k = k;
	int ret = 0;
	rep(i, len){
		if (now_k < 0) break;
		int pos = s[i] - '0';
		if (pos == 0){
			now_len--;
			continue;
		}
		else if (pos == 1){
			ret += fac[now_len - 1][now_k];
			now_k--;
			now_len--;
		}
		else if (pos >= 2){
			if (now_k >= 1){
				//ret += (pos - 1) * fac[now_len - 1][now_k - 1];
				ret += 1 * fac[now_len - 1][now_k - 1];
			}
			ret += fac[now_len - 1][now_k];
			return ret;
			now_len--;
		}
		//cout <<  i << ' ' << ret << endl;
	}
	if (now_k == 0) ret++;
	return ret;
}

int main(){
	freopen("e.in", "r", stdin);
	freopen("e.out", "w", stdout);
	while(~scanf("%d%d", &n, &m)){
		swap(n, m);
		scanf("%d%d", &k, &b);
		l = 0;
		calc(n, p);
		calc(m - 1, q);
		init(k, b);
//		cout << p << ' ' << q << endl;
		printf("%d\n", go(p) - go(q));
	}
	return 0;
}
