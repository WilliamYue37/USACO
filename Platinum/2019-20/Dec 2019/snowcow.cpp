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
const int MAX_N = 1e5 + 5;
const int MAX_Q = 1e5 + 5;

struct SegmentTreeSum {
    int N;
    vector<ll> sum, delta, len;

    SegmentTreeSum() {}
    SegmentTreeSum(int N) {
        this->N = 1;
        while (this->N < N) this->N <<= 1;
        sum.resize(2 * this->N + 1);
        delta.resize(2 * this->N + 1);
        len.resize(2 * this->N + 1);
        //you don't need to init unless default values are not zero
        init(1, 0, this->N - 1);
    }

    void update(int l, int r, int val) {rec(1, 0, N - 1, l, r, val, 0);} //inclusive range

    ll query(int l, int r) {return rec(1, 0, N - 1, l, r, 0, 1);} //inclusive range

    void init(int i, int lo, int hi) {
        //if default segtree values are not zero, initialize node i
        len[i] = hi - lo + 1;

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
        sum[i] = sum[2 * i] + delta[2 * i] * len[2 * i] + sum[2 * i + 1] + delta[2 * i + 1] * len[2 * i + 1];
    }

    ll rec(int i, int lo, int hi, int l, int r, int val, int type) {
        if (r < lo || hi < l) return 0;
        if (l <= lo && hi <= r) {
            if (type == 0) delta[i] += val;
            return sum[i] + delta[i] * len[i];
        }

        push(i);

        int m = (lo + hi) / 2;
        ll sumLeft = rec(2 * i, lo, m, l, r, val, type);
        ll sumRight = rec(2 * i + 1, m + 1, hi, l, r, val, type);

        pull(i);

        return sumLeft + sumRight;
    }
};

struct SegmentTreeMin {
    int N;
    vector<int> mini, delta;

    SegmentTreeMin() {}
    SegmentTreeMin(int N) {
        this->N = 1;
        while (this->N < N) this->N <<= 1;
        mini.resize(2 * this->N + 1);
        delta.resize(2 * this->N + 1);
        //you don't need to init unless default values are not zero
        //init(1, 0, this->N - 1);
    }

    void update(int l, int r, int val) {rec(1, 0, N - 1, l, r, val, 0);} //inclusive range

    int query(int l, int r) {return rec(1, 0, N - 1, l, r, 0, 1);} //inclusive range

    void init(int i, int lo, int hi) {
        //if default segtree values are not zero, initialize node i
        mini[i] = delta[i] = INF;

        if (lo == hi) return;
          
        int m = (lo + hi) / 2;
        init(2 * i, lo, m);
        init(2 * i + 1, m + 1, hi);
    }

    void push(int i) {
    	if (delta[i] == INF) return;
        delta[2 * i] = delta[i];
        delta[2 * i + 1] = delta[i];
        delta[i] = INF;
    }

    void pull(int i) {
    	int left = delta[2 * i] == INF ? mini[2 * i] : delta[2 * i];
    	int right = delta[2 * i + 1] == INF ? mini[2 * i + 1] : delta[2 * i + 1];
        mini[i] = min(left, right);
    }

    int rec(int i, int lo, int hi, int l, int r, int val, int type) {
        if (r < lo || hi < l) return INF;
        if (l <= lo && hi <= r) {
            if (type == 0) delta[i] = val;
            return delta[i] == INF ? mini[i] : delta[i];
        }

        push(i);

        int m = (lo + hi) / 2;
        int minLeft = rec(2 * i, lo, m, l, r, val, type);
        int minRight = rec(2 * i + 1, m + 1, hi, l, r, val, type);

        pull(i);

        return min(minLeft, minRight);
    }
};

// tree stuff
int N, Q;
vector<int> adjList[MAX_N];
int parent[MAX_N];
pi range[MAX_N];

//query stuff
pair<int, pi> queries[MAX_Q]; // {type, {u, c}}
map<int, vector<pi>> mp; // <color, list of updates in the form {id, u}>
bool trash[MAX_Q];
vector<int> nullify[MAX_Q];
SegmentTreeMin stmin1(MAX_N);
SegmentTreeMin stmin2(MAX_N);
SegmentTreeSum stsum(MAX_N);

int id = 0;
void preorder(int u, int p) {
	range[u].ff = id++;
	for (int v: adjList[u]) {
		if (v != p) preorder(v, u);
	}
	range[u].ss = id - 1;
}

void DFS(int u, int p) {
	parent[u] = p;
	for (int v: adjList[u]) {
		if (v != p) DFS(v, u);
	}
}

int main() {
	freopen("snowcow.in", "r", stdin); freopen("snowcow.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> Q;
	for (int i = 0; i < N - 1; ++i) {
		int u, v; cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	preorder(1, -1);
	DFS(1, -1);

	// process queries
	for (int i = 0; i < Q; ++i) {
		int type, u, c; cin >> type;
		if (type == 1) {
			cin >> u >> c;
		}
		else {
			cin >> u;
			c = -1;
		}
		queries[i] = {type, {u, c}};
		if (type == 1) {
			mp[c].push_back({i, u});
		}
	}

	// add time stamp for nullification
	for (auto& item: mp) {
		//clear segtrees
		stmin1.update(0, MAX_N - 1, 1e6);
		stmin2.update(0, MAX_N - 1, 0);


		vector<pi>& v = item.ss; // {id, u}

		//first nullfiy updates that have no impact
		sort(v.begin(), v.end());
		for (int i = 0; i < (int)v.size(); ++i) {
			int u = v[i].ss;
			int l = range[u].ff, r = range[u].ss;
			int mini = stmin2.query(l, r);
			if (mini != 0) {
				trash[v[i].ff] = true;
			}
			else {
				stmin2.update(l, r, 1);
			}
		}

		// find nullification time stamps for remaining updates
		sort(v.begin(), v.end(), greater<pi>());
		for (int i = 0; i < (int)v.size(); ++i) {
			if (trash[v[i].ff]) continue;
			int u = v[i].ss;
			int l = range[u].ff, r = range[u].ss;
			int mini = stmin1.query(l, r);
			if (mini < Q) {
				nullify[mini].push_back(v[i].ff);
			}
			stmin1.update(l, r, v[i].ff);
		}
	}

	// process queries
	for (int i = 0; i < Q; ++i) {
		if (trash[i]) continue;

		// nullify things
		for (int j: nullify[i]) {
			int u = queries[j].ss.ff;
			int l = range[u].ff, r = range[u].ss;
			stsum.update(l, r, -1);
		}

		int u = queries[i].ss.ff;
		int l = range[u].ff, r = range[u].ss;
		if (queries[i].ff == 1) {
			stsum.update(l, r, 1);
		}
		else {
			cout << stsum.query(l, r) << '\n';
		}
	}


	return 0;
}