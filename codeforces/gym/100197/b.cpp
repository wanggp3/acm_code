//label : math
//By myf
//#pragma comment(linker, "/STACK:16777216")  //C++
#include <cstdio>
#include <assert.h>
#include <limits>
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

const int N = 64 + 1;
const int M = 65 + 1;
const int MD = 1000000007;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

int n, m;
string to_str[M];

bool ok[N];
stack<int> p[M];
vector<string> ans;

LL dp[N][M];
int pre[N][N];

LL dfs(int n, int m){
	if (dp[n][m] != -1) return dp[n][m];
	if (m == 1) return dp[n][m] = INF;
	if (n == 1) return dp[n][m] = 1;
	dp[n][m] = INF;
	for(int i = 1; i < n; i++){
		if (dfs(i, m) >= INF) continue;
		if (dfs(n - i, m - 1) >= INF) continue;
		if (dp[i][m] * 2 + dp[n - i][m - 1] < dp[n][m]){
			dp[n][m] = dp[i][m] * 2 + dp[n - i][m - 1];
			pre[n][m] = i;
		}
	}
	return dp[n][m];
}

void init(){
	for(int i = 0; i < 10; i++){
		to_str[i] = "";
		to_str[i].insert(to_str[i].begin(), i + '0');
	}
	for(int i = 10; i < 66; i++){
		to_str[i] = to_str[i / 10] + to_str[i % 10];
	}
	rep(i, N){
		rep(j, M){
			dp[i][j] = -1;
		}
	}
}

string go(int st, int ed){
	//cout << st << ' ' << ed << endl;
	assert(st >= 1 && st <= m);
	assert(ed >= 1 && ed <= m);
	assert(!p[st].empty());
	string ret = "";
	int id = p[st].top();
	p[st].pop();
	ret = "move " + to_str[id] + " from " + to_str[st] + " to " + to_str[ed];
	if (!p[ed].empty()){
		ret += " atop " + to_str[p[ed].top()];
	}
	p[ed].push(id);
//	cout << ret << endl;
	return ret;
}

void move(int num, int cnt, int st, int ed){
	if (num <= 0) return;
	//cout << num << ' ' << cnt << ' ' << st << ' ' << ed << endl;
	if (num == 1){
		ans.PB(go(st, ed));
		return;
	}
	vector<int> tmp;
	for(int i = 1; i <= m; i++){
		if (i == st || i == ed || !ok[i]) continue;
		tmp.push_back(i);
	}
	int pos = pre[num][cnt];
	move(pos, cnt, st, tmp[0]);
	ok[tmp[0]] = false;
	move(num - pos, cnt - 1, st, ed);
	ok[tmp[0]] = true;
	move(pos, cnt, tmp[0], ed);
}

int main(){
	freopen("hanoi.in", "r", stdin);
	freopen("hanoi.out", "w", stdout);
	std::ios::sync_with_stdio(false);
	init();
	while(cin >> n >> m){
		dfs(n, m);
		rep(i, m) while(!p[i + 1].empty()) p[i + 1].pop();
		for(int i = n; i >= 1; i--) p[1].push(i);
		for(int i = 1; i <= n; i++) ok[i] = true;
		ans.clear();
		move(n, m, 1, m); 
		cout << ans.size() << endl;
		rep(i, ans.size()){
			cout << ans[i] << endl;
		}
	}
	return 0;
}
