#include <bits/stdc++.h>

using namespace std;

#define MAXNM 250010 //max N * M

struct Edge {
	int u, v, w;

	bool operator < (const Edge &e) const {
		return this->w < e.w;
	}
};

int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

int N, M, T;
int elevation[MAXNM];
vector<Edge> edges;
int ranks[MAXNM], parent[MAXNM], start[MAXNM], setSize[MAXNM];

int find(int a) {
	return parent[a] == a ? a : (parent[a] = find(parent[a]));
}

void unionSet(int a, int b) {
	a = find(a);
	b = find(b);

	if (ranks[a] > ranks[b]) {
		parent[b] = parent[a];
		start[a] += start[b];
		setSize[a] += setSize[b];
	}
	else {
		parent[a] = parent[b];
		start[b] += start[a];
		setSize[b] += setSize[a];
	}
	if (ranks[a] == ranks[b]) {
		++ranks[b];
	}
}

int main() {
	freopen("skilevel.in", "r", stdin); freopen("skilevel.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> N >> M >> T;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> elevation[i * M + j];
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			int v; cin >> v;
			start[i * M + j] = (v == 1 ? 1 : 0);
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			for (int k = 0; k < 4; ++k) {
				int nr = i + dr[k], nc = j + dc[k];
				if (nr < 0 || nr >= N || nc < 0 || nc >= M) {
					continue;
				}
				edges.push_back({ i * M + j, nr * M + nc, abs(elevation[i * M + j] - elevation[nr * M + nc]) });
			}
		}
	}
	sort(edges.begin(), edges.end());

	for (int i = 0; i < N * M; ++i) {
		parent[i] = i;
	}
	fill(setSize, setSize + N * M, 1);

	long ans = 0;
	for (int i = 0; i < edges.size(); ++i) {
		int u = edges[i].u, v = edges[i].v, w = edges[i].w;
		if (find(u) != find(v)) {
			unionSet(u, v);
			if (setSize[find(u)] >= T) {
				ans += (long)w * start[find(u)];
				start[find(u)] = 0;
			}
		}
	}

	cout << ans << "\n";

	return 0;
}