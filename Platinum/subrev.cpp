#include <bits/stdc++.h>

using namespace std;

#define MAXN 55

typedef long long ll;
typedef pair<int, int> ii;

int N;
int arr[MAXN];
int memo[MAXN][MAXN][MAXN][MAXN];

int dp(int l, int r, int prefix, int suffix) {
	if (suffix < prefix) return -(1 << 29);
	if (l > r) return 0;
	if (l == r) return prefix <= arr[l] && arr[l] <= suffix;
	if (memo[l][r][prefix][suffix] != -1) return memo[l][r][prefix][suffix];

	int ans = 0;
	ans = max(ans, dp(l + 1, r - 1, prefix, suffix));
	if (arr[l] <= suffix) ans = max(ans, dp(l + 1, r - 1, prefix, arr[l]) + 1);
	if (arr[r] >= prefix) ans = max(ans, dp(l + 1, r - 1, arr[r], suffix) + 1);
	if (prefix <= arr[r] && arr[r] <= arr[l] && arr[l] <= suffix) ans = max(ans, dp(l + 1, r - 1, arr[r], arr[l]) + 2);

	ans = max(ans, dp(l + 1, r, prefix, suffix));
	if (prefix <= arr[l]) ans = max(ans, dp(l + 1, r, arr[l], suffix) + 1);
	
	ans = max(ans, dp(l, r - 1, prefix, suffix));
	if (arr[r] <= suffix) ans = max(ans, dp(l, r - 1, prefix, arr[r]) + 1);

	return (memo[l][r][prefix][suffix] = ans);
}

int main() {
	freopen("subrev.in", "r", stdin);
	freopen("subrev.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
	}

	memset(memo, -1, sizeof(memo));
	cout << dp(0, N - 1, 0, 50) << "\n";

	return 0;
}