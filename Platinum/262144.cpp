#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MAXN 262150
#define MAXV 65

typedef long long ll;
typedef pair<int, int> pi;

int N;
int ans = 0;
int dp[MAXN][MAXV];

int main() {
	freopen("262144.in", "r", stdin);
	freopen("262144.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) fill(dp[i], dp[i] + MAXV, -1);
	for (int i = 0; i < N; ++i) {
		int num; cin >> num;
		dp[i][num] = i + 1;
		ans = max(ans, num);
	}

	for (int j = 1; j < MAXV; ++j) {
		for (int i = 0; i < N; ++i) {
			if (dp[i][j] == -1 && dp[i][j - 1] < N && dp[i][j - 1] != -1) {
				dp[i][j] = dp[dp[i][j - 1]][j - 1];
				if (dp[i][j] != -1) ans = max(ans, j);
			}
		}
	}

	cout << ans << "\n";

	return 0;
}