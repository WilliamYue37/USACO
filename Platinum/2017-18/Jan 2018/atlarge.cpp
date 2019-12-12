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
const int MAX_N = 7e4 + 1;
const int MAX_BLOCK = 265;

int block(int i) {return i/MAX_BLOCK;}

int N, g_delta;
vector<int> adjList[MAX_N];
int depth[MAX_N], leaf[MAX_N], ans[MAX_N], preorder[MAX_N], delta[MAX_BLOCK];
int startRange[MAX_N], endRange[MAX_N];
int bit[MAX_BLOCK][MAX_N << 1];

int query(int b, int index) {
	index += MAX_N; int sum = 0;
	while (index > 0) {
		sum += bit[b][index];
		index -= index & -index;
	}
	return sum;	
}

void update(int b, int index, int val) {
	index += MAX_N;
	while (index <= (MAX_N << 1)) {
		bit[b][index] += val;
		index += index & -index;
	}	
}

int id = 0;
int dfs1(int u, int p, int d) {
	leaf[u] = MAX_N + 1;
	depth[u] = d;
	startRange[u] = id++;
	preorder[startRange[u]] = u;
	for (int v: adjList[u]) {
		if (v != p) leaf[u] = min(leaf[u], dfs1(v, u, d + 1) + 1);
	}
	endRange[u] = id - 1;
	if (adjList[u].size() == 1) leaf[u] = 0;
	return leaf[u];
}

void dfs2(int u, int p) {
	if (p != -1) leaf[u] = min(leaf[u], leaf[p] + 1);
	for (int v: adjList[u]) if (v != p) dfs2(v, u);
}

void destory(int l, int r) {
	for (int i = l; i <= r; ++i) {
		int u = preorder[i];
		update(block(i), leaf[u] - depth[u], -(2 - adjList[u].size()));
	}
}

void build(int l, int r) {
	for (int i = l; i <= r; ++i) {
		int u = preorder[i];
		update(block(i), leaf[u] - depth[u], (2 - adjList[u].size()));
	}
}

void updateBlocks(int l, int r, int val) {
	int i_l = l, i_r = r, b_l = block(l), b_r = block(r);
	if (b_l == b_r) {
		destory(i_l, i_r);
		while (l <= r) leaf[preorder[l++]] += val;
		build(i_l, i_r);
		return;
	}
	destory(i_l, b_l * MAX_BLOCK + MAX_BLOCK - 1);
	destory(b_r * MAX_BLOCK, i_r);
	while (l != (b_l + 1) * MAX_BLOCK) leaf[preorder[l++]] += val;
	while (r != b_r * MAX_BLOCK - 1) leaf[preorder[r--]] += val;
	build(i_l, b_l * MAX_BLOCK + MAX_BLOCK - 1);
	build(b_r * MAX_BLOCK, i_r);
	for (int i = b_l + 1; i < b_r; ++i) delta[i] += val;
}

void solve(int u, int p) {
	for (int i = 0; i < MAX_BLOCK; ++i) {
		ans[u] += query(i, -delta[i] - g_delta);
	}
	for (int v: adjList[u]) {
		if (v != p) {
			updateBlocks(startRange[v], endRange[v], 2);
			--g_delta;
			solve(v, u);
			++g_delta;
			updateBlocks(startRange[v], endRange[v], -2);
		}
	}
}

int main() {
	freopen("atlarge.in", "r", stdin); freopen("atlarge.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	dfs1(1, 0, 0);
	dfs2(1, -1);
	
	// init
	for (int u = 1; u <= N; ++u) {
		update(block(startRange[u]), leaf[u] - depth[u], 2 - adjList[u].size());
	}

	solve(1, -1);

	for (int i = 1; i <= N; ++i) cout << (adjList[i].size() == 1 ? 1 : ans[i]) << '\n';

	return 0;
}