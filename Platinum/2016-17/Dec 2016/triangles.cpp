#include <bits/stdc++.h>

using namespace std;

#define MAXN 305
#define x real
#define y imag

typedef long long ll;
typedef pair<int, int> ii;
typedef complex<ll> Point;

int N;
Point points[MAXN];
int below[MAXN][MAXN];
int ans[MAXN];

ll cross(Point a, Point b) {
	return imag(conj(a) * b);
}

bool directlyBelow(Point a, Point b) {
	return a.x() == b.x() && a.y() > b.y();
}

bool betweenBelow(Point a, Point b, Point c) {
	if (a.x() < b.x()) {
		return a.x() < c.x() && c.x() < b.x() && cross(b - a, c - a) < 0;
	}
	else {
		return b.x() < c.x() && c.x() < a.x() && cross(a - b, c - b) < 0;
	}
}

int main() {
	freopen("triangles.in", "r", stdin);
	freopen("triangles.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		int x, y; cin >> x >> y;
		points[i] = Point(x, y);
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (points[i].x() < points[j].x()) {
				for (int k = 0; k < N; ++k) {
					if (k != i && k != j) {
						if (directlyBelow(points[i], points[k])) ++below[i][j];
						if (directlyBelow(points[j], points[k])) ++below[i][j];
						if (betweenBelow(points[i], points[j], points[k])) below[i][j] += 2;
					}
				}
				below[j][i] = -below[i][j];
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			for (int k = j + 1; k < N; ++k) {
				int count = abs(below[i][j] + below[j][k] + below[k][i]) / 2;
				count -= betweenBelow(points[i], points[j], points[k]);
				count -= betweenBelow(points[k], points[i], points[j]);
				count -= betweenBelow(points[j], points[k], points[i]);
				++ans[count];
			}
		}
	}

	for (int i = 0; i <= N - 3; ++i) {
		cout << ans[i] << "\n";
	}
	
	return 0;
}