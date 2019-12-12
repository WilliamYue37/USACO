#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005

typedef long long ll;
typedef pair<int, int> pi;

class BIT {
public:
	int BIT[MAXN];

	int query(int index) {
		++index; int sum = 0;
		while (index > 0) {
			sum += BIT[index];
			index -= index & -index;
		}
		return sum;
	}

	void update(int index, int val) {
		++index;
		while (index <= MAXN) {
			BIT[index] += val;
			index += index & -index;
		}
	}
};

int N;
int side1[MAXN], side2[MAXN], side1Loc[MAXN], side2Loc[MAXN];
BIT bit;

int main() {
	freopen("mincross.in", "r", stdin);
	freopen("mincross.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> side1[i];
	for (int i = 0; i < N; ++i) cin >> side2[i];

	for (int i = 0; i < N; ++i) {
		side1Loc[side1[i]] = i;
		side2Loc[side2[i]] = i;
	}

	ll total = 0;
	for (int i = 0; i < N; ++i) {
		total += bit.query(N - 1) - bit.query(side2Loc[side1[i]]);
		bit.update(side2Loc[side1[i]], 1);
	}

	ll ans = total, val = total;
	for (int i = 0; i < N; ++i) {
		val += (ll)(N - 1 - side2Loc[side1[i]]) - side2Loc[side1[i]];
		ans = min(ans, val);
	}

	val = total;
	for (int i = 0; i < N; ++i) {
		val += (ll)(N - 1 - side1Loc[side2[i]]) - side1Loc[side2[i]];
		ans = min(ans, val);
	}

	cout << ans << "\n";

	return 0;
}