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
const int MAX_K = 1000 + 5;
const int MAX_ID = 300 + 5;

int N, K;
map<int, string> idToS;
map<string, int> sToId;
set<int> points;
int dp[MAX_K][MAX_ID];

int main() {
	//freopen("combos.in", "r", stdin); freopen("combos.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	int id = 1;
	// input an empty string as id 0
	idToS[0] = "";
	sToId[""] = 0;
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		string tmp = "";
		for (int j = 0; j < (int)s.size(); ++j) {
			tmp += s[j];
			if (sToId.count(tmp) != 0) continue;
			idToS[id] = tmp;
			sToId[tmp] = id;
			++id;
		}
		points.insert(sToId[s]);
	}

	for (int i = 0; i < K; ++i) {
		for (int j = 0; j < id; ++j) {
			string s = idToS[j];
			if ((int)s.size() > i) continue;
			for (char c: {'A', 'B', 'C'}) {
				string n_s = s + c;
				// find new id
				int n_id = 0, p = 0;
				for (int k = 0; k < (int)n_s.size(); ++k) {
					if (sToId.count(n_s.substr(k, (int)n_s.size() - k)) != 0) {
						if (n_id == 0) n_id = sToId[n_s.substr(k, (int)n_s.size() - k)];
						if (points.count(sToId[n_s.substr(k, (int)n_s.size() - k)]) != 0) ++p;
					}
				}
				dp[i + 1][n_id] = max(dp[i + 1][n_id], dp[i][j] + p);
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < id; ++i) ans = max(ans, dp[K][i]);
	cout << ans << '\n';

	return 0;
}