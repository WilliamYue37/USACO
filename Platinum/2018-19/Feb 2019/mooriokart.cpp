#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;

const int MOD = 1000000007;
const ll INF = 1000000000000000000LL;
const int MAX_N = 1505;
const int MAX_Y = 2505;

namespace modOp {
    int add(int a, int b, int mod = MOD) { return (a + b) % mod; }
    int sub(int a, int b, int mod = MOD) { return (a - b + mod) % mod; }
    int mul(int a, int b, int mod = MOD) { return (ll)a * b % mod; }
}
using namespace modOp;

pair<int, int> operator+(const pair<int, int>& l, const pair<int, int>& r) {
	return {add(l.first, r.first), add(l.second, r.second)};
}

pair<int, int> operator+=(pair<int, int>& l, const pi& r) {
	return l = l + r;
}

pi augment(pi a, pi b) {
    return {add(mul(a.ff, b.ss), mul(a.ss, b.ff)), mul(a.ss, b.ss)};
}

int N, M, X, Y, K;
vector<pi> adjList[MAX_N];
vector<int> component;
map<int, pi> paths;
bool found[MAX_N];
pi dp[MAX_Y];

void dfs1(int u) {
	component.push_back(u);
	found[u] = true;
	for (auto e: adjList[u]) {
		if (!found[e.ff]) dfs1(e.ff);
	}
}

void dfs2(int u, int p, int orig, int d = 0) {
	for (auto e: adjList[u]) {
		if (e.ff != p) {
			if (orig < e.ff) paths[min(Y, d + e.ss)] += {d + e.ss, 1};
			dfs2(e.ff, u, orig, d + e.ss);
		}
	}
}

int main() {
	freopen("mooriokart.in", "r", stdin); freopen("mooriokart.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M >> X >> Y; K = N - M;
	for (int i = 0; i < M; ++i) {
		int a, b, d; cin >> a >> b >> d;
		adjList[a].push_back({b, d});
		adjList[b].push_back({a, d});
	}
	
	dp[min(K * X, Y)] = {K * X, 1};
	for (int u = 1; u <= N; ++u) {
		if (found[u]) continue;
		component.clear();
		paths.clear();
		dfs1(u);
		for (int i = 0; i < component.size(); ++i) {
			dfs2(component[i], -1, component[i]);
		}
		pi temp[MAX_Y];
		for (auto dist: paths) {
			for (int i = 0; i <= Y; ++i) {
				temp[min(Y, i + dist.ff)] += augment(dp[i], dist.ss);
			}
		}
		for (int i = 0; i <= Y; ++i) dp[i] = temp[i];
	}
	for (int i = 0; i < K - 1; ++i) dp[Y].ff = mul(dp[Y].ff, 2);
	for (int i = 1; i < K; ++i) dp[Y].ff = mul(dp[Y].ff, i);

	cout << dp[Y].ff << '\n';

	return 0;
}