#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_N = 200005;
const int MAX_LOG = 20;

int N, M;
vector<int> adjList[MAX_N];
vector<pi> extra;
int start[MAX_N], pre[MAX_N];
map<pi, int> mp;
int depth[MAX_N], parent[MAX_N][MAX_LOG + 1]; //must be 1-indexed

void DFS(int u, int p, int d) {
	depth[u] = d; parent[u][0] = p;
	for (int v: adjList[u]) {
		if (v != p) DFS(v, u, d + 1);
	}
}

void LCA_precompute() {
	DFS(1, -1, 0);
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

int lift2(int u, int target) {
	if (u == target) return -1;
	for (int i = MAX_LOG - 1; i >= 0; --i) {
		if (depth[parent[u][i]] > depth[target]) u = parent[u][i];
	}
	return u;
}

void DFS2(int u, int p, int sum) {
	pre[u] = sum;
	for (int v: adjList[u]) {
		if (v != p) DFS2(v, u, sum + start[v]);
	}
}

int main() {
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	LCA_precompute();
	ll ans = 0;
	for (int i = N - 1; i < M; ++i) {
		int u, v; cin >> u >> v;
		extra.push_back({u, v});
		int lca = LCA(u, v);
		int liftU = lift2(u, lca), liftV = lift2(v, lca);
		if (liftU != -1) ans -= ++start[liftU];
		if (liftV != -1) ans -= ++start[liftV];
		if (liftU != -1 && liftV != -1) {
			if (liftU > liftV) swap(liftU, liftV);
			ans -= mp[{liftU, liftV}]++;
		}
	}
	DFS2(1, -1, 0);
	for (pi edge: extra) {
		ans += pre[edge.ff] + pre[edge.ss] - 2 * pre[LCA(edge.ff, edge.ss)];
	}
	cout << ans << '\n';

	return 0;
}