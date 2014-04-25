// label : graph, string
//By myf
#pragma comment(linker, "/STACK:167772160")  //C++
#include <cstdio>
#include <iostream>
#include <assert.h>
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

const int N = 100000;
const int MD = 1000000007;
const int INF = 0x3f3f3f3f;
const double PI = acos(-1.0);
const double EPS = 1E-6;

typedef pair<int, int> pii;

struct Trie{
	struct Node{
		Node *ch[26];
		Node *suffix;
		int id;
		bool danger;
	};
	Node mem[N], *C, *root;

	int m;
	int tot;

	Node *newNode(bool danger = false){
		while(C == NULL);
		rep(i, 26) C->ch[i] = NULL;
		C->suffix = NULL;
		C->danger = danger;
		C->id = tot++;
		while(tot >= N);
		return C++;
	}

	void init(int _m){
		m = _m;
		C = mem;
		tot = 0;
		root = newNode();
	}

	void insert(char *st){
		Node *now = root;
		int pos;
		for(int i = 0; st[i]; i++){
			pos = st[i] - 'a';
//			while (pos >= m);
//			assert(pos < m && pos >= 0 && m <= 26 && m > 0);
			if (now->ch[pos] == NULL){
				now->ch[pos] = newNode(now->danger);
			}
			now = now->ch[pos];
		}
		now->danger = true;
	}

	void make_graph(){
		deque<Node*> Q;
		Node *now, *nxt;
		rep(i, 26){
			if (root->ch[i] == NULL){
				root->ch[i] = root;
			}
			else{
				root->ch[i]->suffix = root;
				Q.PB(root->ch[i]);
			}
		}
		while(!Q.empty()){
			now = Q.front(); Q.pop_front();
			now->danger |= now->suffix->danger;
			rep(i, 26){
				if (now->ch[i] == NULL){
					now->ch[i] = now->suffix->ch[i];
					continue;
				}
				nxt = now->ch[i];
				nxt->suffix = now->suffix->ch[i];
				Q.push_back(nxt);
			}
		}
	};

	void get_edge(int &n, vector<int> E[]){
		n = tot;
		rep(i, n){
			E[i].clear();
		}
		Node *a = mem;
		while(a != C){
			Node *now = a++;
			if (now->danger) continue;
			assert(now != NULL);
			rep(i, m){
				Node *nxt = now->ch[i];
				assert(nxt != NULL);
				if (nxt->danger) continue;
				E[now->id].PB(nxt->id);
				//E.PB(MP(now->id, nxt->id));
			}
		}
	}
}graph;

int n, m;
string st;
char str[1005];

vector<pii> edge;
vector<int> E[N];

int id[N];
int d_in[N];

int dfn_tot, cnt_tot;
int dfn[N], low[N];
bool in_stack[N];
stack<int> sta;

void dfs(int x){
	dfn[x] = low[x] = dfn_tot++;
	sta.push(x);
	in_stack[x] = true;
	rep(i, E[x].size()){
		int y = E[x][i];
		if (dfn[y] == -1){
			dfs(y);
			low[x] = min(low[x], low[y]);
		}
		else if (in_stack[y]){
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (dfn[x] == low[x]){
		while(sta.empty());
		while(sta.top() != x){
			int y = sta.top();
			id[y] = cnt_tot;
			in_stack[y] = false;
			sta.pop();
		}
		while(sta.empty());
		sta.pop();
		id[x] = cnt_tot++;
		in_stack[x] = false;
	}
}

void init(){
	scanf("%d %d", &n, &m);
	graph.init(m);
	while(n--){
		scanf(" %s", str);
		graph.insert(str);
	}
	graph.make_graph();
}

bool solve(){
	graph.get_edge(n, E);
	rep(i, n){
		dfn[i] = -1;
		low[i] = -1;
		in_stack[i] = false;
		d_in[i] = 0;
	}
	dfn_tot = 0;
	cnt_tot = 0;
	rep(i, n){
		if (dfn[i] != -1) continue;
		dfs(i);
	}
	rep(i, n){
		int cnt = 0;
		rep(j, E[i].size()){
			int x = i, y = E[i][j];
			if (id[x] != id[y]) continue;
			cnt++;
			if (cnt >= 2) return true;
		}
	}
	return false;
}

int main(){
//	freopen("3784.in", "r", stdin);
//	freopen("3784.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while(T--){
		init();
		if (solve()) puts("Yes");
		else puts("No");
	}
	return 0;
}
