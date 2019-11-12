#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define INF 1000000000000000000LL
#define MAXN 40005

typedef long long ll;
typedef pair<int, int> pi;

class SegmentTree {
public:
	int N;
	ll sum[4 * MAXN + 1][2][2];

	SegmentTree() {}

	SegmentTree(int N) {
		this->N = N;
		//you don't need to init unless default values are not zero
		//init(1, 0, N - 1);
	}
	
	void update(int l, int r, ll val) {update(1, 0, MAXN - 1, l, r, val);} //inclusive range
	
	ll query(int l, int r) {return query(1, 0, MAXN - 1, l, r);} //inclusive range
	
	void init(int i, int lo, int hi) {
		//if default segtree values are not zero, initialize node i
		if (lo == hi) return;
		
		int m = (lo + hi) / 2;
		init(2 * i, lo, m);
		init(2 * i + 1, m + 1, hi);
	}

	void pull(int i) {
		sum[i][0][0] = sum[i][0][1] = sum[i][1][0] = sum[i][1][1] = 0;
		for (int l1 = 0; l1 <= 1; ++l1) for (int r1 = 0; r1 <= 1; ++r1) for (int l2 = 0; l2 <= 1; ++l2) for (int r2 = 0; r2 <= 1; ++r2) if (r1 == 0 || l2 == 0)
			sum[i][l1][r2] = max(sum[i][l1][r2], sum[2 * i][l1][r1] + sum[2 * i + 1][l2][r2]);
	}
	
	void update(int i, int lo, int hi, int l, int r, ll val) {
		if (r < lo || hi < l) return;
		if (l <= lo && hi <= r) {
			sum[i][1][1] = val;
			return;
		}
		
		int m = (lo + hi) / 2;
		update(2 * i, lo, m, l, r, val);
		update(2 * i + 1, m + 1, hi, l, r, val);
		
		pull(i);
	}
	
	ll query(int i, int lo, int hi, int l, int r) {
		if (r < lo || hi < l) return 0;
		if (l <= lo && hi <= r) {
			return max({sum[i][0][0], sum[i][0][1], sum[i][1][0], sum[i][1][1]});
		}
		
		int m = (lo + hi) / 2;
		ll sumLeft = query(2 * i, lo, m, l, r);
		ll sumRight = query(2 * i + 1, m + 1, hi, l, r);
		
		pull(i);
		
		return sumLeft + sumRight;
	}
};

int N, D;
SegmentTree st;

int main() {
	freopen("optmilk.in", "r", stdin);
	freopen("optmilk.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> D;
	for (int i = 0; i < N; ++i) {
		int m; cin >> m;
		st.update(i, i, m);
	}

	ll ans = 0;
	for (int i = 0; i < D; ++i) {
		int pos, m; cin >> pos >> m; --pos;
		st.update(pos, pos, m);
		ans += st.query(0, MAXN - 1);
	}

	cout << ans << '\n';

	return 0;
}