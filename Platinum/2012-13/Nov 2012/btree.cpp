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
const int MAX_N = 4e4 + 5;

int N, ans;
vector<int> adjList[MAX_N];
char b[MAX_N];
int parent[MAX_N], subtreeSize[MAX_N];
bool blocked[MAX_N];
queue<int> q;
map<int, int> mp[2]; //0 = '(', 1 = ')'
vector<pair<char, pi>> paths;

void calcSize(int i, int p) {
	parent[i] = p;
	subtreeSize[i] = 1;

	for (int v: adjList[i]) {
		if (v != p && !blocked[v]) {
			calcSize(v, i);
			subtreeSize[i] += subtreeSize[v];
		}
	}
}

void findPaths(int u, int p, int mini, int maxi, int pre) {
	pre += b[u] == '(' ? 1 : -1;
	mini = min(mini, pre);
	maxi = max(maxi, pre);
	for (int v: adjList[u]) {
		if (v != p && !blocked[v]) findPaths(v, u, mini, maxi, pre);
	}
	if (pre == maxi) paths.push_back({'(', {pre, maxi - mini}});
	else if (pre == mini) paths.push_back({')', {pre, maxi - mini}});
}

void solveTree(int root) {
	mp[0].clear(); mp[1].clear();
	mp[0][0] = mp[1][0] = 0;

	for (int v: adjList[root]) {
		if (!blocked[v]) {
			findPaths(v, root, 0, 0, 0);
			for (auto p: paths) {
				int pre = p.ss.ff + (b[root] == '(' ? 1 : -1);
				if (p.ff == '(' && mp[1].count(-pre)) ans = max(ans, max(p.ss.ss, mp[1][-pre]));
				else if (p.ff == ')' && mp[0].count(-pre)) ans = max(ans, max(p.ss.ss, mp[0][-pre]));
			}
			for (auto p: paths) {
				if (p.ff == '(') mp[0][p.ss.ff] = max(mp[0][p.ss.ff], p.ss.ss);
				else mp[1][p.ss.ff] = max(mp[1][p.ss.ff], p.ss.ss);
			}
			paths.clear();
		}
	}
}

void go(int entryPoint) {
	calcSize(entryPoint, entryPoint);

	int centroid = entryPoint;
	int bestSize = subtreeSize[entryPoint];

	q.push(entryPoint);
	while (!q.empty()) {
		int i = q.front(); q.pop();

		int size = subtreeSize[entryPoint] - subtreeSize[i];

		for (int v: adjList[i]) {
			if (v != parent[i] && !blocked[v]) {
				size = max(size, subtreeSize[v]);
				q.push(v);
			}
		}

		if (size < bestSize) {
			centroid = i;
			bestSize = size;
		}
	}

	solveTree(centroid);

	blocked[centroid] = true;
	for (int v: adjList[centroid]) {
		if (!blocked[v]) {
			go(v);
		}
	}
}

int main() {
	freopen("btree.in", "r", stdin); freopen("btree.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 2; i <= N; ++i) {
		int p; cin >> p;
		adjList[i].push_back(p);
		adjList[p].push_back(i);
	}
	for (int i = 1; i <= N; ++i) cin >> b[i];

	go(1);

	cout << ans << '\n';

	return 0;
}