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
const int MAX = 1e9;

ll fastExpo(int base, int e) {
    ll ans = 1;
    while(e != 0) {
        if(e % 2 == 1) ans = (ll) ans * base % MOD;
        base = (ll) base * base % MOD;
        e /= 2;
    }
    return ans;
}

namespace modOp {
    int add(int a, int b, int mod = MOD) {return (a + b) % mod; /*int r = a + b; if (r >= mod) r -= mod; return r;*/}
    void ADD(int& a, int b, int mod = MOD) {a = (a + b) % mod; /*a += b; if (a >= mod) a -= mod;*/}
    int sub(int a, int b, int mod = MOD) {return (a - b + mod) % mod; /*int r = a - b; if (r < 0) r += mod; return r;*/}
    void SUB(int& a, int b, int mod = MOD) {a = (a - b + mod) % mod; /*a -= b; if (a < 0) a += mod;*/}
    int mul(int a, int b, int mod = MOD) {return (ll)a * b % mod;}
    void MUL(int& a, int b, int mod = MOD) {a = (ll)a * b % mod;}
    int divide(int a, int b, int mod = MOD) {return (ll)a * fastExpo(b, mod - 2) % mod;}
    void DIVIDE(int& a, int b, int mod = MOD) {a = (ll)a * fastExpo(b, mod - 2) % mod;}
}
using namespace modOp;

int N, K;
int windows[MAX_N];

int solve(int mini, int len) {
	int poss = MAX - mini;
	int dp[len + 2], pows[K + 1], powslow[K + 1];
	pows[0] = powslow[0] = 1;
	for (int i = 1; i <= K; ++i) {
		pows[i] = mul(pows[i - 1], poss + 1);
		powslow[i] = mul(powslow[i - 1], poss);
	}
	dp[0] = dp[1] = 1;
	for (int i = 2; i <= min(K, len); ++i) {
		dp[i] = pows[i - 1];
	}
	if (len < K) return pows[len];
	for (int i = K; i <= len; ++i) {
		dp[i + 1] = dp[i];
		SUB(dp[i + 1], mul(dp[i - K], powslow[K - 1]));
		MUL(dp[i + 1], poss);
		ADD(dp[i + 1], dp[i]);
	}
	return dp[len + 1];
}

int main() {
	freopen("tracking2.in", "r", stdin); freopen("tracking2.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N - K + 1; ++i) {
		cin >> windows[i];
	}
	vector<pi> comp;
	int cur = -1, cnt = 0;
	for (int i = 0; i < N - K + 1; ++i) {
		if (cur == windows[i]) ++cnt;
		else {
			if (cur != -1) comp.push_back({cur, cnt});
			cur = windows[i];
			cnt = 1;
		}
	}
	comp.push_back({cur, cnt});

	if (comp.size() == 1) {
		cout << solve(comp[0].ff, N) << '\n';
		return 0;
	}

	int ans = 1;
	for (int i = 0; i < comp.size(); ++i) {
		int len;
		if (i == 0) {
			if (comp[1].ff > comp[0].ff) len = comp[0].ss - 1;
			else len = comp[0].ss + K - 1;
		}
		else if (i == comp.size() - 1) {
			if (comp[i - 1].ff > comp[i].ff) len = comp[i].ss - 1;
			else len = comp[i].ss + K - 1;
		}
		else {
			if (comp[i - 1].ff > comp[i].ff) {
				if (comp[i + 1].ff > comp[i].ff) len = max(0, comp[i].ss - K - 1);
				else len = comp[i].ss - 1;
			}
			else {
				if (comp[i + 1].ff > comp[i].ff) len = comp[i].ss - 1;
				else len = comp[i].ss + K - 1;
			}
		}
		MUL(ans, solve(comp[i].ff, len));
	}

	cout << ans << '\n';

	return 0;
}