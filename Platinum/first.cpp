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
const int MAX_N = 3e5 + 5;

int N, cnt = 1;
int trie[MAX_N][26];
vector<string> v[MAX_N], ans;
map<string, int> mp;
bitset<26> fi[MAX_N][26];

void insert(string s) {
	int cur = 0;
	for (char c: s) {
		if (trie[cur][c - 'a'] == 0) trie[cur][c - 'a'] = cnt++;
		cur = trie[cur][c - 'a'];
	}
	v[cur].push_back(s);
}

void dfs(int cur) {
	for (string s: v[cur]) ans.push_back(s);
	if (v[cur].size() != 0) return;
	for (int i = 0; i < 26; ++i) {
		if (trie[cur][i]) {
			bool f = 0;
			for (int j = 0; j < 26; ++j) {
				if (trie[cur][j] > 0 && fi[cur][j][i]) {
					f = true; 
					break;
				}
			}
			if (f) continue;
			for (int j = 0; j < 26; ++j) fi[trie[cur][i]][j] = fi[cur][j];
			for (int j = 0; j < 26; ++j) {
				if (j != i && trie[cur][j] > 0) fi[trie[cur][i]][i][j] = 1;
			}
			for (int j = 0; j < 26; ++j) {
				for (int k = 0; k < 26; ++k) {
					if (fi[trie[cur][i]][k][j]) fi[trie[cur][i]][k] |= fi[trie[cur][i]][j];
				}
			}
			dfs(trie[cur][i]);
		}
	}
}

int main() {
	freopen("first.in", "r", stdin); freopen("first.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		mp[s] = i;
		insert(s);
	}

	dfs(0);

	cout << ans.size() << '\n';
	sort(ans.begin(), ans.end(), [](const string& a, const string& b) {return mp[a] < mp[b];});
	for (string s: ans) cout << s << '\n';

	return 0;
}