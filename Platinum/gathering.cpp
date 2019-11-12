#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define MAXN 100005

typedef long long ll;
typedef pair<int, int> pi;

int N, M;
vector<int> adjList[MAXN], adjList2[MAXN];
int degree[MAXN], degree2[MAXN];
bool removed[MAXN], ans[MAXN];
queue<int> q;

int main() {
	freopen("gathering.in", "r", stdin);
	freopen("gathering.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;
	for (int i = 0; i < N - 1; ++i) {
		int x, y; cin >> x >> y;
		adjList[x].push_back(y);
		adjList[y].push_back(x);
		++degree[x], ++degree[y];
	}

	for (int i = 0; i < M; ++i) {
		int a, b; cin >> a >> b;
		adjList2[a].push_back(b);
		++degree2[b];
	}

	for (int i = 1; i <= N; ++i) {
		if (degree[i] <= 1 && degree2[i] == 0) {
			q.push(i);
			removed[i] = true;
		}
	}

	int nodesLeft = N;
	while (!q.empty() && nodesLeft > 1) {
		int u = q.front(); q.pop();
		--nodesLeft;
		for (int v: adjList[u]) {
			--degree[v];
			if (degree[v] <= 1 && degree2[v] == 0 && !removed[v]) {
				q.push(v);
				removed[v] = true;
			}
		}
		for (int v: adjList2[u]) {
			--degree2[v];
			if (degree[v] <= 1 && degree2[v] == 0 && !removed[v]) {
				q.push(v);
				removed[v] = true;
			}
		}
	}

	if (nodesLeft != 1) {
		for (int i = 0; i < N; ++i) cout << 0 << '\n';
		return 0;
	}

	int final = q.front();
	q = queue<int>();
	q.push(final); ans[final] = true;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v: adjList[u]) {
			if (!ans[v] && adjList2[v].size() == 0) {
				ans[v] = true;
				q.push(v);
			}
		}
	}

	for (int i = 1; i <= N; ++i) {
		cout << (ans[i] ? 1 : 0) << '\n';
	}

	return 0;
}