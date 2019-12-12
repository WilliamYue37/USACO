#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define MAXK 18
#define MAXN 100005

typedef long long ll;
typedef pair<int, int> pi;

int K, N;
ll coins[MAXK], purchases[MAXN];
int dp[(1 << MAXK)];

int main() {
	freopen("nochange.in", "r", stdin);
	freopen("nochange.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> K >> N;
	for (int i = 0; i < K; ++i) cin >> coins[i];
	for (int i = 1; i <= N; ++i) {
		cin >> purchases[i];
		purchases[i] += purchases[i - 1];
	}

	for (int mask = 1; mask < (1 << K); ++mask) {
		for (int i = 0; (1 << i) <= mask; ++i) {
			if (((1 << i) & mask) != 0) {
				int nmask = ~(1 << i) & mask;
				if (dp[nmask] != -1) {
					int idx = upper_bound(purchases, purchases + N + 1, purchases[dp[nmask]] + coins[i]) - purchases - 1;
					dp[mask] = max(dp[mask], idx);
				}
			}
		}
	}

	ll ans = -1;
	for (int mask = 0; mask < (1 << K); ++mask) {
		if (dp[mask] != N) continue;
		ll left = 0;
		for (int i = 0; (1 << i) < (1 << K); ++i) {
			if (((1 << i) & mask) == 0) left += coins[i];
		}
		ans = max(ans, left);
	}

	cout << ans << '\n';

	return 0;
}