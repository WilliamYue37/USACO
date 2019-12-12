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
const int MAX_N = 25005;

ll A, B, N, M;
vector<ll> ver, hor;s

int main() {
	freopen("fencedin.in", "r", stdin); freopen("fencedin.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> A >> B >> N >> M;
	ver = vector<ll>(N + 1), hor = vector<ll>(M + 1);
	for (int i = 0; i < N; ++i) {
		cin >> ver[i];
	}
	for (int i = 0; i < M; ++i) {
		cin >> hor[i];
	}

	sort(ver.begin(), ver.end());
	for (int i = 0; i < N; ++i) {
		ver[i] = ver[i + 1] - ver[i];
	}
	ver[N] = A - ver[N];

	sort(hor.begin(), hor.end());
	for (int i = 0; i < M; ++i) {
		hor[i] = hor[i + 1] - hor[i];
	}
	hor[M] = B - hor[M];

	sort(ver.begin(), ver.end()); sort(hor.begin(), hor.end());
	ll ans = ver[0] * M + hor[0] * N;
	for (int i = 1, j = 1; i < ver.size() && j < hor.size();) {
		if (ver[i] < hor[j]) {
			ans += ver[i++] * (M - j + 1);
		}
		else {
			ans += hor[j++] * (N - i + 1);
		}
	}

	cout << ans << '\n';

	return 0;
}