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
const int MAX_N = 300 + 5;

int N, M;
int maxi[MAX_N][MAX_N][MAX_N];
int memo[MAX_N][MAX_N];

int dp(int l, int r) {
	if (r < l) return 0;
	if (l == r) return maxi[l][l][r];
	if (memo[l][r] != -1) return memo[l][r];
	int ans = 0;
	for (int i = l; i < r; ++i) ans = max(ans, dp(l, i) + dp(i + 1, r));
	for (int i = l; i <= r; ++i) if (maxi[i][l][r] != 0) ans = max(ans, dp(l, i - 1) + maxi[i][l][r] + dp(i + 1, r));
	return memo[l][r] = ans;
}

int main() {
	freopen("pieaters.in", "r", stdin); freopen("pieaters.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int w, l, r; cin >> w >> l >> r; --l, --r;
		for (int j = l; j <= r; ++j) maxi[j][l][r] = max(maxi[j][l][r], w);
	}

	for (int i = 0; i < N; ++i) {
		for (int j = i; j >= 0; --j) {
			for (int k = i; k < N; ++k) {
				if (j != 0) maxi[i][j - 1][k] = max(maxi[i][j - 1][k], maxi[i][j][k]);
				if (k < N - 1) maxi[i][j][k + 1] = max(maxi[i][j][k + 1], maxi[i][j][k]);
			}
		}
	}

	memset(memo, -1, sizeof memo);
	cout << dp(0, N - 1) << '\n';

	return 0;
}