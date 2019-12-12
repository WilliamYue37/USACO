#include <bits/stdc++.h>
#include "grader.h"

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

vector<int> adjList[MAX_N];
pi loc[MAX_N];
int subTreeSize[MAX_N];
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
		for (int i = 1; i <= getN(); ++i) {
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

int dfs1(int u, int p) {
	int ret = 1;
	for (int v: adjList[u]) {
		if (v != p) {
			ret += dfs1(v, u);
		}
	}
	return subTreeSize[u] = ret;
}

void dfs2(int u, int p, int x, int y) {
	setFarmLocation(u - 1, x, y);
	loc[u] = {x, y};
	x -= subTreeSize[u];
	y -= 1;
	for (int v: adjList[u]) {
		if (v != p) {
			x += subTreeSize[v];
			dfs2(v, u, x, y);
			y -= subTreeSize[v];
		}
	}
}

void addRoad(int a, int b) {
	++a, ++b;
	adjList[a].push_back(b);
	adjList[b].push_back(a);
}

void buildFarms() {
	LCA_precompute();
	dfs1(1, -1); //subtree sizes
	dfs2(1, -1, getN(), getN()); //setFarmLocations
}

void notifyFJ(int a, int b) {
	++a, ++b;
	int lca = LCA(a, b);
	if (lca == a) {
		addBox(loc[b].ff, loc[b].ss, loc[lca].ff, loc[lca].ss);
	}
	else if (lca == b) {
		addBox(loc[a].ff, loc[a].ss, loc[lca].ff, loc[lca].ss);
	}
	else {
		if (loc[a].ff > loc[b].ff) swap(a, b);
		addBox(loc[a].ff, loc[a].ss, loc[b].ff, loc[lca].ss);
		addBox(loc[b].ff, loc[b].ss, loc[lca].ff, loc[lca].ss);
	}
}