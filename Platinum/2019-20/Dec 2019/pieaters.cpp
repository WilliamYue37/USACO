#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const int INF = 1e7;
const double EPS = 1e-6;
const int MAX_N = 305;
const int MAX_M = 45155;

struct SegmentTree {
    int N;
    vector<int> sum, delta;

    SegmentTree() {}
    SegmentTree(int N) {
        this->N = 1;
        while (this->N < N) this->N <<= 1;
        sum.resize(2 * this->N + 1);
        delta.resize(2 * this->N + 1);
        //you don't need to init unless default values are not zero
        init(1, 0, this->N - 1);
    }

    void update(int l, int r, int val) {rec(1, 0, N - 1, l, r, val, 0);} //inclusive range

    int query(int l, int r) {return rec(1, 0, N - 1, l, r, 0, 1);} //inclusive range

    void init(int i, int lo, int hi) {
        //if default segtree values are not zero, initialize node i
    	delta[i] = INF;

        if (lo == hi) return;
          
        int m = (lo + hi) / 2;
        init(2 * i, lo, m);
        init(2 * i + 1, m + 1, hi);
    }

    void push(int i) {
    	if (delta[i] == INF) return;
        delta[2 * i] = delta[i];
        delta[2 * i + 1] = delta[i];
        delta[i] = 0;
    }

    void pull(int i) {
    	int left = delta[2 * i] == INF ? sum[2 * i] : delta[2 * i];
    	int right = delta[2 * i + 1] == INF ? sum[2 * i + 1] : delta[2 * i + 1];
        sum[i] = left + right;
    }

    int rec(int i, int lo, int hi, int l, int r, int val, int type) {
        if (r < lo || hi < l) return 0;
        if (l <= lo && hi <= r) {
            if (type == 0) delta[i] = val;
            return delta[i] == INF ? sum[i] : delta[i];
        }

        push(i);

        int m = (lo + hi) / 2;
        int sumLeft = rec(2 * i, lo, m, l, r, val, type);
        int sumRight = rec(2 * i + 1, m + 1, hi, l, r, val, type);

        pull(i);

        return sumLeft + sumRight;
    }
};

int N, M;
pair<int, pi> cows[MAX_M];
SegmentTree st(MAX_N);

int main() {
	freopen("pieaters.in", "r", stdin); freopen("pieaters.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int w, l, r; cin >> w >> l >> r;
		cows[i] = {w, {l, r}};
	}

	// try all subsets
	ll ans = 0;
	for (int mask = 0; mask < (1 << M); ++mask) {
		// clear segtree
		st.update(0, MAX_N - 1, 0);

		vector<pair<int, pi>> subset;
		for (int i = 0; (1 << i) <= mask; ++i) {
			if (((1 << i) & mask) != 0) subset.push_back(cows[i]);
		}
		sort(subset.begin(), subset.end(), [](pair<int, pi> a, pair<int, pi> b) {return (a.ss.ss - a.ss.ff) < (b.ss.ss - b.ss.ff);});

		ll res = 0;
		for (int i = 0; i < (int)subset.size(); ++i) {
			int w = subset[i].ff, l = subset[i].ss.ff, r = subset[i].ss.ss;
			if (st.query(l, r) < (r - l + 1)) {
				res += w;
				st.update(l, r, 1);
			}
		}

		ans = max(ans, res);
	}

	cout << ans << '\n';

	return 0;
}