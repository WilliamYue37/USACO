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
const int MAX_N = 20;

int N;
bool good[1 << MAX_N];

vector<pi> subsets(vector<int>& S) {
	vector<pi> ret;
	for (int mask = 0; mask < (1 << S.size()); ++mask) {
		for (int j = mask; ; j = (j - 1) & mask) {
			int sum = 0;
			for (int k = 0; k < S.size(); ++k) {
				if (j & (1 << k)) sum -= S[k];
				else if (mask & (1 << k)) sum += S[k];
			}
			if (sum >= 0) ret.push_back({sum, mask});
			if (j == 0) break;
		}
	}
	sort(ret.begin(), ret.end());
	ret.resize(unique(ret.begin(), ret.end()) - ret.begin());
	return ret;
}

int main() {
	//freopen("subsets.in", "r", stdin); freopen("subsets.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	vector<int> A, B;
	for (int i = 0; i < N; ++i) {
		int cow; cin >> cow;
		if (i & 1) A.push_back(cow);
		else B.push_back(cow);
	}

	vector<pi> L = subsets(A), R = subsets(B);

	int p1 = 0, p2 = 0;
	while (p1 < L.size() && p2 < R.size()) {
		if (L[p1].ff < R[p2].ff) ++p1;
		else if (L[p1].ff > R[p2].ff) ++p2;
		else {
			int temp1 = p1, temp2 = p2;
			while (temp1 < L.size() && L[temp1].ff == L[p1].ff) ++temp1;
			while (temp2 < R.size() && R[temp2].ff == R[p2].ff) ++temp2;
			for (int i = p1; i < temp1; ++i) {
				for (int j = p2; j < temp2; ++j) {
					good[L[i].ss | (R[j].ss << A.size())] = true;
				}
			}
			p1 = temp1, p2 = temp2;
		}
	}

	cout << count(good + 1, good + (1 << MAX_N), true) << '\n';

	return 0;
}