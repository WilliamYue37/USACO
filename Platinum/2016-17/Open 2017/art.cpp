#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
#define INF 20000000
#define MAXN 1005

typedef long long ll;
typedef pair<int, int> pi;

struct Rect
{
	int r1, c1, r2, c2;

	Rect() : r1(INF), c1(INF), r2(-1), c2(-1) {}
};

int N;
int total;
int grid[MAXN][MAXN], prefix[MAXN][MAXN], totalCount[MAXN * MAXN];
Rect rects[MAXN * MAXN];
bool possible[MAXN * MAXN];

int main() {
	freopen("art.in", "r", stdin);
	freopen("art.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> grid[i][j];
		}
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			int c = grid[i][j];
			if (c > 0 && totalCount[c] == 0) ++total;
			++totalCount[c];
			rects[c].r1 = min(rects[c].r1, i);
			rects[c].r2 = max(rects[c].r2, i);
			rects[c].c1 = min(rects[c].c1, j);
			rects[c].c2 = max(rects[c].c2, j);
		}
	}

	if (total == 1) {cout << (N == 1 ? 1 : N * N - 1) << "\n"; return 0;}

	for (int c = 1; c <= N * N; ++c) {
		if (totalCount[c] > 0) {
			++prefix[rects[c].r1][rects[c].c1];
			--prefix[rects[c].r1][rects[c].c2 + 1];
			--prefix[rects[c].r2 + 1][rects[c].c1];
			++prefix[rects[c].r2 + 1][rects[c].c2 + 1];
		}
	}

	fill(possible + 1, possible + N * N + 1, true);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			prefix[i][j] += prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
			if (prefix[i][j] >= 2) possible[grid[i][j]] = false;
		}
	}

	int ans = 0;
	for (int i = 1; i <= N * N; ++i) {
		if (possible[i]) ++ans;
	}

	cout << ans << "\n";

	return 0;
}