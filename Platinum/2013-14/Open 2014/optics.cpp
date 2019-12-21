#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define x1 ff.ff
#define y1 ff.ss
#define x2 ss.ff
#define y2 ss.ss

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-6;
const int MAX_N = 1e5 + 5;

struct SegmentTree {
    int N;
    vector<int> sum, delta;

    SegmentTree() {}
    SegmentTree(int N) {
        this->N = 1;
        while (this->N < N) this->N <<= 1;
        sum.resize(2 * this->N + 1);
        delta.resize(2 * this->N + 1);
    }

    void update(int l, int r, int val) {rec(1, 0, N - 1, l, r, val, 0);} //inclusive range

    int query(int l, int r) {return rec(1, 0, N - 1, l, r, 0, 1);} //inclusive range

    void push(int i) {
        delta[2 * i] += delta[i];
        delta[2 * i + 1] += delta[i];
        delta[i] = 0;
    }

    void pull(int i) {
        sum[i] = sum[2 * i] + delta[2 * i] + sum[2 * i + 1] + delta[2 * i + 1];
    }

    int rec(int i, int lo, int hi, int l, int r, int val, int type) {
        if (r < lo || hi < l) return 0;
        if (l <= lo && hi <= r) {
            if (type == 0) delta[i] += val;
            return sum[i] + delta[i];
        }

        push(i);

        int m = (lo + hi) / 2;
        int sumLeft = rec(2 * i, lo, m, l, r, val, type);
        int sumRight = rec(2 * i + 1, m + 1, hi, l, r, val, type);

        pull(i);

        return sumLeft + sumRight;
    }
};

int N, bx, by, lx = 0, ly = 0;
vector<pair<pi, char>> points;
set<pair<int, char>> ver[MAX_N], hor[MAX_N];
vector<pi> path;
bool invalid[4]; // {N, E, S, W}

ll count(vector<pair<int, pi>> h, vector<pair<int, pi>> v) {
	SegmentTree st(MAX_N);
	ll ret = 0;
	vector<pair<int, pi>> query;
	for (auto line: h) {
		query.push_back({line.ss.ff, {1, line.ff}});
		query.push_back({line.ss.ss - 1, {-1, line.ff}});
	}
	sort(query.begin(), query.end());
	sort(v.begin(), v.end());

	int p1 = 0, p2 = 0;
	for (int i = 0; i < MAX_N; ++i) {
		while (p1 < (int)v.size() && v[p1].ff == i) {
			ret += st.query(v[p1].ss.ff + 1, v[p1].ss.ss - 1);
			++p1;
		}
		while (p2 < (int)query.size() && query[p2].ff == i) {
			st.update(query[p2].ss.ss, query[p2].ss.ss, query[p2].ss.ff);
			++p2;
		}
	}

	return ret;
}

bool intersect(pi p1, pi p2, pi x) { // return whether the line p1 - p2 intersects with x
	if (p1 > p2) swap(p1, p2);
	if (p1.ff == x.ff && p2.ff == x.ff && p1.ss < x.ss && x.ss < p2.ss) return true;
	if (p1.ss == x.ss && p2.ss == x.ss && p1.ff < x.ff && x.ff < p2.ff) return true;
	return false;
}

pair<vector<pair<int, pi>>, vector<pair<int, pi>>> gen() { // {hor, ver}
	pair<vector<pair<int, pi>>, vector<pair<int, pi>>> ret;
	for (int i = 0; i < (int)path.size() - 1; ++i) {
		if (path[i].ff == path[i + 1].ff) ret.ss.push_back({path[i].ff, {min(path[i].ss, path[i + 1].ss), max(path[i].ss, path[i + 1].ss)}});
		else ret.ff.push_back({path[i].ss, {min(path[i].ff, path[i + 1].ff), max(path[i].ff, path[i + 1].ff)}});
	}
	return ret;
}

void DFS(int x, int y, char dir) {
	path.push_back({x, y});
	pair<int, char> nxt;
	bool bad = false;
	if (dir == 'N') {
		auto it = ver[x].upper_bound({y, ']'});
		if (it != ver[x].end()) nxt = *it;
		else bad = true, nxt = {MAX_N - 1, '.'};

		if (intersect({x, y}, {x, nxt.ff}, {lx, ly})) nxt.ff = ly, bad = true;
		if (intersect({x, y}, {x, nxt.ff}, {bx, by})) invalid[2] = true, nxt.ff = by, bad = true;

		if (bad) {
			path.push_back({x, nxt.ff});
			return;
		}
		if (nxt.ss == '/') DFS(x, nxt.ff, 'E');
		else DFS(x, nxt.ff, 'W');
	}
	if (dir == 'E') {
		auto it = hor[y].upper_bound({x, ']'});
		if (it != hor[y].end()) nxt = *it;
		else bad = true, nxt = {MAX_N - 1, '.'};

		if (intersect({x, y}, {nxt.ff, y}, {lx, ly})) nxt.ff = lx, bad = true;
		if (intersect({x, y}, {nxt.ff, y}, {bx, by})) invalid[3] = true, nxt.ff = bx, bad = true;

		if (bad) {
			path.push_back({nxt.ff, y});
			return;
		}
		if (nxt.ss == '/') DFS(nxt.ff, y, 'N');
		else DFS(nxt.ff, y, 'S');
	}
	if (dir == 'S') {
		auto it = ver[x].lower_bound({y, '/'});
		if (it != ver[x].begin()) nxt = *prev(it);
		else bad = true, nxt = {0, '.'};

		if (intersect({x, y}, {x, nxt.ff}, {lx, ly})) nxt.ff = ly, bad = true;
		if (intersect({x, y}, {x, nxt.ff}, {bx, by})) invalid[0] = true, nxt.ff = by, bad = true;

		if (bad) {
			path.push_back({x, nxt.ff});
			return;
		}
		if (nxt.ss == '/') DFS(x, nxt.ff, 'W');
		else DFS(x, nxt.ff, 'E');
	}
	if (dir == 'W') {
		auto it = hor[y].lower_bound({x, '/'});
		if (it != hor[y].begin()) nxt = *prev(it);
		else bad = true, nxt = {0, '.'};

		if (intersect({x, y}, {nxt.ff, y}, {lx, ly})) nxt.ff = lx, bad = true;
		if (intersect({x, y}, {nxt.ff, y}, {bx, by})) invalid[1] = true, nxt.ff = bx, bad = true;

		if (bad) {
			path.push_back({nxt.ff, y});
			return;
		}
		if (nxt.ss == '/') DFS(nxt.ff, y, 'S');
		else DFS(nxt.ff, y, 'N');
	}
}

int main() {
	freopen("optics.in", "r", stdin); freopen("optics.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> bx >> by;
	for (int i = 0; i < N; ++i) {
		int x, y; cin >> x >> y;
		char ori; cin >> ori;
		points.push_back({{x, y}, ori});
	}
	points.push_back({{lx, ly}, 'l'}); // the laser
	points.push_back({{bx, by}, 'b'}); // the barn

	// coordinate compression - x coordinate
	sort(points.begin(), points.end());
	int new_x = 0, prevX = -2e9;
	for (int i = 0; i < (int)points.size(); ++i) {
		if (points[i].x1 != prevX) ++new_x;
		prevX = points[i].x1;
		points[i].x1 = new_x;
	}

	// coordinate compression - y coordinate
	sort(points.begin(), points.end(), [](const pair<pi, char>& a, const pair<pi, char>& b) {return a.y1 < b.y1;});
	int new_y = 0, prevY = -2e9;
	for (int i = 0; i < (int)points.size(); ++i) {
		if (points[i].y1 != prevY) ++new_y;
		prevY = points[i].y1;
		points[i].y1 = new_y;
	}

	// extract the barn coordinates and the laser coordinates
	for (int i = 0; i < (int)points.size(); ++i) {
		if (points[i].ss == 'b') {
			bx = points[i].x1, by = points[i].y1;
			points.erase(points.begin() + i);
		}
		if (points[i].ss == 'l') {
			lx = points[i].x1, ly = points[i].y1;
			points.erase(points.begin() + i);
		}
	}

	// fill ver and hor sets
	for (int i = 0; i < (int)points.size(); ++i) {
		ver[points[i].x1].insert({points[i].y1, points[i].ss});
		hor[points[i].y1].insert({points[i].x1, points[i].ss});
	}

	DFS(lx, ly, 'N');
	auto laser = gen();

	ll ans = 0;
	char dir[] = {'N', 'E', 'S', 'W'};
	for (int i = 0; i < 4; ++i) {
		if (invalid[i]) continue;
		path.clear();
		DFS(bx, by, dir[i]);
		auto barn = gen();
		ans += count(laser.ff, barn.ss) + count(barn.ff, laser.ss);
	}

	cout << ans << '\n';

	return 0;
}