#include <bits/stdc++.h>

using namespace std;

#define MAXN 21
#define MAXB 21
#define MAX_MASK (1 << 21)

typedef pair<int, int> ii;

int N, B;
pair<int, ii> bonus[MAXB];
int cows[MAXN][MAXN];
int dp[2][MAX_MASK];

int main() {
	freopen("dec.in", "r", stdin);
	freopen("dec.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> B;
	for (int i = 0; i < B; ++i) {
		int k, p, a; cin >> k >> p >> a;
		bonus[i] = make_pair(k, ii(p, a));
	}
	sort(bonus, bonus + B);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> cows[i][j];
		}
	}

	int b1 = 0;
	for (int i = 1; i <= N; ++i) {
		while (b1 < B && bonus[b1].first < i) ++b1;
		for (int mask = 0; mask < (1 << N); ++mask) {
			if (__builtin_popcount(mask) != i) continue;
			for (int j = 0; (1 << j) <= mask; ++j) {
				if (((1 << j) & mask) != 0) {
					dp[1][mask] = max(dp[1][mask], dp[0][mask & ~(1 << j)] + cows[j+1][i]);
				}
			}
			for (int j = b1; j < B && bonus[b1].first == i; ++j) {
				if (bonus[j].first == i && dp[1][mask] >= bonus[j].second.first) {
					dp[1][mask] += bonus[j].second.second;
				}
			}
		}
		for (int mask = 0; mask < MAX_MASK; ++mask) {
			dp[0][mask] = dp[1][mask];
			dp[1][mask] = 0;
		}
	}

	int ans = 0;
	for (int i = 0; i < MAX_MASK; ++i) {
		ans = max(ans, dp[0][i]);
	}

	cout << ans << "\n";

	return 0; 
}