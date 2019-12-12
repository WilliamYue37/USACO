#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = INT_MAX;
const double EPS = 1e-6;
const int MAX_L = 255;

struct Line {
	int x1, y1, x2, y2;
};

int N;
const int NIL = 0; //NOT in list
//L and R are the sizes of the left and right sides of a bipartite graph, respectively
//pairL stores pair of u in the matching where u is a vertex on the left side, pairR does the same thing
//dist[u] stores the distances of the left side vertices, dist[u] is one more than dist[u'] if u is next to u' in the augmenting path
//adjList stores the adjacents of the left side vertex u, u ranges from 1 - L, 0 (NIL) is used as a dummy vertex
//nodes have to be 1-indexed, nodes in L have to be labeled 1 - L, nodes in R have to be labeled 1 - R
int L, R;
vector<int> pairL, pairR, dist, adjList[MAX_L];
bool BFS() { //returns true if there is an augmenting path, else returns false
	queue<int> q;
	for (int u = 1; u <= L; ++u) {
		if (pairL[u] == NIL) {
			dist[u] = 0;
			q.push(u);
		}
		else dist[u] = INF;
	}

	dist[NIL] = INF;

	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (dist[u] < dist[NIL]) {
			for (int v: adjList[u]) {
				if (dist[pairR[v]] == INF) {
					dist[pairR[v]] = dist[u] + 1;
					q.push(pairR[v]);
				}
			}
		}
	}

	return dist[NIL] != INF;
}

bool DFS(int u) { //returns true if there is an augmenting path beginning with free vertex u
	if (u != NIL) {
		for (int v: adjList[u]) {
			if (dist[pairR[v]] == dist[u] + 1) {
				if (DFS(pairR[v])) {
					pairR[v] = u;
					pairL[u] = v;
					return true;
				}
			}
		}
		
		dist[u] = INF;
		return false;
	}

	return true;
}

int hopcroftKarp() { //returns the size of maximum matching
	//initialize pairL and pairR to NIL
	pairL.resize(L + 1);
	pairR.resize(R + 1);
	dist.resize(L + 1);

	int res = 0;
	while (BFS()) { //continue updating matching while there still is an augmenting path
		for (int u = 1; u <= L; ++u) {
			if (pairL[u] == NIL && DFS(u)) ++res;
		}
	}

	return res;
}

int main() {
	//freopen("steeple.in", "r", stdin); freopen("steeple.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	vector<Line> ver, hor;
	for (int i = 0; i < N; ++i) {
		Line line; cin >> line.x1 >> line.y1 >> line.x2 >> line.y2;
		if (line.x1 > line.x2) swap(line.x1, line.x2);
		if (line.y1 > line.y2) swap(line.y1, line.y2);
		if (line.x1 == line.x2) ver.push_back(line);
		else hor.push_back(line);
	}

	L = ver.size();
	R = hor.size();

	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < R; ++j) {
			if (hor[j].x1 <= ver[i].x1 && ver[i].x1 <= hor[j].x2 && ver[i].y1 <= hor[j].y1 && hor[j].y1 <= ver[i].y2) {
				adjList[i + 1].push_back(j + 1);
			}
		}
	}

	cout << N - hopcroftKarp() << '\n';

	return 0;
}