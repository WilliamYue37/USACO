#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005

typedef long long ll;
typedef pair<int, int> ii;

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
struct Cow {
	int index, p;

	bool operator < (const Cow& c) const {
		return c.p < p;
	}
};

int N;
Cow cows[MAXN];
vector<int> adjList[MAXN];
int preorder = 0;
ii subtree[MAXN];
BIT bit;
int ans[MAXN];

void DFS(int u) {
	subtree[u].first = preorder++;
	for (int v: adjList[u]) {
		DFS(v);
	}
	subtree[u].second = preorder - 1;
}

int main() {
	freopen("promote.in", "r", stdin);
	freopen("promote.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N; 
	for (int i = 0; i < N; ++i) {
		int p; cin >> p;
		cows[i] = Cow{i, p};
	}
	sort(cows, cows + N);
	for (int i = 1; i < N; ++i) {
		int par; cin >> par;
		adjList[--par].push_back(i);
	}

	DFS(0);

	for (int i = 0; i < N; ++i) {
		Cow& c = cows[i];
		ans[c.index] = bit.query(subtree[c.index].second) - bit.query(subtree[c.index].first);
		bit.update(subtree[c.index].first, 1);
	}

	for (int i = 0; i < N; ++i) {
		cout << ans[i] << "\n";
	}

	return 0;
}