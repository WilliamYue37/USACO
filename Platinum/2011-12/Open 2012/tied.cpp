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
const int MAX_N = 10;
const int MAX_M = 1e4;

int N, M, bx, by;
pi poles[MAX_N], rope[MAX_M];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M >> bx >> by;
	for (int i = 0; i < N; ++i) {
		cin >> poles[i].ff >> poles[i].ss;
	}
	for (int i = 0; i <= M; ++i) {
		cin >> rope[i].ff >> rope[i].ss;
	}

	for (int mask = 0; mask < (1 << N); ++mask) {
		
	}

	return 0;
}