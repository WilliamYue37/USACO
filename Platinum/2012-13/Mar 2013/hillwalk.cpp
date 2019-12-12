#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define x1 first.first
#define y1 first.second
#define x2 second.first
#define y2 second.second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-6;
const int MAX_N = 1e5 + 5;

bool equals(ld a, ld b) {
	return abs(a - b) < EPS;
}

int N;
pair<pi, pi> hills[MAX_N];

struct Sol {
    ld m, b;
    int id;

    ld compute(int x) const {
        return m * x + b;
    }

    ld intersect(Sol r) const {
        return (ld)(this->b - r.b)/(r.m - this->m);
    }

    bool operator<(const Sol& other) const {
        return this->m < other.m;
    }
};

class CHT {
public:
    multiset<Sol> hull;

    void insert(Sol part, int x = 0) {
        auto same = hull.lower_bound(part);
        if (same != hull.end() && equals(same->m, part.m) && hills[same->id].x2 > x) {
            if (same->compute(x) >= part.compute(x)) return;
            hull.erase(same);
        }

        auto above = hull.upper_bound(part);
        auto below = hull.lower_bound(part);
        if (above != hull.end() && below != hull.begin() && (--below)->intersect(part) >= part.intersect(*above) && hills[above->id].x2 > x && hills[below->id].x2 > x) return;

        while (true) {
            auto up1 = hull.upper_bound(part);
            if (up1 == hull.end()) break;
            auto up2 = hull.upper_bound(*up1);
            if (up2 == hull.end()) break;

            ld t1 = part.intersect(*up1);
            ld t2 = up1->intersect(*up2);

            if (t1 < t2 && !equals(t1, t2)) break;

            hull.erase(up1);
        }

        while (true) {
            auto lo1 = hull.lower_bound(part);
            if (lo1 == hull.begin()) break; --lo1;
            auto lo2 = hull.lower_bound(*lo1);
            if (lo2 == hull.begin()) break; --lo2;

            ld t1 = lo2->intersect(*lo1);
            ld t2 = lo1->intersect(part);

            if (t1 < t2 && !equals(t1, t2)) break;

            hull.erase(lo1);
        }

        hull.insert(part);
    }

    int query(int x) {
        while (hull.size() >= 2) {
            Sol f = *hull.begin();
            Sol s = *hull.upper_bound(f);
            if (hills[f.id].x2 <= x) hull.erase(hull.begin());
            if (hills[s.id].x2 <= x) hull.erase(hull.upper_bound(f));
            if (f.compute(x) > s.compute(x)) break;
            hull.erase(hull.begin());
        }
        if (hull.size() > 0) {
        	int res = hull.begin()->id;
        	hull.erase(hull.begin());
        	if (hills[res].x2 > x) return res;
        }
        return -1;
    }
};

CHT cht;

Sol line(int i) {
	ld m = (ld)(hills[i].y2 - hills[i].y1) / (hills[i].x2 - hills[i].x1);
	ld b = hills[i].y1 - m * hills[i].x1;
	return {m, b, i};
}

int main() {
	//freopen("hillwalk.in", "r", stdin); freopen("hillwalk.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> hills[i].x1 >> hills[i].y1 >> hills[i].x2 >> hills[i].y2;
	}
	sort(hills, hills + N, [](pair<pi, pi> a, pair<pi, pi> b) {return a.x1 < b.x1;});

	int cur = 0, p1 = 1, ans = 1;
	while (cur != -1) {
		while (p1 < N && hills[p1].x1 <= hills[cur].x2) {
			if (hills[p1].x2 > hills[cur].x2) cht.insert(line(p1), hills[cur].x2);
			++p1;
		}
		int fall = cht.query(hills[cur].x2);
		if (fall == -1) break;
		++ans;
		cur = fall;
		cout << "debug: " << hills[cur].ff.ff << " " << hills[cur].ff.ss << " " << hills[cur].ss.ff << " " << hills[cur].ss.ss << '\n';
	}

	cout << ans << '\n';

	return 0;
}
