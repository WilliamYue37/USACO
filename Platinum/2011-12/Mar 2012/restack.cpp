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
const int MAX_N = 1e5 + 5;

int N;
int S[MAX_N];

int main() {
	//freopen("restack.in", "r", stdin); freopen("restack.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		int a, b; cin >> a >> b;
		S[i] = S[i - 1] + a - b;
	}
	nth_element(S + 1, S + N / 2 + 1, S + N + 1);
	int m = S[N / 2 + 1];
	ll ans = 0;
	for (int i = 1; i <= N; ++i) {
		ans += abs(S[i] - m);
	}
	cout << ans << '\n';

	return 0;
}