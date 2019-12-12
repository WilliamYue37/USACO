#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_K = 11;
const int MAX_M = 50005;

int K, M;
string strings[MAX_K];
vector<int> pre; //prefix sums
int L[MAX_K][2 * MAX_M];
map<vector<int>, pi> mp;

int main() {
	freopen("cbs.in", "r", stdin);
	freopen("cbs.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> K >> M;
	for (int i = 0; i < K; ++i) cin >> strings[i];

	int ans = 0;
	pre = vector<int>(K, M);
	for (int i = 0; i < K; ++i) fill(L[i], L[i] + 2 * MAX_M, M);
	for (int i = 0; i < K; ++i) L[i][M] = 0;

	mp[pre] = {0, 1};
	for (int i = 0; i < M; ++i) {
		int left = 0;
		for (int j = 0; j < K; ++j) {
			if (strings[j][i] == '(') {
				L[j][++pre[j]] = i + 1;
			}
			else {
				--pre[j];
				L[j][pre[j]] = min(L[j][pre[j]], i + 1);
			}
			left = max(left, L[j][pre[j]]);
		}
		if (left == M) continue;

		pi &val = mp[pre];
		if (val.ff == left) ans += val.ss++;
		else val = {left, 1};
	}

	cout << ans << '\n';

	return 0;
}