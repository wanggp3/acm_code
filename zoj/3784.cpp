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

struct Trie{
	const static int MAXNODE = 111111;

	struct Node{
		Node *ch[26];
		Node *suffix;
		bool danger;
		int id;
		bool vis;
	};
	Node mem[N], *C, *root;

	int m;
	int tot;
	Node v[N];
	bool vis[N];
	bool dead[N];

	Node *newNode(bool danger = false){
		rep(i, 26) C->ch[i] = NULL;
		C->suffix = NULL;
		C->danger = danger;
		C->id = tot++;
		C->vis = false;
		return C++;
	}

	void init(int _m){
		m = _m;
		C = mem;
		tot = 0;
		root = newNode();
	}

	Node *getson(Node *now, int pos){
		while(true){
			Node *nxt = now->ch[pos];
			if (nxt) return nxt;
			if (now == root) return now;
			now = now->suffix;
		}
	}

	void insert(string &st){
		Node *now = root;
		int pos;
		rep(i, st.length()){
			pos = st[i] - 'a';
			if (!now->ch[pos]){
				now->ch[pos] = newNode();
			}
			now = now->ch[pos];
		}
		now->danger = true;
	}

	void make_graph(){
		deque<Node*> Q;
		Q.PB(root);
		Node *now, *nxt;
		while(!Q.empty()){
			now = Q.front(); Q.pop_front();
			rep(i, m){
				if (now->ch[i] == NULL) continue;
				Q.push_back(now->ch[i]);
				nxt = now->ch[i];
				if (now == root){
					nxt->suffix = root;
				}
				else{
					nxt->suffix = getson(now->suffix, i);
				}
				nxt->danger |= nxt->suffix->danger;
			}
		}
		Node *a = mem;
		root->suffix = NULL;
		while(a != C){
			now = a++;
			rep(i, m){
				if (now->ch[i]) continue;
				nxt = now->suffix;
				while(nxt && nxt->ch[i] == NULL) nxt = nxt->suffix;
				if (nxt == NULL) now->ch[i] = root;
				else now->ch[i] = nxt->ch[i];
			}
		}
	}

	void dfs(Node *now, vector<int> E[]){
		now->vis = true;
		int x = now->id;
		rep(i, m){
			int y = now->ch[i]->id;
			if (now->ch[i]->danger) continue;
			E[x].PB(y);
			if (now->ch[i]->vis) continue;
			dfs(now->ch[i], E);
		}
	}
};

int n, m;
int tot;
Trie graph;
string st;
char s[1111];

vector<int> E[N];

int mark_tot;
int cnt[N];
int mark[N];

bool solve(){
	tot = graph.tot;
	rep(i, tot){
		E[i].clear();
	}
	graph.dfs(graph.root, E);
	/*
	rep(i, tot){
		cout << i << " : ";
		rep(j, E[i].size()){
			cout << E[i][j] << ' ';
		}
		cout << endl;
	}
	*/
	rep(i, tot){
	}
}

int main(){
	int T;
	scanf("%d", &T);
	mark_tot = 0;
	memset(mark, 0, sizeof mark);
	while(T--){
		scanf("%d%d", &n, &m);
		graph.init(m);
		rep(i, n){
			scanf("%s", s);
			int len = strlen(s);
			st = "";
			rep(j, len) st.insert(st.begin(), s[j]);
			graph.insert(st);
		}
		graph.make_graph();
		if (solve()) puts("No");
		else puts("Yes");
	}
	return 0;
}
