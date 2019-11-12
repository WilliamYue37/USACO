#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_N = 300005;

int N, K;
int pre[MAX_N], dp[MAX_N];
map<int, multiset<int>> mp;

int main() {
	freopen("redistricting.in", "r", stdin);
	freopen("redistricting.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	for (int i = 1; i <= N; ++i) {
		char c; cin >> c;
		pre[i] = pre[i - 1] + (c == 'H' ? -1 : 1);
	}

	mp[0].insert(0);
	for (int i = 1; i <= N; ++i) {
		dp[i] = (*mp.begin()).ff + ((*((*mp.begin()).ss.rbegin()) > pre[i]) ? 0 : 1);
		if (i - K >= 0) {
			mp[dp[i - K]].erase(mp[dp[i - K]].find(pre[i - K]));
			if (mp[dp[i - K]].size() == 0) mp.erase(dp[i - K]);
		}
		mp[dp[i]].insert(pre[i]);
	}

	cout << dp[N] << '\n';

	return 0;
}