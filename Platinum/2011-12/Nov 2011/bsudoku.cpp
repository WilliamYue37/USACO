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

int grid[9][9], start[9], popcount[1 << 9];
int dp[9][1 << 9][2][2][2];

int cost(int orig, int change) {
	int ret = 0;
	for (int i = 0; i < 9; ++i) {
		if (((1 << i) & orig) != ((1 << i) & change)) ++ret;
	}
	return ret;
}

int main() {
	//freopen("bsudoku.in", "r", stdin); freopen("bsudoku.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	for (int i = 0; i < 9; ++i) {
		string s; cin >> s;
		for (int j = 0; j < 9; ++j) {
			if (s[j] == '1') grid[i][j] = 1;
		}
	}

	for (int i = 0; i < 9; ++i) {
		int mask = 0;
		for (int j = 0; j < 9; ++j) {
			if (grid[i][j] == 1) {
				mask |= (1 << j);
			}
		}
		start[i] = mask;
	}

	for (int i = 0; i < 9; ++i) {
		for (int mask = 0; mask < (1 << 9); ++mask) {
			for (int first: {0, 1}) {
				for (int second: {0, 1}) {
					for (int third: {0, 1}) {
						dp[i][mask][first][second][third] = 1e9;
					}
				}
			}
		}
	}

	for (int mask = 0; mask < (1 << 9); ++mask) {
		popcount[mask] = __builtin_popcount(mask);
		if (popcount[mask] % 2 == 0) {
			int f = __builtin_popcount(7 & mask) % 2;
			int s = __builtin_popcount((7 << 3) & mask) % 2;
			int t = __builtin_popcount((7 << 6) & mask) % 2;
			dp[0][mask][f][s][t] = cost(start[0], mask);
		}
	}

	for (int i = 0; i < 8; ++i) {
		for (int mask = 0; mask < (1 << 9); ++mask) {
			for (int f: {0, 1}) {
				for (int s: {0, 1}) {
					for (int t: {0, 1}) {
						for (int new_mask = 0; new_mask < (1 << 9); ++new_mask) {
							if (popcount[new_mask] % 2 != 0) continue;
							int res_mask = new_mask ^ mask;
							int new_f = f ^ (popcount[7 & new_mask] % 2);
							int new_s = s ^ (popcount[(7 << 3) & new_mask] % 2);
							int new_t = t ^ (popcount[(7 << 6) & new_mask] % 2);
							if (i % 3 == 1 && (new_f != 0 || new_s != 0 || new_t != 0)) continue;
							dp[i + 1][res_mask][new_f][new_s][new_t] = min(dp[i + 1][res_mask][new_f][new_s][new_t], dp[i][mask][f][s][t] + cost(start[i + 1], new_mask));
						}
					}
				} 
			}
		}
	}

	cout << dp[8][0][0][0][0] << '\n';

	return 0;
}