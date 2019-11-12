#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005
#define MAXLOG 20

typedef long long ll;
typedef pair<int, int> ii;

int Q, cur;
int component[MAXN];
ii diameter[MAXN];
int depth[MAXN], parent[MAXN][MAXLOG];

int lift(int u, int h) {
	for (int i = 0; (1 << i) <= h; ++i) {
		if ((h & (1 << i)) != 0) {
			u = parent[u][i];
		}
	}
	return u;
}

int LCA(int a, int b) {
	if (depth[a] < depth[b]) {
		b = lift(b, depth[b] - depth[a]);
	}
	else if (depth[b] < depth[a]) {
		a = lift(a, depth[a] - depth[b]);
	}
	if (a == b) return a;
	for (int k = MAXLOG-1; k >= 0; --k) {
		if (parent[a][k] != parent[b][k]) {
			a = parent[a][k], b = parent[b][k];
		}
	}
	return parent[a][0];
}

int dist(int a, int b) {
	int lca = LCA(a, b);
	return depth[a] + depth[b] - 2 * depth[lca];
}

int main() {
	freopen("newbarn.in", "r", stdin);
	freopen("newbarn.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> Q;
	for (int i = 0; i < Q; ++i) {
		char type; int x; cin >> type >> x;
		if (type == 'B') {
			++cur;
			if (x == -1) {
				diameter[component[cur] = cur] = ii(cur, cur);
			}
			else {
				component[cur] = component[x]; 
				depth[cur] = depth[x] + 1;
				parent[cur][0] = x;
				for (int i = 1; i < MAXLOG; ++i) {
					parent[cur][i] = parent[parent[cur][i - 1]][i - 1];
				}
			}

			int endp1 = diameter[component[cur]].first, endp2 = diameter[component[cur]].second;
			int dia = dist(endp1, endp2);
			if (dist(endp1, cur) > dia) diameter[component[cur]] = ii(endp1, cur);
			if (dist(endp2, cur) > dia) diameter[component[cur]] = ii(endp2, cur);
		}
		else {
			cout << max(dist(x, diameter[component[x]].first), dist(x, diameter[component[x]].second)) << "\n";
		}
	}




	return 0;
}