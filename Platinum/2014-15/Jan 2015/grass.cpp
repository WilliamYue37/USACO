#include <bits/stdc++.h>

using namespace std;

#define MAXN 100010

int N, M;
vector<int> adjList[MAXN]; //1-indexed

int counter, numOfSCCs;
vector<int> pre(MAXN, -1), low(MAXN, -1), id(MAXN, -1), sizeOfSCC(MAXN, 0), stk;
void DFSLowLink(int u) {
	pre[u] = low[u] = counter++;
	stk.push_back(u);
	for (int i = 0; i < (int)adjList[u].size(); ++i) {
		int v = adjList[u][i];
		if (pre[v] == -1) {
			DFSLowLink(v);
		}
		low[u] = min(low[u], low[v]);
	}
	if (low[u] == pre[u]) {
		while (true) {
			int j = stk.back(); stk.pop_back();
			id[j] = numOfSCCs;
			++sizeOfSCC[numOfSCCs];
			low[j] = N + 1;
			if (u == j) break;
		}
		++numOfSCCs;
	}
}

vector<int> metaGraph[MAXN], rmetaGraph[MAXN], order, rorder; //0-indexed
int dist[MAXN], rdist[MAXN], deg[MAXN], rdeg[MAXN];
queue<int> q;

int main() {
	freopen("grass.in", "r", stdin);
	freopen("grass.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int x, y; cin >> x >> y;
		adjList[x].push_back(y);
	}

	for (int i = 1; i <= N; ++i) {
		if (pre[i] == -1) {
			DFSLowLink(i);
		}
	}

	for (int u = 1; u <= N; ++u) {
		for (int j = 0; j < adjList[u].size(); ++j) {
			int v = adjList[u][j];
			if (id[u] != id[v]) {
				metaGraph[id[u]].push_back(id[v]); ++deg[id[v]];
				rmetaGraph[id[v]].push_back(id[u]); ++rdeg[id[u]];
			}
		}
	}

	fill(dist, dist + MAXN, -1);
	fill(rdist, rdist + MAXN, -1);

	//topsort
	for (int u = 0; u < numOfSCCs; ++u) {
		if (deg[u] == 0) q.push(u);
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		order.push_back(u);
		for (int i = 0; i < metaGraph[u].size(); ++i) {
			int v = metaGraph[u][i];
			--deg[v];
			if (deg[v] == 0) q.push(v);
		}
	}

	q = queue<int>();
	for (int u = 0; u < numOfSCCs; ++u) {
		if (rdeg[u] == 0) q.push(u);
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		rorder.push_back(u);
		for (int i = 0; i < rmetaGraph[u].size(); ++i) {
			int v = rmetaGraph[u][i];
			--rdeg[v];
			if (rdeg[v] == 0) q.push(v);
		}
	}

	//longest path
	dist[id[1]] = 0;
	for (int u = 0; u < numOfSCCs; ++u) {
		if (dist[order[u]] != -1) {
			for (int i = 0; i < metaGraph[order[u]].size(); ++i) {
				int v = metaGraph[order[u]][i];
				dist[v] = max(dist[v], dist[order[u]] + sizeOfSCC[v]);
			}
		}
	}

	rdist[id[1]] = 0;
	for (int u = 0; u < numOfSCCs; ++u) {
		if (rdist[rorder[u]] != -1) {
			for (int i = 0; i < rmetaGraph[rorder[u]].size(); ++i) {
				int v = rmetaGraph[rorder[u]][i];
				rdist[v] = max(rdist[v], rdist[rorder[u]] + sizeOfSCC[v]);
			}
		}
	}

	int ans = sizeOfSCC[id[1]];
	for (int u = 0; u < numOfSCCs; ++u) {
		for (int j = 0; j < metaGraph[u].size(); ++j) {
			int v = metaGraph[u][j];
			if (rdist[u] != -1 && dist[v] != -1) {
				ans = max(ans, rdist[u] + dist[v] + sizeOfSCC[id[1]]);
			}
		}
	}

	cout << ans << "\n";

	return 0;
}