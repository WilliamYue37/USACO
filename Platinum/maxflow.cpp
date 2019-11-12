#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
#define MAXN 50005
#define MAXLOG 30

typedef long long ll;
typedef pair<int, int> pi;

int N, K;
vector<int> adjList[MAXN];
int depth[MAXN], parent[MAXN][MAXLOG];
int delta[MAXN];
int ans = 0;

void DFS(int u, int p, int d) {
	depth[u] = d; parent[u][0] = p;
	for (int v: adjList[u]) {
		if (v != p) DFS(v, u, d + 1);
	}
}

void LCA_precompute() {
	DFS(1, 0, 0);
	for (int k = 1; k < MAXLOG; ++k) {
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
	for (int k = MAXLOG-1; k >= 0; --k) {
		if (parent[a][k] != parent[b][k]) {
			a = parent[a][k], b = parent[b][k];
		}
	}
	return parent[a][0];
}

int dfs2(int u, int p) {
	int flow = delta[u];
	for (int v: adjList[u]) {
		if (v != p) flow += dfs2(v, u);
	}
	ans = max(ans, flow);
	return flow;
}

int main() {
	freopen("maxflow.in", "r", stdin);
	freopen("maxflow.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> K;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	LCA_precompute();

	for (int i = 0; i < K; ++i) {
		int u, v; cin >> u >> v;
		int lca = LCA(u, v);
		++delta[u];
		++delta[v];
		--delta[lca];
		--delta[parent[lca][0]];
	}

	dfs2(1, -1);

	cout << ans << "\n";

	return 0;
}