#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005
#define MAXK 100005

typedef long long ll;
typedef pair<int, int> ii;

int N, K;
vector<int> controllers[MAXN];

ll budget;
int cowsFound;

bool canForm(int i, ll cost) {
	if (cost > budget) return false;

	if (i == N) {
		++cowsFound;
		return cowsFound >= K;
	}

	if (controllers[i].size() > 1 && controllers[i][1] + cost > budget) {
		++cowsFound;
		return cowsFound >= K;
	}

	for (int v: controllers[i]) {
		if (canForm(i + 1, cost + v)) return true;
	}

	return false;
}

ll savings;
void calcSavings(int i, int cost) {
	if (cost >= budget) return;

	if (i == N) {
		savings += (budget - cost);
		return;
	}

	if (controllers[i].size() > 1 && controllers[i][1] + cost > budget) {
		savings += (budget - cost);
		return;
	}

	for (int v: controllers[i]) {
		calcSavings(i + 1, cost + v);
	}
}

bool compare(const vector<int>& a, const vector<int>& b) {
	for (int i = 0; i < min(a.size(), b.size()) - 1; ++i) {
		int d1 = a[i + 1] - a[i];
		int d2 = b[i + 1] - b[i];
		if (d1 != d2) return d1 < d2;
	}
	return a.size() < b.size();
}

int main() {
	
	freopen("7.in", "r", stdin);
	freopen("7.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	cin >> N >> K;
	ll lo = 0, hi = 0;
	ll baseLine = 0;
	for (int i = 0; i < N; ++i) {
		int M; cin >> M;
		for (int j = 0; j < M; ++j) {
			int cost; cin >> cost;
			controllers[i].push_back(cost);
		}
		sort(controllers[i].begin(), controllers[i].end());

		baseLine += controllers[i][0];
		for (int j = M - 1; j >= 0; --j) {
			controllers[i][j] -= controllers[i][0];
		}

		hi += controllers[i][M - 1];
	}

	sort(controllers, controllers + N, compare);

	while (lo < hi) {
		budget = (lo + hi) / 2;
		cowsFound = 0;
		if (canForm(0, 0)) {
			hi = budget;
		}
		else {
			lo = budget + 1;
		}
	}

	ll mostExpensive = hi + baseLine;
	ll overCost = mostExpensive * K;

	savings = 0;
	budget = hi;
	calcSavings(0, 0);

	ll result = overCost - savings;
	cout << result << "\n";

	return 0;
}