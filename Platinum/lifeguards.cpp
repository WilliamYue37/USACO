#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005
#define MAXK 105

typedef long long ll;
typedef pair<int, int> ii;

int N, K, NN;
ii shifts[MAXN];
bool valid[MAXN];
int nxt[MAXN], nxt2[MAXN];
ll dp[MAXN][MAXK];

bool compare(const ii &p1, const ii &p2) {
	if (p1.first == p2.first) return p1.second > p2.second;
	return p1.first < p2.first;
}

int main() {
	freopen("lifeguards.in", "r", stdin);
	freopen("lifeguards.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> N >> K; NN = N;
	for (int i = 0; i < N; ++i) {
		int start, end; cin >> start >> end;
		shifts[i] = ii(start, end);
	}

	sort(shifts, shifts + N, compare);


	int maxEnd = shifts[0].second;
	for (int i = 0; i < N; ++i) {
		maxEnd = max(maxEnd, shifts[i].second);
		if (shifts[i].second >= maxEnd) valid[i] = true;
	}

	int numOfValid = 0;
	for (int i = 0; i < N; ++i) {
		if (valid[i]) shifts[numOfValid++] = shifts[i]; 
	}
	N = numOfValid;

	sort(shifts, shifts + N, compare);

	for (int i = 0; i < N; ++i) {
		nxt[i] = upper_bound(shifts, shifts + N, ii(shifts[i].second, shifts[i].second)) - shifts;
		nxt2[i] = upper_bound(shifts, shifts + N, ii(shifts[i].second, shifts[i].second)) - shifts - 1;
		if (nxt2[i] == i) {
			nxt2[i] = -1;
		}
	}

	for (int i = 0; i < MAXN; ++i) {
		fill(dp[i], dp[i] + MAXK, -(1ll << 50));
	}

	//base cases
	dp[N-1][K] = shifts[N-1].second - shifts[N-1].first;
	dp[N-1][K-1] = 0;

	for (int i = N - 2; i >= 0; --i) {
		for (int j = 0; j <= K; ++j) {
			//don't take
			dp[i][j] = max(dp[i][j], dp[i + 1][min(K, j + 1)]);

			//take overlap special case
			if (nxt2[i] == N - 1 && j + N - i - 1 >= K) {
				ll skip = N - i - 1, time = shifts[i].second - shifts[i].first;
				dp[i][j] = max(dp[i][j], time);
			}
			
			//take overlap
			if (nxt2[i] != -1) {
				ll skip = nxt2[i] - i - 1, time = shifts[nxt2[i]].first - shifts[i].first;
				dp[i][j] = max(dp[i][j], dp[nxt2[i]][min((ll)K, j + skip)] + time);
			}

			//take non-overlap
			if (nxt[i] < N) {
				ll skip = nxt[i] - i - 1, time = shifts[i].second - shifts[i].first;
				dp[i][j] = max(dp[i][j], dp[nxt[i]][min((ll)K, j + skip)] + time);
			}
		}
	}

	cout << dp[0][NN - N] << "\n";
	
	return 0;
}