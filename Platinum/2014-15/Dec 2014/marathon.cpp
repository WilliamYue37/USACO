#include <bits/stdc++.h>

using namespace std;

#define MAXN 100010

struct Point {
	int x, y;
};

int dist(Point &p1, Point &p2) {
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int N, Q;
Point point[MAXN];
int BIT[MAXN];

int query(int index) {
	++index; int sum = 0;
	while (index > 0) {
		sum += BIT[index];
		index -= index & -index;
	}
	return sum;
}

void update(int index, int newVal) {
	int val = newVal - (query(index) - query(index - 1));
	++index;
	while (index <= MAXN) {
		BIT[index] += val;
		index += index & -index;
	}
}

class SegmentTree {
public:
	int n;
	int lo[4 * MAXN + 1], hi[4 * MAXN + 1], maximum[4 * MAXN + 1];

	SegmentTree(int n) {
		this->n = n;
		init(1, 0, n - 1);
	}

	void update(int a, int b) {
		update(1, a, b);
	}

	int getMax(int a, int b) {
		return getMax(1, a, b);
	}

	void init(int i, int a, int b) {
		lo[i] = a;
		hi[i] = b;

		if (a == b)
			return;

		int m = (a + b) / 2;
		init(2 * i, a, m);
		init(2 * i + 1, m + 1, b);
	}

	void update(int i, int a, int b) {
		if (b < lo[i] || hi[i] < a)
			return;

		if (a <= lo[i] && hi[i] <= b) {
			if (0 < a && a < N - 1) maximum[i] = dist(point[a - 1], point[a]) + dist(point[a], point[a + 1]) - dist(point[a - 1], point[a + 1]);
			return;
		}

		update(2 * i, a, b);
		update(2 * i + 1, a, b);

		//update
		maximum[i] = max(maximum[2 * i], maximum[2 * i + 1]);
	}

	int getMax(int i, int a, int b) {
		if (b < lo[i] || hi[i] < a)
			return 0;
		if (a <= lo[i] && hi[i] <= b) {
			return maximum[i];
		}

		int maxLeft = getMax(2 * i, a, b);
		int maxRight = getMax(2 * i + 1, a, b);

		return max(maxLeft, maxRight);
	}
};

SegmentTree stSkip(MAXN);

int main() {
	freopen("marathon.in", "r", stdin);
	freopen("marathon.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> N >> Q;
	for (int i = 0; i < N; ++i) {
		int x, y; cin >> x >> y;
		point[i] = { x, y };
	}

	for (int i = 0; i < N - 1; ++i) {
		stSkip.update(i, i);
		update(i, dist(point[i], point[i + 1]));
	}

	for (int i = 0; i < Q; ++i) {
		char type; cin >> type;
		if (type == 'U') {
			int id, x, y; cin >> id >> x >> y; --id;
			point[id] = {x, y};
			if (id > 0) update(id - 1, dist(point[id - 1], point[id]));
			update(id, dist(point[id], point[id + 1]));
			stSkip.update(id - 1, id - 1);
			stSkip.update(id, id);
			stSkip.update(id + 1, id + 1);
		}
		else {
			int start, end; cin >> start >> end; --start, --end;
			cout << query(end - 1) - query(start - 1) - stSkip.getMax(start + 1, end - 1) << "\n";
		}
	}

	return 0;
}