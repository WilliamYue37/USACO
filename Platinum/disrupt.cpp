#include <bits/stdc++.h>

using namespace std;

#define MAXN 50005
#define MAXM 50005

typedef long long ll;
typedef pair<int, int> ii;

int N, M;
vector<ii> adjList[MAXN];
vector<int> endpoints[MAXN];
int res[MAXN];

set<int>* solve(int u, int p) {
	set<int>* pq = new set<int>();
	for (ii e: adjList[u]) {
		if (e.first != p) {
			set<int>* subtree = solve(e.first, u);
			res[e.second] = (subtree->size() == 0 ? -1 : *subtree->begin());
			if (pq->size() >= subtree->size()) {
				for (int i: *subtree) {
					if (pq->count(i) == 0) {
						pq->insert(i);
					}
					else {
						pq->erase(i);
					}
				}
			}
			else {
				for (int i: *pq) {
					if (subtree->count(i) == 0) {
						subtree->insert(i);
					}
					else {
						subtree->erase(i);
					}
				}
				pq = subtree;
			}
		}
	}

	for (int i: endpoints[u]) {
		if (pq->count(i) == 0) {
			pq->insert(i);
		}
		else {
			pq->erase(i);
		}
	}

	return pq;
}

int main() {
	freopen("disrupt.in", "r", stdin);
	freopen("disrupt.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> M; 
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adjList[u].push_back(ii(v, i));
		adjList[v].push_back(ii(u, i));
	}

	for (int i = 0; i < M; ++i) {
		int u, v, w; cin >> u >> v >> w;
		endpoints[u].push_back(w);
		endpoints[v].push_back(w);
	}

	solve(1, -1);

	for (int i = 0; i < N - 1; ++i) {
		cout << res[i] << endl;
	}

	return 0;
}