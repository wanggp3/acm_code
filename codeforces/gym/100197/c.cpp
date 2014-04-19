//label : data_structure
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

int n;
deque<LL> p, q;

void get_mi(LL &x){
	if (p.size() == 0){
		x = q.front();
		q.pop_front();
	}
	else if (q.size() == 0){
		x = p.front();
		p.pop_front();
	}
	else if (p.front() < q.front()){
		x = p.front();
		p.pop_front();
	}
	else{
		x = q.front();
		q.pop_front();
	}
}

int main(){
	freopen("huffman.in", "r", stdin);
	freopen("huffman.out", "w", stdout);
	while(~scanf("%d", &n)){
		p.clear();
		q.clear();
		rep(i, n){
			LL x;
			scanf("%I64d", &x);
			p.PB(x);
		}
		LL ret = 0;
		while(p.size() + q.size() > 1){
			LL x, y;
			get_mi(x);
			get_mi(y);
			q.PB(x + y);
			ret += x + y;
		}
		printf("%I64d\n", ret);
	}
	return 0;
}
