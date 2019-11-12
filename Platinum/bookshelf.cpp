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

ll N, L;
deque<pair<pl, pl>> dq;
ll H[MAX_N], W[MAX_N], dp[MAX_N], cum[MAX_N];
multiset<ll> best;

int main() {
	//freopen("bookshelf.in", "r", stdin); freopen("bookshelf.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> L;
	for (int i = 1; i <= N; ++i) {
		cin >> H[i] >> W[i];
		cum[i] = cum[i - 1] + W[i];
	}

	int pre = 0;
	for (int i = 1; i <= N; ++i) {
		pair<pl, pl> a = {{dp[i - 1] + H[i], H[i]}, {i - 1, i - 1}};
		while (dq.size() > 0 && dq.back().ff.ss <= a.ff.ss) {
			pair<pl, pl> b = dq.back(); dq.pop_back();
			best.erase(best.find(b.ff.ff));
			a.ss.ff = b.ss.ff;
			a.ff.ff = dp[a.ss.ff] + H[i];
		}
		dq.push_back(a);
		best.insert(a.ff.ff);

		while (cum[i] - cum[pre] > L) ++pre;
		while (dq.front().ss.ff < pre) {
			best.erase(best.find(dq.front().ff.ff));
			dq.front().ss.ff = pre;
			if (dq.front().ss.ff > dq.front().ss.ss) dq.pop_front();
			else {
				dq.front().ff.ff = dq.front().ff.ss + dp[pre];
				best.insert(dq.front().ff.ff);
			}
		}

		dp[i] = *best.begin();
	}

	cout << dp[N] << '\n';

	return 0;
}