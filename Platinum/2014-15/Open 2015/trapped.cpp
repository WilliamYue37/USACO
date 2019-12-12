#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const int INF = 1e9;
const double EPS = 1e-6;
const int MAX_N = 1e5 + 5;

int N;
pi bales[MAX_N];
set<pi> s, ans;

void add(int st, int en) {
	auto x = ans.upper_bound({st, INF});
	if (!ans.empty() && x != ans.begin()) {
		x = prev(x);
		if ((*x).ff <= st && en <= (*x).ss) return;
	}
	ans.insert({st, en});
}

int main() {
	freopen("trapped.in", "r", stdin); freopen("trapped.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> bales[i].ff >> bales[i].ss;
	sort(bales, bales + N);
	reverse(bales, bales + N);

	for (pi b: bales) {
		pi bale = {b.ss, b.ff};
		auto x = s.upper_bound(bale);
		if (x != s.end()) {
			pi b1 = *x;
			if (min(bale.ss, b1.ss) >= (b1.ff - bale.ff)) add(bale.ff, b1.ff);
		}
		if (!s.empty() && x != s.begin()) {
			pi b1 = *prev(x);
			if (min(bale.ss, b1.ss) >= (bale.ff - b1.ff)) add(b1.ff, bale.ff);
		}
		s.insert(bale);
	}

	int res = 0;
	for (pi p: ans) res += p.ss - p.ff;
	cout << res << '\n';

	return 0;
}