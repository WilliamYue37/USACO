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
const int MAX_N = 18;

ll N, W;
ll cows[MAX_N];
ll dp[MAX_N + 1][1 << MAX_N]; //dp[# of rides][mask]

int main() {
	//freopen("skyscraper.in", "r", stdin); freopen("skyscraper.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> W;
	for (int i = 0; i < N; ++i) {
		cin >> cows[i];
	}

	//init dp with INF
	for (int i = 0; i <= MAX_N; ++i) {
		for (int mask = 0; mask < (1 << N); ++mask) {
			dp[i][mask] = INF;
		}
	}
	
	dp[1][0] = 0;
	for (int i = 1; i < MAX_N; ++i) {
		for (int mask = 0; mask < (1 << N); ++mask) {
			if (dp[i][mask] > W) continue;
			for (int j = 0; j < N; ++j) {
				if (((1 << j) & mask) == 0) {
					dp[i][(1 << j) | mask] = min(dp[i][(1 << j) | mask], dp[i][mask] + cows[j]);
					dp[i + 1][(1 << j) | mask] = min(dp[i + 1][(1 << j) | mask], cows[j]);
				}
			} 
		}
	}
	

	int ans = MAX_N;
	for (int i = 1; i <= MAX_N; ++i) {
		if (dp[i][(1 << N) - 1] <= W) {
			ans = i;
			break;
		}
	}

	cout << ans << '\n';

	return 0;
}