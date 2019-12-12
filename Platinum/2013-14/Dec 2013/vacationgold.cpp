#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define INF 1000000000000000000LL
#define MAXN 20005

typedef long long ll;
typedef pair<int, ll> pi;

int N, M, K, Q;
vector<pi> adjList[MAXN], rAdjList[MAXN];
map<int, vector<ll>> hubs;

vector<ll> dijkstra(int start) {
	vector<ll> dist(MAXN, (1LL << 50));
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({start, 0LL}); //u, dist
	dist[start] = 0LL;
	while (!pq.empty()) {
		int u = pq.top().first, d = pq.top().second; pq.pop();
		if (d > dist[u]) continue;
		for (auto edge : adjList[u]) {
			int v = edge.first; ll w = edge.second;
			if (dist[u] + w < dist[v]) {
				pq.push({v, dist[u] + w});
				dist[v] = dist[u] + w;
			}
		}
	}
	return dist;
}

int main() {
	freopen("vacationgold.in", "r", stdin);
	freopen("vacationgold.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M >> K >> Q;
	for (int i = 0; i < M; ++i) {
		int u, v, d; cin >> u >> v >> d;
		adjList[u].push_back({v, d});
		rAdjList[v].push_back({u, d});
	}
	for (int i = 0; i < K; ++i) {
		int hub; cin >> hub;
		hubs[hub] = dijkstra(hub);
	}

	int count = 0; ll ans = 0;
	for (int i = 0; i < Q; ++i) {
		int a, b; cin >> a >> b;
		ll cost = (1LL << 50);
		if (hubs.count(a) == 0) {
			for (auto edge: adjList[a]) {
				int v = edge.ff; ll w = edge.ss;
				cost = min(cost, hubs[v][b] + w);
			}
		}
		else cost = hubs[a][b];

		if (cost != (1LL << 50)) ++count, ans += cost;
	}

	cout << count << '\n' << ans << '\n';

	return 0;
}