#include <bits/stdc++.h>

using namespace std;

#define MAXN 21
#define MAX_MASK (1 << 21)

typedef long long ll;

int N, H;
ll cows[MAXN][3];
int popcount[MAX_MASK];
ll dp[MAX_MASK];

int main() {
	freopen("guard.in", "r", stdin);
	freopen("guard.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> H;
	for (int i = 0; i < N; ++i) {
		cin >> cows[i][0] >> cows[i][1] >> cows[i][2];
	}

	for (int i = 0; i < MAX_MASK; ++i) {
		popcount[i] = __builtin_popcount(i);
	}
	memset(dp, -1ll, sizeof(dp));

	for (int mask = 0; mask < (1 << N); ++mask) {
		int numOfCows = popcount[mask];
		if (numOfCows == 1) {
			for (int i = 0; (1 << i) <= mask; ++i) {
				if (((1 << i) & mask) != 0) {
					dp[mask] = cows[i][2];
				}
			}
		}
		else {
			for (int i = 0; (1 << i) <= mask; ++i) {
				if (((1 << i) & mask) != 0 && dp[(mask & ~(1 << i))] >= 0) {
					dp[mask] = max(dp[mask], min(dp[(mask & ~(1 << i))] - cows[i][1], cows[i][2]));
				}
			}
		}
	}

	ll maxHeight = 0, maxSafety = -1;
	for (int mask = 0; mask < (1 << N); ++mask) {
		if (dp[mask] < 0) continue;
		ll height = 0;
		for (int i = 0; (1 << i) <= mask; ++i) {
			if (((1 << i) & mask) != 0) {
				height += cows[i][0];
			}
		}
		if (height >= H && dp[mask] > maxSafety) {
			maxHeight = height;
			maxSafety = dp[mask];
		}
	}

	if (maxSafety != -1) {
		cout << maxSafety << "\n";
	}
	else {
		cout << "Mark is too tall" << "\n";
	}

	return 0;
}