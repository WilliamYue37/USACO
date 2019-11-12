#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MAXN 100005

typedef long long ll;
typedef pair<int, int> pi;

int N, T;
ll A[MAXN], L[MAXN]; //negate values in array A for longest decreasing subsequence
stack<int> stk;

int LDS() {
	int lis = 0, lisEnd = 0;
	for (int i = 0; i < N; ++i) {
		int pos = upper_bound(L, L + lis, A[i]) - L; //change to upper_bound to go from increasing to non-decreasing
		L[pos] = A[i];
		if (pos + 1 > lis) {
		 lis = pos + 1;
		 lisEnd = i;
		}
	}
	return lis;
}

int main() {
	freopen("cowjog.in", "r", stdin);
	freopen("cowjog.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> T;
	for (int i = 0; i < N; ++i) {
		ll start, speed; cin >> start >> speed;
		A[i] = -(start + speed * T);
	}

	cout << LDS() << "\n";

	return 0;
}