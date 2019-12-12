#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const int INF = 1e9;
const double EPS = 1e-6;
const int MAX_N = 105;

int N, M;
int gangs[MAX_N];

int result() {
	priority_queue<int> pq;
	for (int i = 2; i <= M; ++i) pq.push(gangs[i]);
	while (pq.size() >= 2) {
		int first = pq.top(); pq.pop(); int second = pq.top(); pq.pop();
		--first, --second;
		if (first != 0) pq.push(first);
		if (second != 0) pq.push(second);
	}
	return gangs[1] - (pq.size() > 0 ? pq.top() : 0);
}

bool valid(int field) {
	int maxi = *max_element(gangs + 2, gangs + M + 1);
	int sum = 0;
	for (int i = 2; i <= M; ++i) sum += gangs[i];
	return maxi - field <= sum - maxi;
}

int main() {
	freopen("gangs.in", "r", stdin); freopen("gangs.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;
	for (int i = 1; i <= M; ++i) {
		cin >> gangs[i];
	}

	int left = result(), field = gangs[1] - left, id = 1;
	if (left <= 0) {
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n" << left << '\n';
	for (int i = 0; i < field; ++i) cout << 1 << '\n';

	int numOfGangs = M - 1, n_field, n_id;
	while (numOfGangs != 0) {
		for (int i = 2; i <= M; ++i) {
			if (gangs[i] > 0) {
				--gangs[i];
				n_id = id;
				if (id == i) {
					n_field = field + 1;
				}
				else {
					if (field > 0) {
						n_field = field - 1;
					}
					else if (field == 0) {
						n_field = 1;
						n_id = i;
					}
				}
				if (valid(n_field)) {
					cout << i << '\n';
					field = n_field;
					id = n_id;
				}
				else {
					++gangs[i];
					int maxi = max_element(gangs + 2, gangs + M + 1) - gangs;
					--gangs[maxi];
					cout << maxi << '\n';
					if (gangs[maxi] == 0) --numOfGangs;
					--field;
				}
				if (gangs[i] == 0) --numOfGangs;
				break;
			}
		}
	}

	for (int i = 0; i < left; ++i) cout << 1 << '\n';
	

	return 0;
}