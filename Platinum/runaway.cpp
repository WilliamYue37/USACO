#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e18 + 1;
const double EPS = 1e-6;
const int MAX_N = 2e5 + 5;
const int MAX_LOG = 25;

ll N, L;
vector<pl> adjList[MAX_N];
int delta[MAX_N], ans[MAX_N];
int parent[MAX_N][MAX_LOG]; //must be 1-indexed
ll dist[MAX_N]; //dist from node 1

void DFS(int u, int p, ll d) {
	dist[u] = d ,parent[u][0] = p;
	for (pl e: adjList[u]) {
		if (e.ff != p) {
			DFS(e.ff, u, d + e.ss);
		}
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

int lift(int u) {
	int i_u = u;
	for (int i = MAX_LOG - 1; i >= 0; --i) {
		if (dist[i_u] - dist[parent[u][i]] <= L) {
			u = parent[u][i];
		}
	}
	return u;
}

void DFS2(int u, int p) {
	++delta[u];
	--delta[parent[lift(u)][0]];
	for (pl e: adjList[u]) {
		if (e.ff != p) {
			DFS2(e.ff, u);
		}
	}
}

int DFS3(int u, int p) {
	int ret = 0;
	for (pl e: adjList[u]) {
		if (e.ff != p) {
			ret += DFS3(e.ff, u);
		}
	}
	ret += delta[u];
	ans[u] = ret;
	return ret;
}

int main() {
	freopen("runaway.in", "r", stdin); freopen("runaway.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> L;
	for (int i = 2; i <= N; ++i) {
		ll p, w; cin >> p >> w;
		adjList[i].push_back({p, w});
		adjList[p].push_back({i, w});
	}
	LCA_precompute();

	DFS2(1, 0);
	DFS3(1, 0);

	for (int i = 1; i <= N; ++i) cout << ans[i] << '\n';

	return 0;
}