#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define MAXR 755
#define MAXC 755
#define MAXRC 562505

typedef long long ll;
typedef pair<int, int> pi;

int R, C, K, grid[755][755];
set<int> columnsWithColor[MAXRC];
vector<int> bit[MAXRC];
map<int, int> compress[MAXRC];

int query(int color, int index) {
	int sum = 0;
	while (index > 0) {
		sum = (sum + bit[color][index]) % MOD;
		index -= index & -index;
	}
	return sum;
}

void update(int color, int index, int val) {
	while (index < bit[color].size()) {
		bit[color][index] = (bit[color][index] + val) % MOD;
		index += index & -index;
	}
}

int main() {
	freopen("hopscotch.in", "r", stdin);
	freopen("hopscotch.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> R >> C >> K;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			cin >> grid[i][j];
			columnsWithColor[grid[i][j]].insert(j);
		}
	}

	for (int i = 0; i < MAXR; ++i) bit[0].push_back(0);
	for (int i = 1; i <= K; ++i) {
		int idx = 1; bit[i].push_back(0);
		for (int j: columnsWithColor[i]) {
			compress[i][j] = idx++;
			bit[i].push_back(0);
		}
	}

	for (int i = R - 1; i >= 0; --i) {
		for (int j = 0; j < C; ++j) {
			int ret = 0;
			if (i != R - 1 || j != C - 1) {
				ret = (ret + query(0, C - 1) - query(0, j) + MOD) % MOD;
				ret = (ret - (query(grid[i][j], bit[grid[i][j]].size() - 1) - query(grid[i][j], compress[grid[i][j]][j]) + MOD) % MOD + MOD) % MOD;
			}
			else ret = 1;
			update(grid[i][j], compress[grid[i][j]][j], ret);
			if (j != 0) update(0, j, ret);
			else if (i == 0) cout << ret << '\n';
		}
	}

	return 0;
}