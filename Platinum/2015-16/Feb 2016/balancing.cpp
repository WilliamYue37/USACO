#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e9;
const double EPS = 1e-6;
const int MAX_N = 1e5 + 5;

struct SegmentTree {
	int N;
	vector<int> sum;

	SegmentTree() {}
	SegmentTree(int N) {
		this->N = 1;
		while (this->N < N) this->N <<= 1;
		sum.resize(2 * this->N + 1);
	}

	void update(int l, int r, int val) { rec(1, 0, N - 1, l, r, val, 0); } //inclusive range

	int query(int l, int r) { return rec(1, 0, N - 1, l, r, 0, 1); } //inclusive range

	void pull(int i) {
		sum[i] = sum[2 * i] + sum[2 * i + 1];
	}

	int rec(int i, int lo, int hi, int l, int r, int val, int type) {
		if (r < lo || hi < l) return 0;
		if (l <= lo && hi <= r) {
			if (type == 0) sum[i] += val;
			return sum[i];
		}

		int m = (lo + hi) / 2;
		int sumLeft = rec(2 * i, lo, m, l, r, val, type);
		int sumRight = rec(2 * i + 1, m + 1, hi, l, r, val, type);

		pull(i);

		return sumLeft + sumRight;
	}
};

int N;
pi cows[MAX_N];
SegmentTree l(MAX_N), r(MAX_N);

int solve(int i, int l_top, int l_bot, int r_top, int r_bot, int lo, int hi) {
	if (lo == hi) {
		(l_top < l_bot ? l_top : l_bot) += l.sum[i];
		(r_top < r_bot ? r_top : r_bot) += r.sum[i];
		if (N != 1e5) return max({l_top, r_top, l_bot, r_bot});
		if (max(l_top, r_top) < max(l_bot, r_bot)) {
			return max({l_top + l.sum[i], l_bot, r_top + r.sum[i], r_bot});
		}
		else {
			return max({l_top, l_bot + l.sum[i], r_top, r_bot + r.sum[i]});
		}
	}
	
	int a = 2 * i, b = 2 * i + 1;
	if (max(l_top + l.sum[a], r_top + r.sum[a]) < max(l_bot + l.sum[b], r_bot + r.sum[b])) {
		return solve(b, l_top + l.sum[a], l_bot, r_top + r.sum[a], r_bot, (lo + hi) / 2 + 1, hi);
	}
	else {
		return solve(a, l_top, l_bot + l.sum[b], r_top, r_bot + r.sum[b], lo, (lo + hi) / 2);
	}
}

int main() {
	freopen("balancing.in", "r", stdin); freopen("balancing.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> cows[i].ff >> cows[i].ss;
	}

	int id = 0, prev = -1;
	sort(cows, cows + N, [](const pi& a, const pi& b) {return a.ss < b.ss;});
	for (int i = 0; i < N; ++i) {
		if (i != 0 && cows[i].ss != prev) ++id;
		prev = cows[i].ss;
		cows[i].ss = id;
	}

	id = 0, prev = -1;
	sort(cows, cows + N);
	for (int i = 0; i < N; ++i) {
		if (i != 0 && cows[i].ff != prev) ++id;
		prev = cows[i].ff;
		cows[i].ff = id;
		r.update(cows[i].ss, cows[i].ss, 1);
	}

	int ans = INF;
	for (int i = 0; i < N;) {
		int j = 0;
		while (i + j < N && cows[i].ff == cows[i + j].ff) {
			l.update(cows[i + j].ss, cows[i + j].ss, 1);
			r.update(cows[i + j].ss, cows[i + j].ss, -1);
			++j;
		}
		ans = min(ans, solve(1, 0, 0, 0, 0, 0, l.N - 1));
		i += j;
	}

	cout << ans << '\n';

	return 0;
}