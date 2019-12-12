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

int N;
ll X, Y, Z;
priority_queue<ll, vector<ll>, greater<ll>> extra, need;

int main() {
	freopen("landscape.in", "r", stdin); freopen("landscape.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
		
	cin >> N >> X >> Y >> Z;
	ll ans = 0;	
	for (int i = 0; i < N; ++i) {
		int A, B; cin >> A >> B;
		int delta = B - A;
		if (delta > 0) {
			for (int j = 0; j < delta; ++j) {
				ll cost = X;
				if (!extra.empty() && extra.top() + Z * i < X) {
					cost = extra.top() + Z * i; extra.pop();
				}
				ans += cost;
				need.push(-cost - Z * i);
			}
		}
		else {
			for (int j = 0; j < -delta; ++j) {
				ll cost = Y;
				if (!need.empty() && need.top() + Z * i < Y) {
					cost = need.top() + Z * i; need.pop();
				}
				ans += cost;
				extra.push(-cost - Z * i);
			}
		}
	}

	cout << ans << '\n';

	return 0;
}
