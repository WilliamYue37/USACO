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

int N, K, id = 0;
int cows[MAX_N], cnt[MAX_N];
map<int, int> mp;

int main() {
	freopen("lineup.in", "r", stdin); freopen("lineup.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		cin >> cows[i];
		if (mp.count(cows[i]) == 0) {
			mp[cows[i]] = id++;
		}
	}

	int ans = 0, distinct = 0, p1 = 0, p2 = -1;
	while (p1 < N && p2 < N) {
		if (distinct <= K + 1) {
			++p2;
			if (p2 >= N) break;
			int b_id = mp[cows[p2]];
			++cnt[b_id];
			if (cnt[b_id] == 1) ++distinct;
		}
		else {
			int b_id = mp[cows[p1++]];
			--cnt[b_id];
			if (cnt[b_id] == 0) --distinct;
		}
		if (distinct <= K + 1) ans = max(ans, cnt[mp[cows[p2]]]);
	}

	cout << ans << '\n';

	return 0;
}