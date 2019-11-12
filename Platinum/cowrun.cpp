#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_N = 1005;
const int ZERO = 500000;

int N, gate;
int cows[MAX_N];
int memo[MAX_N][MAX_N][2];

int dp(int l, int r, int side) {
	if (memo[l][r][side] != -1) return memo[l][r][side];
	int ret = (1 << 27);
	
}

int main() {
	//freopen("cowrun.in", "r", stdin); freopen("cowrun.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N; ++N;
	cows[0] = 0;
	for (int i = 1; i < N; ++i) {
		cin >> cows[i];
		cows[i] += ZERO;
	}
	sort(cows, cows + N);
	gate = lower_bound(cows, cows + N, 0) - cows;
	memset(memo, -1, sizeof(memo));



	return 0;
}