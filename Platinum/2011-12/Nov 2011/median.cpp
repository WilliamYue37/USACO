#include <bits/stdc++.h>

using namespace std;

#define MAXN 100010

int N, X;
int pre[MAXN];

int BIT[MAXN * 2];

int query(int index) {
	index += N; int sum = 0;
	while (index > 0) {
		sum += BIT[index];
		index -= index & -index;
	}
	return sum;
}

void update(int index, int val) {
	index += N;
	while (index <= MAXN * 2) {
		BIT[index] += val;
		index += index & -index;
	}
}

int main() {
	//freopen("median.in", "r", stdin);
	//freopen("median.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N >> X;
	for (int i = 1; i <= N; ++i) {
		int h; cin >> h;
		pre[i] = pre[i-1] + (h >= X ? 1 : -1);
	}

	long long ans = 0; update(0, 1);
	for (int i = 1; i <= N; ++i) {
		ans += query(pre[i]);
		update(pre[i], 1);
	}

	cout << ans << "\n";

	return 0;
}