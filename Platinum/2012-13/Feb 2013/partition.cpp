#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_N = 20;
const int MAX_K = 35;

int N, K;
int grid[MAX_N][MAX_N];
int prefix[MAX_N][MAX_N];

int sum(int r1, int c1, int r2, int c2) {
	++r1, ++c1, ++r2, ++c2;
	return prefix[r2][c2] - prefix[r2][c1 - 1] - prefix[r1 - 1][c2] + prefix[r1 - 1][c1 - 1];
}

bool possible(int val) {
	for (int i = 0; i < (1 << (N - 1)); ++i) {
		bool flag = false;
		int popcount = __builtin_popcount(i);
		if (popcount > K) continue;
		vector<pi> hor; int prevR = 0;
		for (int j = 0; (1 << j) <= i; ++j) {
			if (((1 << j) & i) != 0) {
				hor.push_back({prevR, j});
				prevR = j + 1;
			}
		}
		hor.push_back({prevR, N - 1});
		int left = K - popcount, prevCol = 0, col = 0;
		while (left > 0 && col < N && !flag) {
			for (int i = 0; i < hor.size(); ++i) {
				if (sum(hor[i].ff, prevCol, hor[i].ss, col) > val) {
					--left;
					if (col == prevCol) flag = true;
					prevCol = col;
					--col;
					break;
				}
			}
			++col;
		}
		for (int i = 0; i < hor.size(); ++i) {
			if (sum(hor[i].ff, prevCol, hor[i].ss, N - 1) > val) {
				flag = true;
				break;
			}
		}
		if (!flag) return true;
	}
	return false;
}

int main() {
	freopen("partition.in", "r", stdin); freopen("partition.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> grid[i][j];
		}
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			prefix[i][j] = grid[i - 1][j - 1];
			prefix[i][j] += prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
		}
	}

	int lo = 0, hi = MAX_N * MAX_N * 1000, ans = (1 << 29);
	while (lo <= hi) {
		int m = (lo + hi) / 2;
		if (possible(m)) {
			ans = m;
			hi = m - 1;
		}
		else {
			lo = m + 1;
		}
	}

	cout << ans << '\n';

	return 0;
}