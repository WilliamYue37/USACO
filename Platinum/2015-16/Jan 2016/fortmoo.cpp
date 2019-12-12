#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

#define MAXN 205
#define MAXM 205

typedef long long ll;
typedef pair<int, int> pi;

int N, M;
char grid[MAXN][MAXM];
int row[MAXN][MAXM], col[MAXN][MAXM]; //prefix arrays

bool valid(int r1, int c1, int r2, int c2) {
	bool ret = true;
	if (row[r1][c2] - row[r1][c1 - 1] != 0) ret = false;
	if (row[r2][c2] - row[r2][c1 - 1] != 0) ret = false;
	if (col[r2][c1] - col[r1 - 1][c1] != 0) ret = false;
	if (col[r2][c2] - col[r1 - 1][c2] != 0) ret = false;
	return ret;
} 

int main() {
	freopen("fortmoo.in", "r", stdin);
	freopen("fortmoo.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> M;
	for (int r = 1; r <= N; ++r) {
		for (int c = 1; c <= M; ++c) {
			cin >> grid[r][c];
			row[r][c] = grid[r][c] == 'X' ? 1 : 0;
			col[r][c] = grid[r][c] == 'X' ? 1 : 0;
		}
	}

	for (int r = 1; r <= N; ++r) {
		for (int c = 1; c <= M; ++c) {
			++b;
			row[r][c] += row[r][c - 1];
		}
	}

	for (int c = 1; c <= M; ++c) {
		for (int r = 1; r <= N; ++r) {
			++b;
			col[r][c] += col[r - 1][c];
		}
	}

	int ans = 0; 	
	for (int r1 = 1; r1 <= N; ++r1) {
		for (int c1 = 1; c1 <= M; ++c1) { if (grid[r1][c1] != 'X')
			for (int r2 = r1; r2 <= N; ++r2) { if (col[r2][c1] - col[r1 - 1][c1] == 0 && (r2 - r1 + 1) * M > ans)
				for (int c2 = c1; c2 <= M; ++c2) {
					if (valid(r1, c1, r2, c2)) ans = max(ans, (r2 - r1 + 1) * (c2 - c1 + 1));
				}
			}
		}
	}

	cout << ans << "\n";

	return 0;
}