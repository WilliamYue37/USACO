#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_N = 100005, MAX_M = 1000000;

class SegmentTree {
public:
	int N;
	vector<int> maximum, delta;

	SegmentTree() {}

	SegmentTree(int N) {
		this->N = N;
		maximum = vector<int>(4 * N + 1);
		delta = vector<int>(4 * N + 1);
		//you don't need to init unless default values are not zero
		//init(1, 0, N - 1);
	}
	
	void update(int l, int r, int val) {update(1, 0, N - 1, l, r, val);} //inclusive range
	
	int query(int l, int r) {return query(1, 0, N - 1, l, r);} //inclusive range
	
	void init(int i, int lo, int hi) {
		//if default segtree values are not zero, initialize node i
		if (lo == hi) return;
		
		int MAX_M = (lo + hi) / 2;
		init(2 * i, lo, MAX_M);
		init(2 * i + 1, MAX_M + 1, hi);
	}
	
	void push(int i) {
		delta[2 * i] += delta[i];
		delta[2 * i + 1] += delta[i];
		delta[i] = 0;
	}

	void pull(int i) {
		maximum[i] = max(maximum[2 * i] + delta[2 * i], maximum[2 * i + 1] + delta[2 * i + 1]);
	}
	
	void update(int i, int lo, int hi, int l, int r, int val) {
		if (r < lo || hi < l) return;
		if (l <= lo && hi <= r) {
			delta[i] += val;
			return;
		}
		
		push(i);
		
		int MAX_M = (lo + hi) / 2;
		update(2 * i, lo, MAX_M, l, r, val);
		update(2 * i + 1, MAX_M + 1, hi, l, r, val);
		
		pull(i);
	}
	
	int query(int i, int lo, int hi, int l, int r) {
		if (r < lo || hi < l) return (1 << 29);
		if (l <= lo && hi <= r) {
			return maximum[i] + delta[i];
		}
		
		push(i);
		
		int MAX_M = (lo + hi) / 2;
		int maxLeft = query(2 * i, lo, MAX_M, l, r);
		int maxRight = query(2 * i + 1, MAX_M + 1, hi, l, r);
		
		pull(i);
		
		return max(maxLeft, maxRight);
	}
};

int N, K;
pair<int, pi> cows[MAX_N];
SegmentTree st(2 * MAX_M);

int main() {
	freopen("lazy.in", "r", stdin);
	freopen("lazy.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		int g, x, y; cin >> g >> x >> y;
		cows[i] = {g, {MAX_M - x, y}};
	}
	
	vector<pair<pi, int>> temp;
	for (int i = 0; i < N; ++i) {
		temp.push_back({{cows[i].ss.ff + cows[i].ss.ss - K, 1}, i});
		temp.push_back({{cows[i].ss.ff + cows[i].ss.ss + K + 1, -1}, i});
	}
	sort(temp.begin(), temp.end());

	int ans = 0;
	for (auto a: temp) {
		int dif = cows[a.ss].ss.ss - cows[a.ss].ss.ff + MAX_M;
		if (a.ff.ss == 1) st.update(dif, min(dif + 2 * K, 2 * MAX_M - 1), cows[a.ss].ff);
		else st.update(dif, min(dif + 2 * K, 2 * MAX_M - 1), -cows[a.ss].ff);
		ans = max(ans, st.query(0, 2 * MAX_M - 1));
	}

	cout << ans << '\n';

	return 0;
}