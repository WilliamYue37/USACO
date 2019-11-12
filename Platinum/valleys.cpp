#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_N = 755;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int dr2[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc2[] = {0, 1, 1, 1, 0, -1, -1, -1};

class DSU {
public:
	int numOfComponents;
	vector<int> parent, rank, size, holes;

	DSU() {}

	DSU(int n) {
		parent.resize(n); rank.resize(n); size.resize(n); holes.resize(n);
		numOfComponents = n;
		for (int i = 0; i < n; ++i) {
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
			holes[a] += holes[b];
		}
		else {
			parent[a] = parent[b];
			size[b] += size[a];
			holes[b] += holes[a];
		}
		if (rank[a] == rank[b]) ++rank[b];
		--numOfComponents;
	}
};

int N;
int heights[MAX_N * MAX_N], cells[MAX_N * MAX_N];
DSU dsu1, dsu2;

int hsh(int r, int c) {return r * N + c;}
pi unhsh(int hsh) {return {hsh / N, hsh % N};}

int main() {
	freopen("valleys.in", "r", stdin); freopen("valleys.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> heights[hsh(i, j)];
			cells[hsh(i, j)] = hsh(i, j);
		}
	}
	sort(cells, cells + N * N, [](int a, int b) {return heights[a] < heights[b];});

	dsu1 = DSU(N * N + 1);
	int numHoles[N * N + 1]; numHoles[N * N] = 0;
	for (int i = N * N - 1; i >= 0; --i) {
		numHoles[i] = numHoles[i + 1] + 1;
		int r = unhsh(cells[i]).ff, c = unhsh(cells[i]).ss;
		for (int j = 0; j < 8; ++j) {
			int nr = r + dr2[j], nc = c + dc2[j];
			int loc = 0 <= nr && nr < N && 0 <= nc && nc < N ? hsh(nr, nc) : N * N;
			if (dsu1.find(cells[i]) != dsu1.find(loc) && (loc == N * N || heights[cells[i]] < heights[loc])) {
				--numHoles[i];
				dsu1.unionSet(cells[i], loc);
			}
		}
	}

	dsu2 = DSU(N * N);
	ll ans = 0;
	for (int i = 0; i < N * N; ++i) {
		int r = unhsh(cells[i]).ff, c = unhsh(cells[i]).ss, h = heights[cells[i]];
		for (int j = 0; j < 4; ++j) {
			int nr = r + dr[j], nc = c + dc[j];
			int loc = hsh(nr, nc);
			if (nr < 0 || nr >= N || nc < 0 || nc >= N || heights[loc] > h) continue;
			if (dsu2.find(loc) != dsu2.find(cells[i])) dsu2.unionSet(loc, cells[i]);
		}
		dsu2.holes[dsu2.find(cells[i])] += numHoles[i + 1] - numHoles[i];
		if (dsu2.holes[dsu2.find(cells[i])] == 0) ans += dsu2.size[dsu2.find(cells[i])];
	}

	cout << ans << '\n';

	return 0;
}