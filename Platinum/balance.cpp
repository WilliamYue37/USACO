#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define MAXN 100005

typedef long long ll;
typedef pair<int, int> pi;

int N;
ll f[MAXN];
vector<int> hull;
int l[MAXN];
int r[MAXN];

int main() {
	freopen("balance.in", "r", stdin);
	freopen("balance.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> f[i];

	hull.push_back(0);
	for (int k = 1; k <= N + 1; ++k) {
		while (hull.size() >= 2) {
			int i = hull[hull.size() - 2];
			int j = hull[hull.size() - 1];
			if ((k - i) * f[j] < (j - i) * f[k] + (k - j) * f[i]) hull.pop_back();
			else break;
		}
		hull.push_back(k);
	}

	for (int j = 0; j < hull.size() - 1; ++j) {
		for (int i = hull[j] + 1; i < hull[j + 1]; ++i) {
			l[i] = hull[j];
			r[i] = hull[j + 1];
		}
		l[hull[j]] = r[hull[j]] = hull[j];
	}
	l[N + 1] = r[N + 1] = N + 1;
	for (int i = 1; i <= N; ++i) {
		if (l[i] == r[i]) cout << 100000ll * f[i] << '\n';
		else cout << 100000 * ((r[i] - i) * f[l[i]] + (i - l[i]) * f[r[i]]) / (r[i] - l[i]) << '\n'; 
	}

	return 0;

}