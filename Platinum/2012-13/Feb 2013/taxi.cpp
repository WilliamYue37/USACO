#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;

int N, M;

int main() {
	freopen("taxi.in", "r", stdin); freopen("taxi.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;

	ll ans = 0;
	vector<pi> v;
	v.push_back({0, 1});
	v.push_back({M, -1});
	for (int i = 0; i < N; ++i) {
		int s, e; cin >> s >> e;
		ans += abs(s - e);
		v.push_back({s, -1});
		v.push_back({e, 1});
	}
	sort(v.begin(), v.end());

	int sum = v[0].ss;
	for (int i = 1; i < v.size(); ++i) {
		ans += 1ll * (v[i].ff - v[i - 1].ff) * abs(sum);
		sum += v[i].ss;
	}

	cout << ans << '\n';

	return 0;
}