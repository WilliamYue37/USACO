#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_N = 3e4 + 5;
const int MAX_K = 7;
const int MAX_COMB = 262145;

int N, K;
int hor[MAX_N][MAX_K], ver[MAX_N][MAX_K];

int c[8];
void decode(int x) {
	for (int i = 0; i < K; ++i) {
		c[i] = x >> (3 * i) & 7;
	}
}

int visited[20], mapped[20], stamp;
int encode() {
	++stamp;
	int cnt = 0, ret = 0;
	for (int i = 0; i < K; ++i) {
		if (visited[c[i]] != stamp) {
			visited[c[i]] = stamp;
			mapped[c[i]] = cnt++;
		}
		c[i] = mapped[c[i]];
		ret |= c[i] << (3 * i);
	}
	return ret;
}

pair<ll, int> add(pair<ll, int> a, pair<ll, int> b) {
	if (a.ff == b.ff) return {a.ff, (a.ss + b.ss) % MOD};
	else if (a.ff < b.ff) return a;
	else return b;
}

int stateid[MAX_COMB];
int stateis[MAX_COMB];
int trans[132][6][4];
int cnt = 0;

int a[10];
bool ok() {
	for (int i = 0; i < K; ++i) {
		for (int j = i + 1; j < K; ++j) {
			for (int k = j + 1; k < K; ++k) {
				for (int l = k + 1; l < K; ++l) {
					if (a[i] == a[k] && a[j] == a[l] && a[i] != a[j]) return false;
				}
			}
		}
	}
	return true;
}

void dfs(int x, int y, int z) {
	if (x == K) {
		if (ok()) {
			stateid[z] = cnt;
			stateis[cnt] = z;
			++cnt;
		}
	}
	else {
		for (int i = 0; i <= y; ++i) {
			a[x] = i;
			dfs(x + 1, max(i + 1, y), z | (i << (3 * x)));
		}
	}
}

pair<ll, int> dp[2][132];
void insert(int enc, pair<ll, int> d) {
	enc = stateid[enc];
	dp[1][enc] = add(dp[1][enc], d);
}

int main() {
	freopen("escape.in", "r", stdin);
	freopen("escape.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		for (int j = 1; j < K; ++j) {
			cin >> hor[i][j];
		}
	}
	for (int j = 0; j < K; ++j) {
		for (int i = 1; i < N; ++i) {
			cin >> ver[i][j];
		}
	}

	memset(stateid, -1, sizeof stateid);
	dfs(0, 0, 0);
	for (int j = 0; j < K; ++j) {
		for (int k = 0; k < cnt; ++k) {
			//no up, no left
			int cnt = 0;
			for (int l = 0; l < K; ++l) {
				if ((stateis[k] >> (3 * l) & 7) == (stateis[k] >> (3 * j) & 7)) ++cnt;
			}
			if (cnt > 1) {
				decode(stateis[k]);
				c[j] = 17;
				trans[k][j][0] = encode();
			}
			else {
				trans[k][j][0] = -1;
			}

			//no up, left
			trans[k][j][1] = stateis[k];

			//up, no left
			if (j > 0) {
				decode(stateis[k]);
				int cnt = 0;
				for (int l = 0; l < K; ++l) {
					if (c[l] == c[j]) ++cnt;
				}
				if (cnt > 1) {
					c[j] = c[j - 1];
					trans[k][j][2] = encode();
				}
				else {
					trans[k][j][2] = -1;
				}
			}
			else {
				trans[k][j][2] = -1;
			}

			//up, left
			if (j > 0) {
				decode(stateis[k]);
				if (c[j] != c[j - 1]) {
					int cj = c[j];
					for (int l = 0; l < K; ++l) {
						if (c[l] == cj) {
							c[l] = c[j - 1];
						}
					}
					trans[k][j][3] = encode();
				}
				else {
					trans[k][j][3] = -1;
				}
			}
			else {
				trans[k][j][3] = -1;
			}
		}
	}

	for (int k = 0; k < cnt; ++k) dp[0][k] = {1e18, 0};
	dp[0][0] = {0, 1};
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) {
			if (i == 0 && j == 0) continue;
			for (int k = 0; k < cnt; ++k) {
				dp[1][k] = {1e18, 0};
			}
			for (int k = 0; k < cnt; ++k) {
				if (dp[0][k].ff == 1e18 || dp[0][k].ss == 0) continue;

				//no up, no left
				if (trans[k][j][0] != -1) {
					insert(trans[k][j][0], dp[0][k]);
				}

				//no up, left
				if (i > 0 && trans[k][j][1] != -1) {
					insert(trans[k][j][1], {dp[0][k].ff + ver[i][j], dp[0][k].ss});
				}


				//up, no left
				if (trans[k][j][2] != -1) {
					insert(trans[k][j][2], {dp[0][k].ff + hor[i][j], dp[0][k].ss});
				}

				//up, left
				if (i > 0 && trans[k][j][3] != -1) {
					insert(trans[k][j][3], {dp[0][k].ff + hor[i][j] + ver[i][j], dp[0][k].ss});
				}
			}
			swap(dp[0], dp[1]);
		}
	}

	cout << dp[0][0].ss << '\n';

	return 0;
}