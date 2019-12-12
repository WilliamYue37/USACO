#include <bits/stdc++.h>

using namespace std;

#define MAXN 300

typedef pair<int, int> ii;

int N, M;
vector<int> adjList[MAXN];
int adjMatrix[MAXN][MAXN];
int prevNode[MAXN];

int dist[MAXN];
int dijkstra(bool record) {
	priority_queue<ii> pq;
	fill(dist, dist + MAXN, (1 << 29));
	pq.push(ii(0, 1));
	dist[1] = 0;

	while (!pq.empty()) {
		int u = pq.top().second, d = pq.top().first; pq.pop();
		if (d > dist[u]) continue;
		for (int v : adjList[u]) {
			if (dist[u] + adjMatrix[u][v] < dist[v]) {
				pq.push(ii(dist[u] + adjMatrix[u][v], v));
				dist[v] = dist[u] + adjMatrix[u][v];
				if (record) prevNode[v] = u;
			}
		}
	}

	return dist[N];
}

int solve(int u) {
	if (prevNode[u] == -1) return -1;
	int v = prevNode[u], d = adjMatrix[u][v];
	adjMatrix[u][v] = d * 2;
	adjMatrix[v][u] = d * 2;
	int ans = dijkstra(false);
	adjMatrix[u][v] = d;
	adjMatrix[v][u] = d;
	return max(ans, solve(v));
}

int main() {
	freopen("rblock.in", "r", stdin);
	freopen("rblock.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j <= N; ++j) {
			adjMatrix[i][j] = (1 << 29);
		}
	}
	for (int i = 0; i < M; ++i) {
		int a, b, l; cin >> a >> b >> l;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
		adjMatrix[a][b] = l;
		adjMatrix[b][a] = l;
	}
	memset(prevNode, -1, sizeof(prevNode));

	int dijk = dijkstra(true);

	cout << solve(N) - dijk << "\n";

	return 0;
}