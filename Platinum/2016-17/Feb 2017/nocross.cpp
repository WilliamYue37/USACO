#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005

typedef long long ll;
typedef pair<int, int> ii;

class SegmentTree {
public:
	int n;
	int lo[4*MAXN+1], hi[4*MAXN+1], maximum[4*MAXN+1], delta[4*MAXN+1];

	SegmentTree() {}
	
	SegmentTree(int n) {
		this->n = n;
		init(1, 0, n-1);
	}
	
	void increment(int a, int b, int val) {
		increment(1, a, b, val);
	}
	
	int getMax(int a, int b) {
		return getMax(1, a, b);
	}
	
	void init(int i, int a, int b) {
		lo[i] = a;
		hi[i] = b;
		
		if (a == b) 
			return;
		
		int m = (a+b)/2;
		init(2*i, a, m);
		init(2*i+1, m+1, b);
	}
	
	void prop(int i) {
		delta[2*i] += delta[i];
		delta[2*i+1] += delta[i];
		delta[i] = 0;
	}
	
	void update(int i) {
		maximum[i] = max(maximum[2*i] + delta[2*i], maximum[2*i+1] + delta[2*i+1]);
	}
	
	void increment(int i, int a, int b, int val) {
		if (b < lo[i] || hi[i] < a) 
			return;
		
		if (a <= lo[i] && hi[i] <= b) {
			delta[i] += val;
			return;
		}
		
		prop(i);
		
		increment(2*i, a, b, val);
		increment(2*i+1, a, b, val);
		
		update(i);
	}
	
	int getMax(int i, int a, int b) {
		if (b < lo[i] || hi[i] < a) 
			return 0;
		
		if (a <= lo[i] && hi[i] <= b) {
			return maximum[i] + delta[i];
		}
		
		prop(i);
		
		int maxLeft = getMax(2*i, a, b);
		int maxRight = getMax(2*i+1, a, b);
		
		update(i);
		
		return max(maxLeft, maxRight);
	}
};

int N;
int side1[MAXN], loc[MAXN];
int dp[MAXN];
SegmentTree segtree(MAXN);

int main() {
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> side1[i];
	for (int i = 0; i < N; ++i) {
		int breed; cin >> breed;
		loc[breed] = i;
	}

	for (int i = 0; i < N; ++i) {
		int breed = side1[i];
		vector<int> index;
		for (int j = min(N, breed + 4); j >= max(1, breed - 4); --j) {
			index.push_back(loc[j]);
		}
		sort(index.begin(), index.end(), greater<int>());
		for (int j = 0; j < index.size(); ++j) {
			dp[i] = max(dp[i], segtree.getMax(0, index[j] - 1) + 1);
			int update = max(segtree.getMax(0, index[j] - 1) + 1, segtree.getMax(index[j], index[j])) - segtree.getMax(index[j], index[j]);
			segtree.increment(index[j], index[j], update);
		}
	}

	int ans = 0;
	for (int i = 0; i < N; ++i) ans = max(ans, dp[i]);

	cout << ans << "\n";

	return 0;
}