#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_N = 1e5 + 5;
const int MAX_LOG = 25;

class SegmentTree {
public:
	int N;
	vector<int> sum, delta;

	SegmentTree() {}

	SegmentTree(int N) {
		this->N = N;
		sum = vector<int>(4 * N + 1);
		delta = vector<int>(4 * N + 1);
		//you don't need to init unless default values are not zero
		//init(1, 0, N - 1);
	}
	
	void update(int l, int r, int val) {update(1, 0, N - 1, l, r, val);} //inclusive range
	
	int query(int l, int r) {return query(1, 0, N - 1, l, r);} //inclusive range
	
	void init(int i, int lo, int hi) {
		//if default segtree values are not zero, initialize node i
		if (lo == hi) return;
		
		int m = (lo + hi) / 2;
		init(2 * i, lo, m);
		init(2 * i + 1, m + 1, hi);
	}
	
	void push(int i) {
		if (delta[i] == 0) return;
		delta[2 * i] = delta[i];
		delta[2 * i + 1] = delta[i];
		delta[i] = 0;
	}

	void pull(int i) {
		sum[i] = sum[2 * i] + delta[2 * i] + sum[2 * i + 1] + delta[2 * i + 1];
	}
	
	void update(int i, int lo, int hi, int l, int r, int val) {
		if (r < lo || hi < l) return;
		if (l <= lo && hi <= r) {
			delta[i] = val;
			return;
		}
		
		push(i);
		
		int m = (lo + hi) / 2;
		update(2 * i, lo, m, l, r, val);
		update(2 * i + 1, m + 1, hi, l, r, val);
		
		pull(i);
	}
	
	int query(int i, int lo, int hi, int l, int r) {
		if (r < lo || hi < l) return 0;
		if (l <= lo && hi <= r) {
			return sum[i] + delta[i];
		}
		
		push(i);
		
		int m = (lo + hi) / 2;
		int sumLeft = query(2 * i, lo, m, l, r);
		int sumRight = query(2 * i + 1, m + 1, hi, l, r);
		
		pull(i);
		
		return sumLeft + sumRight;
	}
};

int N, Q;
int e[MAX_N], pre[MAX_N];
pi preOrder[MAX_N];
vector<int> adjList[MAX_N];
SegmentTree st(MAX_N);
int depth[MAX_N], parent[MAX_N][MAX_LOG]; //must be 1-indexed

void DFS(int u, int p, int d) {
	depth[u] = d; parent[u][0] = p;
	for (int v: adjList[u]) {
		if (v != p) DFS(v, u, d + 1);
	}
}

void LCA_precompute() {
	DFS(1, 0, 0);
	for (int k = 1; k < MAX_LOG; ++k) {
		for (int i = 1; i <= N; ++i) {
			parent[i][k] = parent[parent[i][k - 1]][k - 1];
		}
	}
}

int lift(int u, int h) {
	for (int i = 0; (1 << i) <= h; ++i) {
		if ((h & (1 << i)) != 0) {
			u = parent[u][i];
		}
	}
	return u;
}

int LCA(int a, int b) {
	if (depth[a] < depth[b]) {
		b = lift(b, depth[b] - depth[a]);
	}
	else if (depth[b] < depth[a]) {
		a = lift(a, depth[a] - depth[b]);
	}
	if (a == b) return a;
	for (int k = MAX_LOG-1; k >= 0; --k) {
		if (parent[a][k] != parent[b][k]) {
			a = parent[a][k], b = parent[b][k];
		}
	}
	return parent[a][0];
}

int id = 1;
void DFS2(int u, int p, int preSum) {
	preOrder[u].ff = id++; pre[u] = preSum ^ e[u];
	for (int v: adjList[u]) {
		if (v != p) DFS2(v, u, preSum ^ e[u]);
	}
	preOrder[u].ss = id - 1;
}

int main() {
	freopen("cowland.in", "r", stdin); 
	freopen("cowland.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> Q;
	for (int i = 1; i <= N; ++i) {
		cin >> e[i];
	}
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	LCA_precompute();
	fill(visited, visited + N + 5, false);
	DFS2(1, 0, 0);
	for (int i = 0; i < Q; ++i) {
		int type; cin >> type;
		if (type == 1) {
			int u, v; cin >> u >> v;
			st.update(preOrder[u].ff, preOrder[u].ss, pre[u] ^ st.query(preOrder[u].ff, preOrder[u].ff) ^ v);
		}
		else {
			int u, v; cin >> u >> v;
			int lca = parent[LCA(u, v)][0];
			int pathU = pre[u] ^ st.query(preOrder[u].ff, preOrder[u].ff) ^ pre[lca] ^ st.query(preOrder[lca].ff, preOrder[lca].ff);
			int pathV = pre[v] ^ st.query(preOrder[v].ff, preOrder[v].ff) ^ pre[lca] ^ st.query(preOrder[lca].ff, preOrder[lca].ff);
			if (parent[u][0] == lca) {
				cout << pathV << '\n';
				continue;
			}
			if (parent[v][0] == lca) {
				cout << pathU << '\n';
				continue;
			}
			cout << (pathU ^ pathV) << '\n';
		}
	}

	return 0;
}