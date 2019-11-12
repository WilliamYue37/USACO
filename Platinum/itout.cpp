#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define INF 1000000000000000000LL
#define MAXN 100005

typedef long long ll;
typedef pair<int, int> pi;

class SegmentTree {
public:
	int N;
	vector<ll> maximum, sum, delta;

	SegmentTree() {}

	SegmentTree(int N) {
		this->N = N;
		maximum = vector<ll>(4 * N + 1);
		sum = vector<ll>(4 * N + 1);
		delta = vector<ll>(4 * N + 1);
		//you don't need to init unless default values are not zero
		//init(1, 0, N-1);
	}
	
	void update(int l, int r, ll val) {update(1, 0, N - 1, l, r, val);} //inclusive range
	
	ll queryMax(int l, int r) {return queryMax(1, 0, N - 1, l, r);} //inclusive range

	ll querySum(int l, int r) {return querySum(1, 0, N - 1, l, r);}
	
	void init(int i, int lo, int hi) {
		//if default segtree values are not zero, initialize node i
		if (lo == hi) return;
		
		int m = (lo + hi) / 2;
		init(2 * i, lo, m);
		init(2 * i + 1, m + 1, hi);
	}
	
	void push(int i) {
		delta[2 * i] += delta[i];
		delta[2 * i + 1] += delta[i];
		delta[i] = 0LL;
	}

	void pull(int i) {
		maximum[i] = max(maximum[2 * i] + delta[2 * i], maximum[2 * i + 1] + delta[2 * i + 1]);
		sum[i] = min(INF, sum[2 * i] + delta[2 * i] + sum[2 * i + 1] + delta[2 * i + 1]);
	}
	
	void update(int i, int lo, int hi, int l, int r, ll val) {
		if (r < lo || hi < l) return;
		if (l <= lo && hi <= r) {
			delta[i] += val;
			return;
		}
		
		push(i);
		
		int m = (lo + hi) / 2;
		update(2 * i, lo, m, l, r, val);
		update(2 * i + 1, m + 1, hi, l, r, val);
		
		pull(i);
	}
	
	ll queryMax(int i, int lo, int hi, int l, int r) {
		if (r < lo || hi < l) return 0LL;
		if (l <= lo && hi <= r) {
			return maximum[i] + delta[i];
		}
		
		push(i);
		
		int m = (lo + hi) / 2;
		ll maxLeft = queryMax(2 * i, lo, m, l, r);
		ll maxRight = queryMax(2 * i + 1, m + 1, hi, l, r);
		
		pull(i);
		
		return max(maxLeft, maxRight);
	}

	ll querySum(int i, int lo, int hi, int l, int r) {
		if (r < lo || hi < l) return 0;
		if (l <= lo && hi <= r) {
			return sum[i] + delta[i];
		}
		
		push(i);
		
		int m = (lo + hi) / 2;
		ll sumLeft = querySum(2 * i, lo, m, l, r);
		ll sumRight = querySum(2 * i + 1, m + 1, hi, l, r);
		
		pull(i);
		
		return min(sumLeft + sumRight, INF);
	}
};

int N;
ll K;
int a[MAXN], lis[MAXN];

int main() {
	freopen("itout.in", "r", stdin);
	freopen("itout.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> a[i];

	int best = 0;
	SegmentTree st = SegmentTree(N + 1);
	for (int i = N - 1; i >= 0; --i) {
		lis[i] = st.queryMax(a[i], N) + 1;
		st.update(a[i], a[i], lis[i]);
		best = max(best, lis[i]);
	}

	vector<SegmentTree> segtrees;
	vector<int> lisLengths[best];
	vector<ll> dp[best];
	vector<int> p;
	vector<int> loc[best];
	int id[N];
	for (int i = N - 1; i >= 0; --i) {
		--lis[i];
		id[i] = lisLengths[lis[i]].size();
		lisLengths[lis[i]].push_back(a[i]);
		dp[lis[i]].push_back(0LL);
		loc[lis[i]].push_back(i);
	}
	for (int i = 0; i < best; ++i) {
		p.push_back(0);
		segtrees.push_back(SegmentTree(lisLengths[i].size() + 1));
	}
	for (int i = N - 1; i >= 0; --i) {
		if (lis[i] == 0) {
			dp[lis[i]][id[i]] = 1LL;
			segtrees[lis[i]].update(id[i], id[i], 1LL); 
			continue;
		}
		ll v = 0LL;
		while (p[lis[i]] < lisLengths[lis[i] - 1].size() && a[i] > lisLengths[lis[i] - 1][p[lis[i]]]) ++p[lis[i]];
		v = segtrees[lis[i] - 1].querySum(p[lis[i]], lisLengths[lis[i] - 1].size());
		dp[lis[i]][id[i]] = v;
		segtrees[lis[i]].update(id[i], id[i], v);
	}

	ll count = K;
	bool ans[N + 1]; fill(ans, ans + N + 1, true);
	int prev = -1;
	for (int i = best - 1; i >= 0; --i) {
		int use = lisLengths[i].size() - 1;
		while (loc[i][use] < prev) --use;
		while (dp[i][use] < count) count -= dp[i][use--];
		prev = loc[i][use];
		ans[lisLengths[i][use]] = false;
	}
	
	int sz = 0; for (int i = 1; i <= N; ++i) if (ans[i]) ++sz;
	cout << sz << '\n';
	for (int i = 1; i <= N; ++i) if (ans[i]) cout << i << '\n';

	return 0;
}