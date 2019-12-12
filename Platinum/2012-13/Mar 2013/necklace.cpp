#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const ld PI = 4 * atan((ld)1);
const int MAX_N = 1e4 + 5;
const int MAX_M = 1e3 + 5;

string N, M;
int memo[MAX_N][MAX_M];
vector<int> lps;

vector<int> precompute(string s) {
	vector<int> lps(s.size());
	int j = 0;
	for (int i = 1; i < s.size();) {
		if (s[i] == s[j]) lps[i] = ++j, ++i;
		else if (j != 0) j = lps[j - 1];
		else lps[i] = 0, ++i;
	}
	return lps;
}

int dp(int i, int j) {
	if (j == M.size()) return (1 << 29);
	if (i == N.size()) return 0;
	if (memo[i][j] != -1) return memo[i][j];
	if (N[i] == M[j]) return memo[i][j] = min(dp(i + 1, j + 1), dp(i + 1, j) + 1);
	else if (j != 0) return memo[i][j] = dp(i, lps[j - 1]);
	else return memo[i][j] = dp(i + 1, 0);
}

int main() {
	freopen("necklace.in", "r", stdin); freopen("necklace.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;
	memset(memo, -1, sizeof(memo));
	lps = precompute(M);
	cout << dp(0, 0) << '\n';

	return 0;
}