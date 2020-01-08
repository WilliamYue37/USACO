#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define sz(x) int(x.size())

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-6;
const int MAX_N = 2e4 + 5;

int N;
map<int, vector<int>> mp;
int ans[MAX_N];

int main() {
	//freopen("photo.in", "r", stdin); freopen("photo.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int j = 0; j < 5; ++j) {
		for (int i = 0; i < N; ++i) {
			int cow; cin >> cow;
			if (j == 0) ans[i] = cow;
			mp[cow].push_back(i);
		}
	}

	sort(ans, ans + N, [](int a, int b) {
		int cnt_a = 0, cnt_b = 0;
		for (int i = 0; i < 5; ++i) {
			if (mp[a][i] < mp[b][i]) ++cnt_a;
			else ++cnt_b;
		}
		return cnt_a > cnt_b;
	});

	for (int i = 0; i < N; ++i) cout << ans[i] << '\n';

	return 0;
}