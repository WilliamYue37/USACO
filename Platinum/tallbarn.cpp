#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005

typedef long long ll;
typedef pair<int, int> ii;

ll N, K;
ll a[MAXN];

ll solve(double x) {
	ll total = 0;
	for (int i = 0; i < N; ++i) {
		total += ll((sqrt(1 + 4 * a[i]/x) - 1) / 2);
	}
	return total;
}

int main() {
	freopen("tallbarn.in", "r", stdin);
	freopen("tallbarn.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> K; K -= N;
	for (int i = 0; i < N; ++i) {
		cin >> a[i];
	}

	double lo = 0, hi = 1e18;
	for (int i = 0; i < 200; ++i) {
		double mid = (lo + hi) / 2;
		if (solve(mid) >= K) {
			lo = mid;
		}
		else {
			hi = mid;
		}
	}

	double ans = 0;
	ll total = 0;
	for (int i = 0; i < N; ++i) {
		ll x  = ll((sqrt(1 + 4 * a[i] / lo) - 1) / 2);
		ans += (double)a[i]/(x + 1);
		total += x;
	}

	cout << (ll)round(ans - (K - total) * lo) << "\n";

	return 0;
}