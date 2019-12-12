#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define MOD 1000000007
#define INF 1000000000000000000LL

const int MAX_N = 100005;

typedef long long ll;
typedef pair<int, int> pi;

int N;
double sum;
double milk[MAX_N];

double kadane(double B) {
	double maxEndingHere = milk[1] - B, maxSoFar = milk[1] - B;
	for (int i = 2; i < N - 1; ++i) {
		maxEndingHere = max(maxEndingHere + milk[i] - B, milk[i] - B);
		maxSoFar = max(maxSoFar, maxEndingHere);
	}
	return maxSoFar;
}

int main() {
	freopen("sabotage.in", "r", stdin);
	freopen("sabotage.out", "w", stdout);
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> milk[i];
		sum += milk[i];
	}

	double lo = 0.0, hi = 10000.0;
	while (hi - lo > 0.00001) {
		double m = (lo + hi) / 2;
		if (sum - N * m - kadane(m) > 0) {
			lo = m;
		}
		else {
			hi = m;
		}
	}

	cout << fixed << setprecision(3) << hi << '\n';

	return 0;
}