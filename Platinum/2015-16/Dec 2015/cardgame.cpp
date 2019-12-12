#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
#define MAXN 50005

typedef long long ll;
typedef pair<int, int> pi;

int N;
int elsie[MAXN];
set<int> bessie;
bool cards[2 * MAXN];
int prefix[MAXN], suffix[MAXN];

int main() {
	freopen("cardgame.in", "r", stdin);
	freopen("cardgame.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	int N; cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> elsie[i];
		cards[elsie[i]] = true;
	}

	for (int i = 1; i <= 2 * N; ++i) if (!cards[i]) bessie.insert(i);

	for (int i = 1; i <= N; ++i) {
		set<int>::iterator idx = bessie.upper_bound(elsie[i]);
		if (idx == bessie.end()) {
			prefix[i] = prefix[i - 1];
		}
		else {
			prefix[i] = prefix[i - 1] + 1;
			bessie.erase(idx);
		}
	}

	for (int i = 1; i <= 2 * N; ++i) if (!cards[i]) bessie.insert(i);

	for (int i = N; i >= 1; --i) {
		set<int>::iterator idx = bessie.lower_bound(elsie[i]);
		if (idx == bessie.begin()) {
			suffix[i] = suffix[i + 1];
		}
		else {
			suffix[i] = suffix[i + 1] + 1;
			bessie.erase(--idx);
		}
	}

	int ans = 0;
	for (int i = 1; i <= N + 1; ++i) {
		ans = max(ans, prefix[i - 1] + suffix[i]);
	}

	cout << ans << "\n";

	return 0;
}