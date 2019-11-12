#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define INF 1000000000000000000LL
#define MAXN 505

typedef long long ll;
typedef pair<int, int> pi;

int N;
pi degree[MAXN];
vector<int> ans;

bool check(int remove) {
    vector<int> freq(MAXN); //MAXNUM is the largest degree value
    ll sum = 0;
    for (int i = 0; i < N; ++i) {
    	if (i != remove) {
			++freq[degree[i].ff];
			sum += degree[i].ff;
		}
    }
    if (sum % 2 == 1) return false; 
    long long left = 0, right = 0; int less = 0;
    for (int k = 1, i = 0; k <= N - 1 && i < N; ++i) {
        if (i != remove) {
        	left += degree[i].ff;
	        --freq[degree[i].ff];
	        right -= min(degree[i].ff, k - 1);
	        if (degree[i].ff < k - 1) --less;
	        less += freq[k - 1];
	        right += (N - 1) - k - less;
	        if (left > (long long)k * (k - 1) + right) return false;
	        ++k;
        }
    }
    return true;
}


int main() {
	freopen("fcount.in", "r", stdin);
	freopen("fcount.out", "w", stdout);

	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N; ++N;
	for (int i = 0; i < N; ++i) {
		int d; cin >> d;
		degree[i] = {d, i};
	}
	sort(degree, degree + N, greater<pi>());

	for (int i = 0; i < N; ++i) if (check(i)) ans.push_back(degree[i].ss);

	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (int i = 0; i < ans.size(); ++i) cout << ans[i] + 1 << '\n';

	return 0;
}