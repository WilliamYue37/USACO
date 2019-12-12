#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define MAXN 505

typedef long long ll;
typedef pair<int, int> pi;

int N;
char grid[MAXN][MAXN];
ll dp[2][MAXN][MAXN];

int main() {
	freopen("palpath.in", "r", stdin);
	freopen("palpath.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> grid[i][j];
		}
	}

	for (int i = 0; i < N; ++i) dp[0][i][i] = 1;
	for (int len = 1; len < N; ++len) {
		for (int r1 = 0; r1 < N; ++r1) {
			int mc = N - r1 - 1; //middle column
			int c1 = mc - len;
			for (int r2 = r1; r2 < N; ++r2) {
				int c2 = mc + (len - (r2 - r1));
				//special case
				if (r2 - r1 > len) {
					int mr = (r1 + len); //middle row
					c1 = N - mr - 1;
					c2 = c1 + ((mr + len) - r2);
				}
				if (r2 - r1 + 1 > 2 * len + 1 || c1 < 0 || c1 >= N || c2 < 0 || c2 >= N || grid[r1][c1] != grid[r2][c2]) continue;
				dp[1][r1][r2] = (dp[1][r1][r2] + dp[0][r1][r2]) % MOD;
				dp[1][r1][r2] = (dp[1][r1][r2] + dp[0][r1 + 1][r2]) % MOD;
				dp[1][r1][r2] = (dp[1][r1][r2] + dp[0][r1][r2 - 1]) % MOD;
				dp[1][r1][r2] = (dp[1][r1][r2] + dp[0][r1 + 1][r2 - 1]) % MOD;
			} 
		}
		for (int r = 0; r < N; ++r) for (int c = 0; c < N; ++c) {
			dp[0][r][c] = dp[1][r][c];
			dp[1][r][c] = 0;
		}
	}

	cout << dp[0][0][N - 1] << '\n';

	return 0;
}