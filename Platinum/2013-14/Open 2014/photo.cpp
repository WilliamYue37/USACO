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
const int MAX_N = 2e5 + 5;

struct SegmentTree {
    int N;
    vector<int> maxi, delta;

    SegmentTree() {}
    SegmentTree(int N) {
        this->N = 1;
        while (this->N < N) this->N <<= 1;
        maxi.resize(2 * this->N + 1);
        delta.resize(2 * this->N + 1);
        //you don't need to init unless default values are not zero
        //init(1, 0, this->N - 1);
    }

    void update(int l, int r, int val) {rec(1, 0, N - 1, l, r, val, 0);} //inclusive range

    int query(int l, int r) {return rec(1, 0, N - 1, l, r, 0, 1);} //inclusive range

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
        delta[i] = 0;
    }

    void pull(int i) {
        maxi[i] = max(maxi[2 * i] + delta[2 * i], maxi[2 * i + 1] + delta[2 * i + 1]);
    }

    int rec(int i, int lo, int hi, int l, int r, int val, int type) {
        if (r < lo || hi < l) return -1;
        if (l <= lo && hi <= r) {
            if (type == 0) delta[i] += val;
            return maxi[i] + delta[i];
        }

        push(i);

        int m = (lo + hi) / 2;
        int maxLeft = rec(2 * i, lo, m, l, r, val, type);
        int maxRight = rec(2 * i + 1, m + 1, hi, l, r, val, type);

        pull(i);

        return max(maxLeft, maxRight);
    }
};

int N, M;
int Lbound[MAX_N], Rbound[MAX_N]; //inclusive
SegmentTree st(MAX_N);

int main() {
	freopen("photo.in", "r", stdin); freopen("photo.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;
	fill(Rbound, Rbound + N + 1, N + 1);
	for (int i = 0; i < M; ++i) {
		int l, r; cin >> l >> r;
		Rbound[l - 1] = min(Rbound[l - 1], r);
		Lbound[l] = max(Lbound[l], r + 1);
	}

	Rbound[N + 1] = N + 1;
	for (int i = N - 1; i >= 0; --i) {
		Rbound[i] = min(Rbound[i], Rbound[i + 1]);
	}
	for (int i = 1; i <= N; ++i) {
		Lbound[i] = max(Lbound[i], Lbound[i - 1]);
	}

	st.update(1, N, -1);
	st.update(N + 1, N + 1, 0);
	for (int i = N; i >= 0; --i) {
		int l = max(Lbound[i], i + 1);
		int r = Rbound[i];
		if (l > r) st.update(i, i, -1);
		else if (st.query(l, r) < 0) st.update(i, i, -1 - st.query(i, i));
		else st.update(i, i, st.query(l, r) + 1 - st.query(i, i));
	}

	cout << max(st.query(0, 0) - 1, -1) << '\n';

	return 0;
}