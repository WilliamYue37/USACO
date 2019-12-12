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

namespace modOp {
    int add(int a, int b, int mod = MOD) {return (a + b) % mod; /*int r = a + b; if (r >= mod) r -= mod; return r;*/}
    void ADD(ll& a, ll b, int mod = MOD) {a = (a + b) % mod; /*a += b; if (a >= mod) a -= mod;*/}
    int sub(int a, int b, int mod = MOD) {return (a - b + mod) % mod; /*int r = a - b; if (r < 0) r += mod; return r;*/}
    void SUB(int& a, int b, int mod = MOD) {a = (a - b + mod) % mod; /*a -= b; if (a < 0) a += mod;*/}
    int mul(int a, int b, int mod = MOD) {return (ll)a * b % mod;}
    void MUL(int& a, int b, int mod = MOD) {a = (ll)a * b % mod;}
}
using namespace modOp;

ll N, point[MAX_N], lo[MAX_N], hi[MAX_N];
ll cumlo[MAX_N][2], cumhi[MAX_N][2];
ll ans = 0;

ll getlo(int type, int l, int r) {
	return sub(cumlo[r + 1][type], cumlo[l][type]);
}

ll gethi(int type, int l, int r) {
	return sub(cumhi[r + 1][type], cumhi[l][type]);
}

void solve(int x) {
	int l = x - 1, r = N - 2;
	while (l < r) {
		int m = (l + r + 1) / 2;
		if (hi[m] >= lo[x]) l = m;
		else r = m - 1;
	}
	ans += gethi(1, x, l);
	ans -= 2 * gethi(0, x, l) * lo[x];
	ans += (l + 1 - x) * lo[x] * lo[x];
	ans += 3 * (gethi(0, x, l) - (l+1 - x) * lo[x]);
	ans += 2 * (l + 1 - x);
	ans %= MOD;
}

int main() {
	freopen("sprinklers.in", "r", stdin); freopen("sprinklers.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		int x, y; cin >> x >> y;
		point[x] = y;
	}
	for (int i = 0; i < N - 1; ++i) {
		lo[i] = point[i];
		if (i > 0) lo[i] = min(lo[i], lo[i - 1]);
	}
	for (int i = N - 1; i >= 0; --i) {
		hi[i] = point[i  + 1] - 1;
		if (i < N - 2) hi[i] = max(hi[i], hi[i + 1]);
	}

	for (int i = 0; i < N - 1; ++i) {
		cumlo[i + 1][0] = lo[i], cumlo[i + 1][1] = lo[i] * lo[i];
		cumhi[i + 1][0] = hi[i], cumhi[i + 1][1] = hi[i] * hi[i];
		for (int j = 0; j < 2; ++j) {
			ADD(cumlo[i + 1][j], cumlo[i][j]);
			ADD(cumhi[i + 1][j], cumhi[i][j]);
		}
	}

	for (int i = 0; i < N - 1; ++i) solve(i);
	ans *= (MOD + 1) / 2;
	ans = (ans % MOD + MOD) % MOD;

	cout << ans << '\n';

	return 0;
}