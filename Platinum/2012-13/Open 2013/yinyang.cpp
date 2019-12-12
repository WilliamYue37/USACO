#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001
#define OFFSET 100000

typedef pair<int, int> ii;
typedef long long ll;

struct Path {
	int w;
	bool t;
};

int N;
vector<ii> adjList[MAXN];
int parent[MAXN], subtreeSize[MAXN];
bool blocked[MAXN];
queue<int> q;

void calcSize(int i, int p) {
	parent[i] = p;
	subtreeSize[i] = 1;

	for (ii e: adjList[i]) {
		if (e.first != p && !blocked[e.first]) {
			calcSize(e.first, i);
			subtreeSize[i] += subtreeSize[e.first];
		}
	}
}

int depthSeen[2 * MAXN];
vector<Path> pathList;
void findPaths(int i, int p, int sum) {
	pathList.push_back({sum`, depthSeen[sum + OFFSET] > 0});

	++depthSeen[sum + OFFSET];

	for (ii e: adjList[i]) {
		if (e.first == p) continue;
		if (blocked[e.first]) continue;

		findPaths(e.first, i, e.second + sum);
	}

	--depthSeen[sum + OFFSET];
}

int pathSat[2 * MAXN], pathUnsat[2 * MAXN];
ll solveTree(int root, int compSize) {
	for (int i = OFFSET - compSize - 1; i <= OFFSET + compSize - 1; ++i) {
		pathSat[i] = 0;
		pathUnsat[i] = 0;
	}

	ll res = 0;

	for (ii e: adjList[root]) {
		if (blocked[e.first]) continue;
		pathList.clear();
		findPaths(e.first, root, e.second);
		for (Path p: pathList) {
			//count # of paths ending at p
			if (p.t || p.w == 0) {
				res += pathUnsat[OFFSET - p.w];
			}
			res += pathSat[OFFSET - p.w];

			if (p.w == 0 && p.t) {
				++res;
			}
		}

		for (Path p: pathList) {
			if (p.t) {
				++pathSat[p.w + OFFSET];
			}
			else {
				++pathUnsat[p.w + OFFSET];
			}
		}
	}

	return res;
}

ll go(int entryPoint) {
	calcSize(entryPoint, entryPoint);

	int centroid = entryPoint;
	int bestSize = subtreeSize[entryPoint];

	int compSize = 0;
	q.push(entryPoint);
	while (!q.empty()) {
		int i = q.front(); q.pop();
		++compSize;

		int size = subtreeSize[entryPoint] - subtreeSize[i];

		for (ii e: adjList[i]) {
			if (e.first != parent[i] && !blocked[e.first]) {
				size = max(size, subtreeSize[e.first]);
				q.push(e.first);
			}
		}

		if (size < bestSize) {
			centroid = i;
			bestSize = size;
		}
	}

	ll ways = solveTree(centroid, compSize);

	blocked[centroid] = true;
	for (ii e: adjList[centroid]) {
		if (!blocked[e.first]) {
			ways += go(e.first);
		}
	}

	return ways;
}

int main() {
	freopen("yinyang.in", "r", stdin);
	freopen("yinyang.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N - 1; ++i) {
		int a, b, t; cin >> a >> b >> t;
		t = 2 * t - 1;
		adjList[a].push_back(ii(b, t));
		adjList[b].push_back(ii(a, t));
	}

	ll res = go(1);

	cout << res << "\n";

	return 0;
}