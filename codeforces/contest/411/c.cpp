// label : easy
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

pii v[4];

bool win(int a, int b, int c, int d){
	return v[a].F > v[d].S && v[b].S > v[c].F;
}

int main(){
	while(~scanf("%d%d", &v[0].F, &v[0].S)){
		rep(i, 3){
			scanf("%d%d", &v[i + 1].F, &v[i + 1].S);
		}
		if (win(0, 1, 2, 3) && win(0, 1, 3, 2) || win(1, 0, 2, 3) && win(1, 0, 3, 2)){
			puts("Team 1");
		}
		else if ((win(2, 3, 0, 1) || win(3, 2, 0, 1)) && (win(2, 3, 1, 0) || win(3, 2, 1, 0))){
			puts("Team 2");
		}
		else{
			puts("Draw");
		}
	}
	return 0;
}
