#include <bits/stdc++.h>

using namespace std;

#define MAXN 1005
#define MAXM 1005
#define MAXK 15
#define MOD 1000000009

typedef long long ll;
typedef pair<int, int> ii;

struct Cow {
	int score;
	bool isFJ;

	bool operator < (Cow const &c) const {
		return (score == c.score ? (isFJ && !c.isFJ) : score < c.score);
	}
};

int N, M, K;
Cow cows[MAXN + MAXM];
ll dp[MAXN + MAXM][MAXK][MAXK];

int main() {
	freopen("team.in", "r", stdin);
	freopen("team.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) {
		int score; cin >> score;
		cows[i] = Cow{score, true};
	}
	for (int i = N; i < N + M; ++i) {
		int score; cin >> score;
		cows[i] = Cow{score, false};
	}

	sort(cows, cows + N + M);

	dp[N + M][0][0] = 1;

	for (int index = N + M - 1; index >= 0; --index) {
		for (int i = 0; i <= K; ++i) {
			for (int j = 0; j <= K; ++j) {
				if (i >= j) {
					if (cows[index].isFJ) {
						dp[index][i][j] = (dp[index + 1][i][j] + (i != 0 ? dp[index + 1][i - 1][j] : 0)) % MOD;
					}
					else {
						dp[index][i][j] = (dp[index + 1][i][j] + (j != 0 ? dp[index + 1][i][j - 1] : 0)) % MOD;
					}
				}
			}
		}
	}

	cout << dp[0][K][K] << "\n";

	return 0;
}