#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-6;
const int MAX_N = 1e5 + 5;

int N, Q;
vector<int> adjList[MAX_N];
int parent[MAX_N];
set<int> colors[MAX_N];

void DFS(int u, int p) {
	parent[u] = p;
	for (int v: adjList[u]) {
		if (v != p) DFS(v, u);
	}
}

void add(int u, int c) {
	colors[u].insert(c);
	for (int v: adjList[u]) {
		if (v != parent[u]) add(v, c);
	}
}

ll query(int u) {
	ll ret = colors[u].size();
	for (int v: adjList[u]) {
		if (v != parent[u]) ret += query(v);
	}
	return ret;
}

int main() {
	//freopen("snowcow.in", "r", stdin); freopen("snowcow.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> Q;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	DFS(1, -1);

	for (int i = 0; i < Q; ++i) {
		int type; cin >> type;
		if (type == 1) {
			int u, c; cin >> u >> c;
			add(u, c);
		}
		else {
			int u; cin >> u;
			cout << query(u) << '\n';
		}
	}

	return 0;
}