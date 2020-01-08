#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define sz(x) int(x.size())

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-6;
const int MAX_N = 1e5 + 5;

namespace modOp {
    int add(int a, int b, int mod = MOD) {return (a + b) % mod; /*int r = a + b; if (r >= mod) r -= mod; return r;*/}
    void ADD(int& a, int b, int mod = MOD) {a = (a + b) % mod; /*a += b; if (a >= mod) a -= mod;*/}
    int sub(int a, int b, int mod = MOD) {return (a - b + mod) % mod; /*int r = a - b; if (r < 0) r += mod; return r;*/}
    void SUB(int& a, int b, int mod = MOD) {a = (a - b + mod) % mod; /*a -= b; if (a < 0) a += mod;*/}
    int mul(int a, int b, int mod = MOD) {return (ll)a * b % mod;}
    void MUL(int& a, int b, int mod = MOD) {a = (ll)a * b % mod;}
}
using namespace modOp;

int N, M;
vector<int> adjList[MAX_N];
bool found[MAX_N];

int main() {
	//freopen("alliance.in", "r", stdin); freopen("alliance.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int u, v; cin >> u >> v;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	int ans = 1;
	for (int i = 1; i <= N; ++i) {
		if (!found[i]) {
			int edges = 0, sz = 1;
			queue<int> q;
			q.push(i);
			edges += sz(adjList[i]);
			found[i] = true;
			while (!q.empty()) {
				int u = q.front(); q.pop();
				for (int v: adjList[u]) {
					if (!found[v]) {
						q.push(v);
						edges += sz(adjList[v]);
						found[v] = true;
						++sz;
					}
				}
			}
			edges /= 2;
			if (edges > sz) MUL(ans, 0);
			else if (edges == sz) MUL(ans, 2);
			else MUL(ans, sz);
		}
	}

	cout << ans << '\n';

	return 0;
}