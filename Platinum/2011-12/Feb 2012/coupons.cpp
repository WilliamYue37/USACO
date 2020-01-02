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
const int MAX_N = 5e4 + 5;

ll N, K, M;
ll P[MAX_N], C[MAX_N];
bool used[MAX_N];
priority_queue<pl, vector<pl>, greater<pl>> regular, discount;

int main() {
	//freopen("coupons.in", "r", stdin); freopen("coupons.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K >> M;
	for (int i = 0; i < N; ++i) {
		cin >> P[i] >> C[i];
		regular.push({P[i], i});
		discount.push({C[i], i});
	}
	
	priority_queue<ll, vector<ll>, greater<ll>> recover(K, 0LL);
	int cnt = 0;
	while (M > 0 && cnt < N) {
		while (used[discount.top().ss]) discount.pop();
		while (used[regular.top().ss]) regular.pop();
		if (recover.top() + discount.top().ff < regular.top().ff) {
			ll cost = recover.top() + discount.top().ff;
			if (M < cost) break;
			M -= cost;
			recover.pop();
			int idx = discount.top().ss;
			recover.push(P[idx] - C[idx]);
			used[idx] = true;
		}
		else {
			if (M < regular.top().ff) break;
			M -= regular.top().ff;
			used[regular.top().ss] = true;
		}
		++cnt;
	}

	cout << cnt << '\n';

	return 0;
}