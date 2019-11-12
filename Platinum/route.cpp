#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-6;
const int MAX_N = 4e4 + 5;

int A, B, E, ans = 0;
int L[MAX_N], R[MAX_N], dpL[MAX_N], dpR[MAX_N];
vector<int> adjListL[MAX_N], adjListR[MAX_N];

int main() {
	freopen("route.in", "r", stdin); freopen("route.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> A >> B >> E;
	for (int i = 1; i <= A; ++i) {
		cin >> L[i];
		dpL[i] = L[i];
		ans = max(ans, L[i]);
	}
	for (int i = 1; i <= B; ++i) {
		cin >> R[i];
		dpR[i] = R[i];
		ans = max(ans, R[i]);
	}
	for (int i = 0; i < E; ++i) {
		int u, v; cin >> u >> v;
		adjListL[u].push_back(v);
		adjListR[v].push_back(u);
	}
	for (int i = 1; i <= A; ++i) sort(adjListL[i].begin(), adjListL[i].end());
	for (int i = 1; i <= B; ++i) sort(adjListR[i].begin(), adjListR[i].end());

	
	for (int i = 1; i <= A; ++i) {
		for (int j: adjListL[i]) {
			int tmpL = dpR[j] + L[i];
			int tmpR = dpL[i] + R[j];
			dpL[i] = max(dpL[i], tmpL);
			dpR[j] = max(dpR[j], tmpR);
			ans = max({ans, dpL[i], dpR[j]});
		}
	}

	cout << ans << '\n';

	return 0;
}