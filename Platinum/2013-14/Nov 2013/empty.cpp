#include <bits/stdc++.h>

using namespace std;

#define MAXN 3000000

typedef long long ll;

int N, K;
int barn[MAXN];

int main() {
	//freopen("empty.in", "r", stdin);
	//freopen("empty.out", "w", stdout);

	cin >> N >> K;
	for (int i = 0; i < K; ++i) {
		int x, y, a, b; cin >> x >> y >> a >> b;
		for (int j = 1; j <= y; ++j) {
			barn[((ll)a*j + b) % N] += x;
		}
	}

	//first pass
	for (int i = 0; i < N; ++i) {
		if (barn[i] > 1) {
			barn[(i + 1) % N] += barn[i] - 1;
			barn[i] = 1;
		}
	}

	//second pass
	for (int i = 0; i < N; ++i) {
		if (barn[i] > 1) {
			barn[(i + 1) % N] += barn[i] - 1;
			barn[i] = 1;
		}
	}

	int ans = -1;
	for (int i = 0; i < N; ++i) {
		if (barn[i] == 0) {
			ans = i;
			break;
		}
	}

	cout << ans << "\n";

	return 0;
}