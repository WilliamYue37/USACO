#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1505
#define MAXM 1505
#define MAXSIZE MAXN * MAXM

typedef long long ll;
typedef pair<int, int> ii;

struct Edge {
	int u, v;
};

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int N, M, Q, A, B;
char grid[MAXSIZE];
bool bessieReachable[MAXSIZE], reachable[MAXSIZE][4];
queue<int> q1;
queue<ii> q2; //pair stores position of box and relative position for bessie

vector<Edge> adjList[MAXSIZE]; //adjacency list for the grid
set<int> BCCs[MAXSIZE]; //the BCCs of each node in the grid
int counter, rootChildren, counterBCC; //counter = counter for DFSLowLink, rootChildren = # of children for root node, counterBCC = id for BCCs
int pre[MAXSIZE], low[MAXSIZE], parent[MAXSIZE]; //pre, low, and parent vectors for DFSLowLink
stack<Edge*> st; //stack for edges during DFSLowLink

//DFSLowLink to find data structures
void DFSLowLink(int u) {
	pre[u] = low[u] = counter++;
	for (int i = 0; i < (int)adjList[u].size(); ++i) {
		Edge* e = &adjList[u][i]; int v = e->v;
		if (pre[v] == -1) {
			parent[v] = u;
			st.push(e);
			if (pre[u] == 0) ++rootChildren;
			DFSLowLink(v);
			if ((pre[u] == 0 && rootChildren > 1) || (pre[u] != 0 && pre[u] <= low[v])) {
				while (st.top()->u != u || st.top()->v != v) {
					Edge* e = st.top(); st.pop();
					BCCs[e->u].insert(counterBCC);
					BCCs[e->v].insert(counterBCC);						
				}
				Edge* e = st.top(); st.pop();
				BCCs[e->u].insert(counterBCC);
				BCCs[e->v].insert(counterBCC);
				++counterBCC;
			}
			low[u] = min(low[u], low[v]);
		}
		else if (parent[u] != v) {
            if (pre[v] < low[u]) {
            	low[u] = pre[v];
            	st.push(e);
            }
		}
	}
}

//check if two nodes are in the same BCC
bool sameBCC(int u, int v) {
	for (int i : BCCs[u]) {
		if (BCCs[v].count(i) == 1) return true;
	}
	return false;
}

int parse1(ii rc) {
	return rc.first * M + rc.second;
}

ii parse2(int i) {
	return ii(i / M, i % M);
}

int main() {
	freopen("pushabox.in", "r", stdin);
	freopen("pushabox.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	//input
	cin >> N >> M >> Q;
	memset(pre, -1, sizeof(pre));
	memset(low, -1, sizeof(low));
	memset(parent, -1, sizeof(parent));
	for (int i = 0; i < N * M; ++i) {
		cin >> grid[i];
		if (grid[i] == 'A') {
			A = i;
			grid[i] = '.';
		}
		else if (grid[i] == 'B') {
			B = i;
		}
	}

	//convert implict graph into an adjList
	for (int u = 0; u < N * M; ++u) {
		if (grid[u] == '#') continue;
		ii rc = parse2(u);
		int r = rc.first, c = rc.second;
		for (int j = 0; j < 4; ++j) {
			int nr = r + dr[j], nc = c + dc[j], v = parse1(ii(nr, nc));
			if (nr < 0 || nr >= N || nc < 0 || nc >= M || grid[v] == '#') continue;
			adjList[u].push_back({u, v});
		}
	}

	//run DFS Low Link from all possible starting nodes
	for (int u = 0; u < N * M; ++u) {
		if (grid[u] != '#' && pre[u] == -1) {
			counter = 0, rootChildren = 0;
			DFSLowLink(u);
	    	bool emp = st.empty();
			while (!st.empty()) {
				Edge* e = st.top(); st.pop();
				BCCs[e->u].insert(counterBCC);
				BCCs[e->v].insert(counterBCC);	
			}
			if (!emp) ++counterBCC;
		}
	}

	//find all places Bessie can reach
	q1.push(A); bessieReachable[A] = true;
	while (!q1.empty()) {
		int u = q1.front(); q1.pop();
		ii rc = parse2(u);
		int r = rc.first, c = rc.second;
		for (int j = 0; j < 4; ++j) {
			int nr = r + dr[j], nc = c + dc[j], v = parse1(ii(nr, nc));
			if (nr < 0 || nr >= N || nc < 0 || nc >= M || grid[v] != '.' || bessieReachable[v]) continue;
			 q1.push(v); bessieReachable[v] = true;
		}
	}

	//compute reachable for the box
	for (int i = 0; i < 4; ++i) {
		ii rc = parse2(B);
		int nr = rc.first + dr[i], nc = rc.second + dc[i], v = parse1(ii(nr, nc));
		if (nr < 0 || nr >= N || nc < 0 || nc >= M || grid[v] == '#' || !bessieReachable[v]) continue;
		q2.push(ii(B, i)); reachable[B][i] = true;
	}

	while (!q2.empty()) {
		ii state = q2.front(); q2.pop();
		ii rc = parse2(state.first);
		int r = rc.first, c = rc.second, u = state.first, rBessie = r + dr[state.second], cBessie = c + dc[state.second], uBessie = parse1(ii(rBessie, cBessie));
		
		//case #1: bessie just pushes the box forwards
		int nr = r + dr[(state.second + 2) % 4], nc = c + dc[(state.second + 2) % 4], v = parse1(ii(nr, nc));
		if (!(nr < 0 || nr >= N || nc < 0 || nc >= M || grid[v] == '#' || reachable[v][state.second])) {
			reachable[v][state.second] = true; q2.push(ii(v, state.second));
		}

		//case #2: bessie switches sides
		for (int i = 0; i < 4; ++i) {
			int nrBessie = r + dr[i], ncBessie = c + dc[i], vBessie = parse1(ii(nrBessie, ncBessie));
			if (nrBessie < 0 || nrBessie >= N || ncBessie < 0 || ncBessie >= M || grid[vBessie] == '#' || reachable[u][i] || !sameBCC(uBessie, vBessie)) continue;
			reachable[u][i] = true; q2.push(ii(u, i));
		}
	}

	//answer queries
	for (int i = 0; i < Q; ++i) {
		int r, c; cin >> r >> c;
		--r, --c;
		int u = parse1(ii(r, c));
		bool res = false;
		for (int j = 0; j < 4; ++j) {
			res |= reachable[u][j];
		}
		res |= (u == B);
		cout << (res ? "YES" : "NO") << "\n";
	}

	return 0;
}