#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-6;
const int MAX_N = 301;

int N;
int memo[MAX_N][MAX_N];
short grid[MAX_N][MAX_N], max_up[MAX_N][MAX_N][MAX_N], max_down[MAX_N][MAX_N][MAX_N];

int solve(int r, int i, int j) {
	if (i + 1 == j) return 0;
	if (memo[i][j] != -1) return memo[i][j];
	return memo[i][j] = max({solve(r, i + 1, j), solve(r, i, j - 1), (max_up[i][j][r] - 2) * (j - i - 1)});
}

int main() {
	freopen("eight.in", "r", stdin); freopen("eight.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		string line; cin >> line;
		for (int j = 1; j <= N; ++j) {
			if (line[j - 1] == '*') grid[i][j] = 1;
			grid[i][j] += grid[i][j - 1];
		}
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			int cur = 0;
			for (int k = 1; k <= N; ++k) {
				if (cur != 0 || grid[k][j] - grid[k][i - 1] == 0) ++cur;
				if (grid[k][i] - grid[k][i - 1] != 0 || grid[k][j] - grid[k][j - 1] != 0) cur = 0;
				if (grid[k][j] - grid[k][i - 1] == 0) max_up[i][j][k] = cur;
			}
			cur = 0;
			for (int k = N; k >= 1; --k) {
				if (cur != 0 || grid[k][j] - grid[k][i - 1] == 0) ++cur;
				if (grid[k][i] - grid[k][i - 1] != 0 || grid[k][j] - grid[k][j - 1] != 0) cur = 0;
				if (grid[k][j] - grid[k][i - 1] == 0) max_down[i][j][k] = cur;
			}
		}
	}

	int ans = 0;
	for (int k = 1; k <= N; ++k) {
		memset(memo, -1, sizeof memo);
		for (int i = 1; i <= N; ++i) {
			for (int j = i + 2; j <= N; ++j) {
				if (grid[k][j] - grid[k][i - 1] == 0) ans = max(ans, (max_down[i][j][k] - 2) * (j - i - 1) * solve(k, i, j));
			}
		}
	}

	cout << (ans == 0 ? -1 : ans) << '\n';

	return 0;
}