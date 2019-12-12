#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005

typedef long long ll;
typedef pair<int, int> ii;

int N;
int arr[MAXN], idx[MAXN], precomp[MAXN];

bool compare(int a, int b) {
	return (arr[a] == arr[b] ? a < b : arr[a] < arr[b]);
}

int main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
		idx[i] = i;
	}

	sort(idx, idx + N, compare);

	int maximum = 0;
	for (int i = 1; i < N; ++i) {
		maximum = max(maximum, idx[i-1]);
		precomp[i] = maximum + 1 - i;
	}

	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		int res = 0;
		if (i > 0) res = max(res, precomp[i]);
		if (i < N - 1) res = max(res, precomp[i + 1]);
		if (res == 0 && N > 1) ++res;
		ans += res;
	}

	cout << ans << "\n";

	return 0;
}