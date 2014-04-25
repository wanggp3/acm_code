//label : math
//By myf
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

const int N = 128;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

int n, m;
vector<string> ans;
stack<int> p[N];
string to_str[N];

LL v[N];

string go(int st, int ed){
//	cout << st << ' ' << ed << endl;
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
//	p[ed].push(id);
//	cout << ret << endl;
//	cout << st << ' ' << ed << endl;
	return ret;
}

void move(int num, int st, int ed, int cnt){
	//if (v[num] != -1) return ;
	v[num] = 0;
	if (num <= 0) return;
	if (num == 1){
		v[num] = 1;
		ans.PB(go(st, ed));
		return;
	}
//#define OUT_ALL
#ifdef OUT_ALL
	cout << num << ' ' << st << ' ' << ed << ' '  << cnt << ' ' << "in" << endl;
#endif
	int move_out = min(cnt - 2, num - 1);
	int count = move_out - (cnt - 2), base = num - move_out;
	//cout << move_out << ' ' << count << ' ' << base << endl;
	//cout << count << endl;
	for(int i = 1; i <= cnt; i++){
		if (i == st || i == ed) continue;
		if (count == 0){
			v[num] += v[base];
			move(base, st, i, cnt);
		}
		else if (count > 0){
			v[num]++;
			ans.PB(go(st, i));
		}
		count++;
	}
	v[num]++;
	ans.PB(go(st, ed));
	for(int i = cnt; i >= 1; i--){
		if (i == st || i == ed) continue;
		//cout << i << ' ' << count << endl;
		if (count == 1){
			v[num] += v[base];
			move(base, i, ed, cnt);
		}
		else if (count > 1){
			v[num]++;
			ans.PB(go(i, ed));
		}
		count--;
	}
#ifdef OUT_ALL
	cout << num << ' ' << st << ' ' << ed << ' '  << cnt << ' ' << "out" << endl;
#endif
}

int main(){
	//freopen("b.in", "r", stdin);
//	freopen("hanoi.in", "r", stdin);
//	freopen("hanoi.out", "w", stdout);
	for(int i = 0; i < 10; i++){
		to_str[i] = "";
		to_str[i].insert(to_str[i].begin(), i + '0');
	}
	for(int i = 10; i < 66; i++){
		to_str[i] = to_str[i / 10] + to_str[i % 10];
	}
	std::ios::sync_with_stdio(false);
	while(cin >> n >> m){
		rep(i, m) while(!p[i + 1].empty()) p[i + 1].pop();
		for(int i = n; i >= 1; i--) p[1].push(i);
		move(n, 1, m, m); 
		cout << ans.size() << endl;
	//	rep(i, ans.size()){
	//		cout << ans[i] << endl;
	//	}
	}
	return 0;
}
