#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define f first
#define s second

#define MAXN 100005
#define MAXT 100005

typedef long long ll;
typedef pair<int, int> pi;
typedef tree<pi, null_type, less<pi>, rb_tree_tag, tree_order_statistics_node_update> OST;

int N, T, nex = 0;
OST s[MAXN];
ll ans = 0;
vector<pair<pi, pi>> vert, hor;
//vertical - x-coor, time, low y, high y
//horizontal - x-coor, insert/delete, time, y

int query(int time, int y) {
	int ret = 0;
	while (time > 0) {
		ret += s[time].order_of_key({y + 1, 0});
		time -= time & -time;
	}
	return ret;
}

void update(int time, int y, int delta) {
	while (time <= N) {
		if (delta == 1) s[time].insert({y, nex++});
		else s[time].erase(s[time].lower_bound({y, 0}));
		time += time & -time;
	}
}

int main() {
	freopen("mowing.in", "r", stdin);
	freopen("mowing.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> T;
	int prevX, prevY;
	for (int i = 0; i < N; ++i) {
		int x, y; cin >> x >> y;
		if (i != 0) {
			if (x == prevX) {
				vert.push_back({{x, i}, {min(y, prevY) + 1, max(y, prevY) - 1}});
			}
			else if (min(x, prevX) + 1 != max(x, prevX)) {
				hor.push_back({{min(x, prevX) + 1, 1}, {i, y}});
				hor.push_back({{max(x, prevX), -1}, {i, y}});
			}
		}
		prevX = x, prevY = y;
	}

	sort(vert.begin(), vert.end());
	sort(hor.begin(), hor.end());
	
	int idx = -1;
	for (auto a: vert) {
		while ((idx + 1) < hor.size() && hor[idx + 1].f.f <= a.f.f) {
			++idx;
			update(hor[idx].s.f, hor[idx].s.s, hor[idx].f.s);
		}
		if (a.f.s + T < N) {
			ans += query(N - 1, a.s.s) - query(N - 1, a.s.f - 1);
			ans -= query(a.f.s + T - 1, a.s.s) - query(a.f.s + T - 1, a.s.f - 1);
		}
		if (a.f.s > T) {
			ans += query(a.f.s - T, a.s.s) - query(a.f.s - T, a.s.f - 1);
		}
	}

	cout << ans << "\n";

	return 0;
}