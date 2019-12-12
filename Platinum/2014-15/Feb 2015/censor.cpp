#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007ll
#define BASE 30ll
#define MAXN 100005

typedef long long ll;
typedef pair<int, int> pi;

string S;
int N;
ll power[MAXN];
set<int> lengths;
set<ll> censor;
ll R[MAXN];
char ans[MAXN];
int p1 = 0;

int hsh(string s) {
	ll ret = 0;
	for (int i = 0; i < s.length(); ++i) ret = (ret + (s[i] - 'a' + 1) * power[s.length() - i - 1] % MOD) % MOD;
	return ret;
}

int check() {
	for (int len: lengths) {
		ll t = ((R[p1 - 1] + MOD) - ((p1 - len - 1) >= 0 ? R[p1 - len - 1] : 0) * power[len] % MOD) % MOD;
		if (censor.count(t) > 0) return len;
	}
	return -1;
}

int main() {
	freopen("censor.in", "r", stdin);
	freopen("censor.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> S >> N;
	power[0] = 1ll;
	for (int i = 1; i < MAXN; ++i) power[i] = power[i - 1] * BASE % MOD;
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		lengths.insert(s.length());
		censor.insert(hsh(s));
	}

	for (int i = 0; i < S.length(); ++i) {
		ans[p1] = S[i];
		if (p1 == 0) R[p1] = (S[i] - 'a' + 1);
		else R[p1] = (R[p1 - 1] * BASE % MOD + (S[i] - 'a' + 1)) % MOD;
		++p1;
		int len = -1;
		while ((len = check()) != -1) {
			p1 -= len;
		}
	}

	for (int i = 0; i < p1; ++i) cout << ans[i];
	cout << '\n';

	return 0;
}