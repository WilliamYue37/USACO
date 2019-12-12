#include <bits/stdc++.h>

using namespace std;

#define MAXN 500
#define MAXM 50005

typedef long long ll;
typedef pair<int, int> ii;

class SegmentTree {
public:
	int lo[4*MAXN+1], hi[4*MAXN+1], minimum[4*MAXN+1], delta[4*MAXN+1];

	SegmentTree() {
		init(1, 0, MAXN-1);
	}
	
	void update(int a, int b, int val) {
		update(1, a, b, val);
	}
	
	int query(int a, int b) {
		return query(1, a, b);
	}
	
	void init(int i, int a, int b) {
		lo[i] = a;
		hi[i] = b;
		
		if (a == b) 
			return;
		
		int m = (a+b)/2;
		init(2*i, a, m);
		init(2*i+1, m+1, b);
	}
	
	void update(int i, int a, int b, int val) {
		if (b < lo[i] || hi[i] < a) 
			return;
		
		if (a <= lo[i] && hi[i] <= b) {
			delta[i] += val;
			return;
		}
		
		delta[2*i] += delta[i];
		delta[2*i+1] += delta[i];
		delta[i] = 0;
		
		update(2*i, a, b, val);
		update(2*i+1, a, b, val);
		
		minimum[i] = min(minimum[2*i] + delta[2*i] * (hi[2*i] - lo[2*i] + 1), minimum[2*i+1] + delta[2*i+1] * (hi[2*+1] - lo[2*i+1] + 1));
	}
	
	int query(int i, int a, int b) {
		if (b < lo[i] || hi[i] < a) 
			return (1 << 29);
		
		if (a <= lo[i] && hi[i] <= b) {
			return minimum[i] + delta[i] * (hi[i] - lo[i] + 1);
		}
		
		//prop
		delta[2*i] += delta[i];
		delta[2*i+1] += delta[i];
		delta[i] = 0;

		//recursion
		int minLeft = query(2*i, a, b);
		int minRight = query(2*i+1, a, b);
		
		//update
		minimum[i] = min(minimum[2*i] + delta[2*i] * (hi[2*i] - lo[2*i] + 1), minimum[2*i+1] + delta[2*i+1] * (hi[2*+1] - lo[2*i+1] + 1));
		
		return min(minLeft, minRight);
	}
};

int N, M;
vector<int> adjList[MAXN];

class HeavyLight {
public:
	int parent[MAXN], heavy[MAXN], depth[MAXN], root[MAXN], treePos[MAXN];
	SegmentTree segtree;

	HeavyLight() {
		fill(heavy, heavy + MAXN, -1);
		parent[0] = -1, depth[0] = 0;
		DFS(0);
		for (int i = 0, currentPos = 0; i < N; ++i) {
			if (parent[i] == -1 || heavy[parent[i]] != i) {
				for (int j = i; j != -1; j = heavy[j]) {
					root[j] = i;
					treePos[j] = currentPos++;
				}
			}
		}
	}

	int DFS(int u) {
		int size = 1, maxSubtree = 0;
		for (int v: adjList[u]) if(v != parent[u]) {
			parent[v] = u;
			depth[v] = depth[u] + 1;
			int subtree = DFS(v);
			if (subtree > maxSubtree) {
				heavy[u] = v;
				maxSubtree = subtree;
			}
			size += subtree;
		}
		return size;
	}

	template <typename BinaryOperation>
	void processPath(int u, int v, BinaryOperation op) {
		for (; root[u] != root[v]; v = parent[root[v]]) {
			if (depth[root[u]] > depth[root[v]]) swap(u, v);
			op(treePos[root[v]], treePos[v]);
		}
		if (depth[u] > depth[v]) swap(u, v);
		op(treePos[u] + 1, treePos[v]);
	}

	void modifyPath(int u, int v, int value) {
		processPath(u, v, [this, &value](int l, int r) {segtree.update(l, r, value);});
	}

	int queryPath(int u, int v) {
		int res = 0;
		processPath(u, v, [this, &res](int l, int r) {res += segtree.query(l, r);});
		return res;
	}
};

int main() {
	//freopen("grassplant.in", "r", stdin);
	//freopen("grassplant.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> M;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v; --u, --v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	HeavyLight hld;
	for (int i = 0; i < M; ++i) {
		char c; cin >> c;
		int a, b; cin >> a >> b;
		--a, --b;
		if (c == 'P') hld.modifyPath(a, b, 1);
		else cout << hld.queryPath(a, b) << "\n";
	}

	return 0;
}