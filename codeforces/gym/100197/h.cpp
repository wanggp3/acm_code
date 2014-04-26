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

const int N = 1000000;
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
	void operator +=(Bignum &a){
		len = max(len, a.len);
		rep(i, len){
			v[i] += a.v[i];
		}
		rep(i, len){
			v[i + 1] += v[i] / BASE;
			v[i] = v[i] % BASE;
			if (v[len]) len++;
		}
	}
	void operator /= (int x){
		int pre = 0;
		for(int i = len - 1; i >= 0; i--){
			v[i] += pre * BASE;
			pre = v[i] % x;
			v[i] = v[i] / x;
		}
		while(len && v[len - 1] == 0) len--;
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
};

int n, m;
int id[20][20];
int v[20][20];
int tmp[20][20];
pair<int, int> inv[20 * 20];
bool vis[20 * 20];
Bignum ret, now;

void get_pow(Bignum &now, int tim){
	now.len = 1;
	memset(now.v, 0, sizeof now.v);
	now.v[0] = 1;
	rep(i, tim) now += now;
}

void print(){
	rep(i, n){
		rep(j, m){
			cout << v[i][j] << ' ';
		}
		cout << endl;
	}
}

int work(){
	rep(i, n){
		rep(j, m){
			vis[v[i][j]] = false;
		}
	}
	int tot = 0;
	rep(i, n){
		rep(j, m){
			int now = id[i][j];
			if (vis[now]) continue;
			tot++;
			while(!vis[now]){
				vis[now] = true;
				now = v[inv[now].F][inv[now].S];
			}
		}
	}
	return tot;
}

void check(){
	rep(i, n){
		rep(l, m){
			rep(j, n){
				rep(k, m - 1){
					swap(v[j][k], v[j][k + 1]);
				}
			}
			get_pow(now, work());
			ret += now;
		}
		rep(j, n - 1){
			rep(k, m){
				swap(v[j][k], v[j + 1][k]);
			}
		}
	}
}

int main(){
	freopen("tickets.in", "r", stdin);
	freopen("tickets.out", "w", stdout);
	cin >> n >> m;
	int cnt = 0;
	rep(i, n){
		rep(j, m){
			inv[cnt] = make_pair(i, j);
			id[i][j] = v[i][j] = cnt++;
		}
	}
	if (n == m){
		rep(rotate, 4){
			check();
			rep(i, n){
				rep(j, n){
					tmp[i][j] = v[i][j];
				}
			}
			rep(i, n){
				rep(j, n){
					v[i][j] = tmp[n - 1 - j][i];
				}
			}
		}
		ret /= (4 * n * m);
	}
	else{
		check();
		rep(i, n){
			rep(j, m){
				tmp[i][j] = v[i][j];
			}
		}
		rep(i, n){
			rep(j, m){
				v[i][j] = tmp[n - 1 - i][m - 1 - j];
			}
		}
		check();
		ret /= (2 * n * m);
	}
	ret.print();
	return 0;
}
