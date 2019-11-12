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
const int MAX_K = 8;

int N, K;
pi cows[MAX_N];
vector<int> back[MAX_N], forw[MAX_N];
int pre[MAX_N][MAX_K];
map<vector<int>, int> mp[1 << MAX_K];
int found[MAX_K];

int main() {
	freopen("fairphoto.in", "r", stdin); freopen("fairphoto.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;	
	for (int i = 1; i <= N; ++i) {
		cin >> cows[i].ff >> cows[i].ss; --cows[i].ss;
	}
	sort(cows + 1, cows + N + 1);

	// generate backward bitmasks
	for (int i = 1; i <= N; ++i) {
		found[cows[i].ss] = i;
		vector<pi> v;
		for (int j = 0; j < MAX_K; ++j) {
			if (found[j] != 0) v.push_back({found[j], j});
		}
		sort(v.begin(), v.end(), greater<pi>());
		int mask = 0;
		for (int j = 0; j < v.size(); ++j) {
			mask |= (1 << v[j].ss);
			back[i].push_back(mask);
		}
	}

	// generate forward bitmasks
	memset(found, 0, sizeof found);
	for (int i = N; i >= 0; --i) {
		if (i != 0) found[cows[i].ss] = i;
		vector<pi> v;
		for (int j = 0; j < MAX_K; ++j) {
			if (found[j] != 0) v.push_back({found[j], j});
		}
		sort(v.begin(), v.end());
		int mask = 0;
		for (int j = 0; j < v.size(); ++j) {
			mask |= (1 << v[j].ss);
			forw[i].push_back(mask);
		}
	}

	int ans = -1;
	for (int i = 1; i <= N; ++i) {
		//update prefix sums
		for (int j = 0; j < MAX_K; ++j) {
			pre[i][j] = pre[i - 1][j];
		}
		++pre[i][cows[i].ss];

		// query
		for (int k = 0; k < back[i].size(); ++k) {
			vector<int> v(MAX_K);
			int first = -1;
			for (int j = 0; j < MAX_K; ++j) {
				if (((1 << j) & back[i][k]) != 0) {
					if (first == -1) {
						first = pre[i][j];
					}
					v[j] = pre[i][j] - first;
				}
				else v[j] = pre[i][j];
			}

			if (mp[back[i][k]].count(v)) {
				int idx = mp[back[i][k]][v];
				int unique = 0;
				for (int j = 0; j < MAX_K; ++j) {
					if (pre[i][j] - pre[idx - 1][j] > 0) ++unique;
				}
				if (unique >= K) {
					ans = max(ans, cows[i].ff - cows[idx].ff);
				}
			}
		}

		// update mp
		for (int k = 0; k < forw[i - 1].size(); ++k) {
			vector<int> v(MAX_K);
			int first = -1;
			for (int j = 0; j < MAX_K; ++j) {
				if (((1 << j) & forw[i - 1][k]) != 0) {
					if (first == -1) {
						first = pre[i - 1][j];
					}
					v[j] = pre[i - 1][j] - first;
				}
				else v[j] = pre[i - 1][j];
			}
			if (mp[forw[i - 1][k]].count(v) == 0) mp[forw[i - 1][k]][v] = i;
		}
	}

	cout << ans << '\n';

	return 0;
}