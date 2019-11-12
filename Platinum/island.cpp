#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const int INF = (1 << 29);
const double EPS = 1e-6;
const int MAX_N = 16;
const int MAX_SZ = 55;

int dr[] = {-1, 0, 1, 0, -1, 1, 1, -1};
int dc[] = {0, 1, 0, -1, 1, 1, -1, -1};

int R, C, id = 0;
char grid[MAX_SZ][MAX_SZ];
int island[MAX_SZ][MAX_SZ], dist[MAX_SZ][MAX_SZ], adjMat[MAX_N][MAX_N], dp[1 << MAX_N][MAX_N];

void floodFill(int r, int c) {
	island[r][c] = id;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i], nc = c + dc[i];
		if (nr < 0 || nr >= R || nc < 0 || nc >= C || grid[nr][nc] != 'X' || island[nr][nc] != -1) continue;
		floodFill(nr, nc);
	}
}

void BFS(int start) {
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) dist[i][j] = INF;

	queue<pair<pi, int>> q;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (island[i][j] == start) {
				dist[i][j] = 0;
				q.push({{i, j}, 0});
			}
		}
	}
	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		int r = cur.ff.ff, c = cur.ff.ss, d = cur.ss;
		if (d > dist[r][c]) continue;
		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr < 0 || nr >= R || nc < 0 || nc >= C || grid[nr][nc] == '.') continue;
			int nd = d + (grid[nr][nc] == 'S' ? 1 : 0);
			if (nd >= dist[nr][nc]) continue;
			dist[nr][nc] = nd;
			q.push({{nr, nc}, nd});
		}
	}

	for (int i = 0; i < R; ++i) { 
		for (int j = 0; j < C; ++j) {
			int island_id = island[i][j];
			if (island_id < 0 || island_id >= id) continue;
			adjMat[start][island_id] = dist[i][j];
		}
	}
}

int main() {
	freopen("island.in", "r", stdin); freopen("island.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> R >> C;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			cin >> grid[i][j];
		}
	}

	//flood fill
	memset(island, -1, sizeof island);
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (island[i][j] == -1 && grid[i][j] == 'X') {
				floodFill(i, j);
				++id;
			}
		}
	}

	//BFS to build graph
	for (int i = 0; i < id; ++i) BFS(i);

	for (int i = 1; i < (1 << id); ++i) for (int j = 0; j < id; ++j) dp[i][j] = INF;
	for (int mask = 0; mask < (1 << id); ++mask) {
		for (int i = 0; i < id; ++i) {
			if (((1 << i) & mask) == 0) continue;
			for (int j = 0; j < id; ++j) {
				if (((1 << j) & mask) == 0) continue;
				int n_mask = ((~(1 << j)) & mask);
				dp[mask][j] = min(dp[mask][j], dp[n_mask][i] + adjMat[i][j]);
			}
		}
	}

	int ans = INF;
	for (int i = 0; i < id; ++i) ans = min(ans, dp[(1 << id) - 1][i]);
	cout << ans << '\n';

	return 0;
}