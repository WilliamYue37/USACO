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
const int MAX_N = 1005;
const int MAX_K = 10;

struct Sol {
	ll x;
	ll prevCost;

	ll compute(ll y) {
		return x * y + prevCost;
	}

	//time that r overtakes this
	ld intersect(Sol r) {
		return (this->prevCost - r.prevCost) / (r.x - this->x);	
	}
};

class CHT {
public: 
	Sol dq[MAX_N]; //deque
	int p1, p2; //front and back pointers, respectively 

	void insert(Sol part) {
		while (p2 - p1 >= 2 && dq[p2 - 2].intersect(dq[p2 - 1]) >= dq[p2 - 2].intersect(part)) --p2;
		dq[p2++] = part;
	}

	ll query(ll x) {
		while (p1 + 1 < p2 && dq[p1].compute(x) >= dq[p1 + 1].compute(x)) ++p1;
		return dq[p1].compute(x);
	}
};

int N, K;
ll cows[MAX_N], arr[MAX_N], pre1[MAX_N], pre2[MAX_N], dp[MAX_N][MAX_K];
CHT cht[MAX_K];

ll solve() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <= K; ++j) {
			dp[i][j] = INF;
		}
	}
	for (int i = 0; i < N; ++i) {
		pre1[i] = arr[i] * i + (i == 0 ? 0 : pre1[i - 1]);
		pre2[i] = arr[i] + (i == 0 ? 0 : pre2[i - 1]);
	}
	for (int i = 0; i <= K; ++i) {
		cht[i] = CHT();
		cht[i].insert({pre2[N - 1], pre1[N - 1]});
	}
	for (int i = N - 1; i >= 0; --i) {
		for (int j = 1; j <= K; ++j) {
			dp[i][j] = cht[j - 1].query(-1 * i) + i * (i == 0 ? 0 : pre2[i - 1]) - (i == 0 ? 0 : pre1[i - 1]);
		}
		for (int j = 1; j <= K; ++j) {
			cht[j].insert({i == 0 ? 0 : pre2[i - 1], dp[i][j] + (i == 0 ? 0 : pre1[i - 1])});
		}
	}

	return dp[0][K];
}

int main() {
	freopen("cbarn.in", "r", stdin); freopen("cbarn.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		cin >> cows[i];
	}

	ll ans = INF;
	for (int i = 0; i < N; ++i) {
		int p1 = 0;
		for (int j = i; j < N; ++j) arr[p1++] = cows[j];
		for (int j = 0; j < i; ++j) arr[p1++] = cows[j];
		ans = min(ans, solve());
	}

	cout << ans << '\n';

	return 0;
}