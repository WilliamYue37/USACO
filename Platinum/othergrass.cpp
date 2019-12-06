#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const int INF = 1e9;
const double EPS = 1e-6;
const int MAX_N = 2e5 + 5;

struct Edge {
	int u, v, w;
	bool operator < (const Edge &e) const {return this->w < e.w;}
};

struct DSU {
	int numOfComponents;
	vector<int> parent, rank, size;

	DSU() {}

	DSU(int n) {
		parent.resize(n + 1); rank.resize(n + 1); size.resize(n + 1);
		numOfComponents = n;
		for (int i = 1; i <= n; ++i) {
			parent[i] = i;
			rank[i] = 0;
			size[i] = 1;
		}
	}

	int find(int a) {
		return parent[a] == a ? a : (parent[a] = find(parent[a]));
	}

	void unionSet(int a, int b) {
		a = find(a); b = find(b);
		if (rank[a] > rank[b]) {
			parent[b] = parent[a];
			size[a] += size[b];
		}
		else {
			parent[a] = parent[b];
			size[b] += size[a];
		}
		if (rank[a] == rank[b]) ++rank[b];
		--numOfComponents;
	}
};

int min1(multiset<int>& s) {
	if (s.size() < 1) return INF;
	return *(s.begin());
}

int N, M, K, Q;
vector<Edge> edges;
vector<pi> adjList[MAX_N];
int color[MAX_N], parent[MAX_N], edgeUp[MAX_N];
map<int, multiset<int>> mp[MAX_N];
multiset<int> ans, mini[MAX_N];

void MST() { //returns -1 if a MST is not possible
	DSU dsu(N);
	sort(edges.begin(), edges.end());
	for (int i = 0; i < edges.size() && dsu.numOfComponents > 1; ++i) {
		int u = edges[i].u, v = edges[i].v, w = edges[i].w;
		if (dsu.find(u) != dsu.find(v)) {
			adjList[u].push_back({v, w});
			adjList[v].push_back({u, w});
			dsu.unionSet(u, v);
		}
	}
}

void DFS(int u, int p) {
	parent[u] = p;
	for (pi edge: adjList[u]) {
		int v = edge.ff, w = edge.ss;
		if (v == p) continue;
		edgeUp[v] = w;
		if (color[u] != color[v]) {
			ans.erase(ans.find(min1(mini[u])));
			if (mp[u][color[v]].size() > 0) mini[u].erase(mini[u].find(min1(mp[u][color[v]])));
		}
		mp[u][color[v]].insert(w);
		if (color[u] != color[v]) {
			mini[u].insert(min1(mp[u][color[v]]));
			ans.insert(min1(mini[u]));
		}
		DFS(v, u);
	}
}

int main() {
	freopen("grass.in", "r", stdin); freopen("grass.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M >> K >> Q;
	for (int i = 0; i < M; ++i) {
		int u, v, w; cin >> u >> v >> w;
		edges.push_back({u, v, w});
	}
	for (int i = 1; i <= N; ++i) {
		cin >> color[i];
		ans.insert(INF);
	}

	MST();

	// init
	edgeUp[1] = INF;
	DFS(1, 0);

	for (int i = 0; i < Q; ++i) {
		int u, c; cin >> u >> c;
		int old_c = color[u];

		// parent
		int p = parent[u];
		if (p != 0) {
			// delete from high to low
			ans.erase(ans.find(min1(mini[p])));
			if (old_c != color[p]) mini[p].erase(mini[p].find(min1(mp[p][old_c])));
			if (c != color[p] && mp[p].count(c) > 0) mini[p].erase(mini[p].find(min1(mp[p][c])));

			mp[p][old_c].erase(mp[p][old_c].find(edgeUp[u]));
			if (mp[p][old_c].size() == 0) mp[p].erase(old_c);
			mp[p][c].insert(edgeUp[u]);

			// rebuild from low to high
			if (old_c != color[p] && mp[p].count(old_c) > 0) mini[p].insert(min1(mp[p][old_c]));
			if (c != color[p]) mini[p].insert(min1(mp[p][c]));	
			ans.insert(min1(mini[p]));
		}

		// children - only have to update things regarding old color and new color if they are different
		if (old_c != c) {
			// erase old color
			ans.erase(ans.find(min1(mini[u])));
			if (mp[u].count(old_c) > 0) mini[u].insert(min1(mp[u][old_c]));
			if (mp[u].count(c) > 0) mini[u].erase(mini[u].find(min1(mp[u][c])));
			// update new color
			ans.insert(min1(mini[u]));
		}

		// change color
		color[u] = c;

		cout << min1(ans) << '\n';
	}

	return 0;
}