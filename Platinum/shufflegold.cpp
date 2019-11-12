#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define INF 1000000000000000000LL
#define MAXM 100005

typedef long long ll;
typedef pair<int, int> pi;

int N, M, Q;
int sh[MAXM], rsh[MAXM];
vector<int> s;
map<int, int> last;
map<int, int> last2;

vector<int> operator*(vector<int> v1, vector<int> v2) {
	vector<int> ret(M + 1);
	for (int i = 1; i <= M; ++i) {
		if (v1[i] >= 1) ret[i] = v2[v1[i]];
		else ret[i] = v1[i];
	}
	return ret;
}

vector<int> expo(vector<int> base, int e) {
    if (e == 0) {
    	vector<int> one(M + 1);
    	for (int i = 1; i <= M; ++i) one[i] = i;
    	return one;
    }
    if (e == 1) return base;
    vector<int> ans = expo(base, e / 2);
    ans = ans * ans;
    if (e % 2 == 1) ans = ans * base;
    return ans;
}

int main() {
	freopen("shufflegold.in", "r", stdin);
	freopen("shufflegold.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M >> Q;
	s = vector<int>(M + 1);
	for (int i = 1; i <= M; ++i) {
		cin >> sh[i];
		rsh[sh[i]] = i;
		s[i] = sh[i] - 1;
	}

	int length = 0, p1 = M, p2;
	while (p1 != 0) {
		++length;
		p1 = sh[p1] - 1;
	}

	vector<int> first; p1 = 0, p2 = N - length + 1;
	while (first.size() < length) {
		p1 = rsh[++p1];
		first.push_back(p1);
		last2[(N - M + sh[p1] - 1) + 1] = p2++;
	}

	s = expo(s, N - M + 1);
	for (int i = 1; i <= M; ++i) {
		if (s[i] >= 1) last[(N - M + 1) + s[i]] = i;
	}

	for (int q = 0; q < Q; ++q) {
		int pos; cin >> pos; pos = N + 1 - pos;
		if (pos > length && pos <= N - M + 1) {
			cout << pos + (M - length) << '\n';
		}
		else if (pos > N - M + 1) {
			if (last.count(pos) != 0) cout << last[pos] << '\n';
			else cout << last2[pos] << '\n';
		}
		else if (pos <= length) {
			cout << first[pos - 1] << '\n';
		}
	}

	return 0;
}