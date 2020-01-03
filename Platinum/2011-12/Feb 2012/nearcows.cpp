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
const int MAX_N = 1e5 + 5;
const int MAX_K = 20 + 5;

int N, K;
vector<int> adjList[MAX_N];
int dp[MAX_N][MAX_K];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	for (int i = 1; i <= N; ++i) {
		cin >> dp[i][0];
	}

	for (int k = 1; k <= K; ++k) {
		for (int u = 1; u <= N; ++u) {
			for (int v: adjList[u]) {
				dp[u][k] += dp[v][k - 1];
			}
			if (k > 1) dp[u][k] -= dp[u][k - 2] * (adjList[u].size() - 1);
			else dp[u][k] += dp[u][0];
		}
	}

	for (int u = 1; u <= N; ++u) cout << dp[u][K] << '\n';

	return 0;
}