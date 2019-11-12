#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const ld PI = 4 * atan((ld)1);
const int MAX_N = 1e6 + 5;

int N;
double prob[MAX_N];
double ans = 0;

int main() {
	freopen("cowdate.in", "r", stdin); freopen("cowdate.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> prob[i];
		prob[i] *= 0.000001;
	}

	int p1 = 0, p2 = 0; //inclusive, exclusive
	double p = 1, s = 0, ans = 0;
	while (p2 < N) {
		while (p2 < N && s < 1) {
			s += prob[p2] / (1 - prob[p2]);
			p *= (1 - prob[p2]);
			++p2;
		}
		ans = max(ans, p * s);
		s -= prob[p1] / (1 - prob[p1]);
		p /= (1 - prob[p1]);
		++p1;
	}

	cout << (int)(ans * 1e6) << '\n';

	return 0;
}