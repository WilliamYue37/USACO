#include <bits/stdc++.h>

using namespace std;

#define MAXN 100005
#define MAXM 100005

typedef long long ll;
typedef pair<ll, int> ii;

struct Slingshot {
	int x, y;
	ll t, rank;
};

struct Query {
	int a, b, order;
	ll answer;
};

bool compareX(Slingshot s1, Slingshot s2) {
	return s1.x < s2.x;
}

bool compareY(Slingshot s1, Slingshot s2) {
	return s1.y < s2.y;
}

bool compareA(Query q1, Query q2) {
	return q1.a < q2.a;
}

bool compareO(Query q1, Query q2) {
	return q1.order < q2.order;
}

class SegmentTree {
public:
	int n;
	ll lo[4*MAXN+1], hi[4*MAXN+1], minimum[4*MAXN+1], delta[4*MAXN+1];
	
	SegmentTree() {}

	SegmentTree(int n) {
		this->n = n;
		init(1, 0, n-1);
	}
	
	void increment(int a, int b, ll val) {
		increment(1, a, b, val);
	}
	
	ll getMin(int a, int b) {
		return getMin(1, a, b);
	}
	
	void init(int i, int a, int b) {
		lo[i] = a;
		hi[i] = b;
		minimum[i] = (1ll << 40);
		
		if (a == b) 
			return;
		
		ll m = (a+b)/2;
		init(2*i, a, m);
		init(2*i+1, m+1, b);
	}
	
	void prop(int i) {
		delta[2*i] += delta[i];
		delta[2*i+1] += delta[i];
		delta[i] = 0;
	}
	
	void update(int i) {
		minimum[i] = min(minimum[2*i] + delta[2*i], minimum[2*i+1] + delta[2*i+1]);
	}
	
	void increment(int i, int a, int b, ll val) {
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
	
	ll getMin(int i, int a, int b) {
		if (b < lo[i] || hi[i] < a) 
			return (1ll << 40);
		
		if (a <= lo[i] && hi[i] <= b) {
			return minimum[i] + delta[i];
		}
		
		prop(i);
		
		ll minLeft = getMin(2*i, a, b);
		ll minRight = getMin(2*i+1, a, b);
		
		update(i);
		
		return min(minLeft, minRight);
	}
};

int N, M;
Slingshot slingshots[MAXN];
Query queries[MAXM];
ll yvalues[MAXN];
SegmentTree st1(MAXN), st2(MAXN), st3(MAXN), st4(MAXN);

int main() {
	freopen("slingshot.in", "r", stdin);
	freopen("slingshot.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	//input	
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		int x, y; ll t; cin >> x >> y >> t;
		slingshots[i] = Slingshot{x, y, t, 0};
		yvalues[i] = y;
	}
	for (int i = 0; i < M; ++i) {
		int a, b; cin >> a >> b;
		queries[i] = Query{a, b, i, abs(a - b)};
	}

	//sort and get rankings for Slingshots
	sort(yvalues, yvalues + N);
	sort(queries, queries + M, compareA);
	sort(slingshots, slingshots + N, compareY);
	for (int i = 0; i < N; ++i) {
		slingshots[i].rank = i;
	}
	sort(slingshots, slingshots + N, compareX);

	//case 1 x <= a, y <= b
	int p1 = 0;
	for (int i = 0; i < M; ++i) {
		while (p1 < N && slingshots[p1].x <= queries[i].a) {
			ll index = slingshots[p1].rank;
			st1.increment(index, index, (slingshots[p1].t - slingshots[p1].x - slingshots[p1].y) - st1.getMin(index, index));
			++p1;
		}
		ll index = lower_bound(yvalues, yvalues + N, queries[i].b) - yvalues;
		index = (queries[i].b == yvalues[index] ? index : index - 1);
		queries[i].answer = min(queries[i].answer, queries[i].a + queries[i].b + st1.getMin(0, index));
	}

	//case 2 a <= x, y <= b
	p1 = N - 1;
	for (int i = M - 1; i >= 0; --i) {
		while (p1 >= 0 && slingshots[p1].x >= queries[i].a) {
			ll index = slingshots[p1].rank;
			st2.increment(index, index, (slingshots[p1].t + slingshots[p1].x - slingshots[p1].y) - st2.getMin(index, index));
			--p1;
		}
		ll index = lower_bound(yvalues, yvalues + N, queries[i].b) - yvalues;
		index = (queries[i].b == yvalues[index] ? index : index - 1);
		queries[i].answer = min(queries[i].answer, queries[i].b - queries[i].a + st2.getMin(0, index));
	}

	//case 3 x <= a, b <= y
	p1 = 0;
	for (int i = 0; i < M; ++i) {
		while (p1 < N && slingshots[p1].x <= queries[i].a) {
			ll index = slingshots[p1].rank;
			st3.increment(index, index, (slingshots[p1].t - slingshots[p1].x + slingshots[p1].y) - st3.getMin(index, index));
			++p1;
		}
		ll index = lower_bound(yvalues, yvalues + N, queries[i].b) - yvalues;
		queries[i].answer = min(queries[i].answer, queries[i].a - queries[i].b + st3.getMin(index, N - 1));
	}

	//case 4 x <= a, y <= b
	p1 = N - 1;
	for (int i = M - 1; i >= 0; --i) {
		while (p1 >= 0 && slingshots[p1].x >= queries[i].a) {
			ll index = slingshots[p1].rank;
			st4.increment(index, index, (slingshots[p1].t + slingshots[p1].x + slingshots[p1].y) - st4.getMin(index, index));
			--p1;
		}
		ll index = lower_bound(yvalues, yvalues + N, queries[i].b) - yvalues;
		queries[i].answer = min(queries[i].answer, -1 * queries[i].a - queries[i].b + st4.getMin(index, N - 1));
	}

	sort(queries, queries + M, compareO);

	for (int i = 0; i < M; ++i) {
		cout << queries[i].answer << "\n";
	}

	return 0;
}