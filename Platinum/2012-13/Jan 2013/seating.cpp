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
const int MAX_N = 5e5 + 5;

struct SegmentTree {
    int N;
    vector<int> maxi, left, right, delta, len; //delta -> -1 = empty, 1 = full, 0 = nothing

    SegmentTree() {}
    SegmentTree(int N) {
        this->N = 1;
        while (this->N < N) this->N <<= 1;
        maxi.resize(2 * this->N + 1);
        left.resize(2 * this->N + 1);
        right.resize(2 * this->N + 1);
        delta.resize(2 * this->N + 1);
        len.resize(2 * this->N + 1);

        init(1, 0, this->N - 1);
        update(0, this->N - 1, 1);
    }

    void update(int l, int r, int val) {update(1, 0, N - 1, l, r, val);} //inclusive range

    int query(int sz) {return query(1, 0, N - 1, sz);} //inclusive range

    void init(int i, int lo, int hi) {
    	len[i] = hi - lo + 1;

        if (lo == hi) return;
          
        int m = (lo + hi) / 2;
        init(2 * i, lo, m);
        init(2 * i + 1, m + 1, hi);
    }

    int getMaxi(int i) {
    	if (delta[i] == -1) return len[i];
    	if (delta[i] == 1) return 0;
    	return maxi[i];
    }

    int getL(int i) {
    	if (delta[i] == -1) return len[i];
    	if (delta[i] == 1) return 0;
    	return left[i];
    }

    int getR(int i) {
    	if (delta[i] == -1) return len[i];
    	if (delta[i] == 1) return 0;
    	return right[i];
    }

    void push(int i) {
    	if (delta[i] == 0) return;
        delta[2 * i] = delta[i];
        delta[2 * i + 1] = delta[i];
        delta[i] = 0;
    }

    void pull(int i) {
        maxi[i] = max({getMaxi(2 * i), getMaxi(2 * i + 1), getR(2 * i) + getL(2 * i + 1)});
        left[i] = getL(2 * i);
        if (getL(2 * i) == len[2 * i]) left[i] += getL(2 * i + 1);
        right[i] = getR(2 * i + 1);
        if (getR(2 * i + 1) == len[2 * i + 1]) right[i] += getR(2 * i);
    }

    void update(int i, int lo, int hi, int l, int r, int val) {
        if (r < lo || hi < l) return;
        if (l <= lo && hi <= r) {
        	delta[i] = val;
        	return;
        }

        push(i);

        int m = (lo + hi) / 2;
        update(2 * i, lo, m, l, r, val);
        update(2 * i + 1, m + 1, hi, l, r, val);

        pull(i);
    }

    int query(int i, int lo, int hi, int sz) {
    	if (lo == hi) {
    		if (sz == 1) return lo;
    		return -1;
    	}
    	if (getMaxi(i) < sz) return -1;

    	push(i);

    	int m = (lo + hi) / 2, ret = 0;
    	if (getMaxi(2 * i) >= sz) {
    		ret = query(2 * i, lo, m, sz);
    	}
    	else if (getR(2 * i) + getL(2 * i + 1) >= sz) {
    		ret = m - getR(2 * i) + 1;
    	}
    	else if (getMaxi(2 * i + 1) >= sz) {
    		ret = query(2 * i + 1, m + 1, hi, sz);
    	}
    	
    	pull(i);

    	return ret;
    }
};

int N, M;
SegmentTree st(MAX_N);

int main() {
	freopen("seating.in", "r", stdin); freopen("seating.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
		
	cin >> N >> M;
	st.update(1, N, -1);
	int ans = 0;
	for (int i = 0; i < M; ++i) {
		char type; cin >> type;
		if (type == 'A') {
			int sz; cin >> sz;
			int res = st.query(sz);
			if (res == -1) ++ans;
			else st.update(res, res + sz - 1, 1);
		}
		else {
			int l, r; cin >> l >> r;
			st.update(l, r, -1);
		}
	}

	cout << ans << '\n';

	return 0;
}