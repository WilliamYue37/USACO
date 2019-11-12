#include <bits/stdc++.h>

using namespace std;

#define MAXN 200100

typedef long long ll;
typedef pair<int, int> ii;

int N; //length of string T
string T; //inputed string
int RA[MAXN], tempRA[MAXN]; //Rank
int SA[MAXN], tempSA[MAXN]; //Suffix Array
int c[MAXN]; //used for radix sort
vector<ii> owner; //stores the owner of the first string in suffix_i; owner of special characters ($, ?, %) is -1; !NOTE! - has to be computed in main method when inputing strings

int M; //length of pattern string
string P; //pattern string (for string matching)

int Phi[MAXN]; //stores previous suffix (used for computing longest common prefix)
int PLCP[MAXN]; //Permuted Longest Common Prefix
int LCP[MAXN]; //Longest Common Prefix

void countingSort(int k) {
	int sum, maxi = max(300, N);
	memset(c, 0, sizeof(c));
	for (int i = 0; i < N; ++i) {
		++c[i + k < N ? RA[i + k] : 0];
	}
	for (int i = sum = 0; i < maxi; ++i) {
		int t = c[i]; c[i] = sum; sum += t;
	}
	for (int i = 0; i < N; ++i) {
		tempSA[c[SA[i] + k < N ? RA[SA[i] + k] : 0]++] = SA[i];
	}
	for (int i = 0; i < N; ++i) {
		SA[i] = tempSA[i];
	}
}

void constructSA() {
	int r;
	for (int i = 0; i < N; ++i) RA[i] = T[i];
	for (int i = 0; i < N; ++i) SA[i] = i;
	for (int k = 1; k < N; k <<= 1) {
		countingSort(k);
		countingSort(0);
		tempRA[SA[0]] = r = 0;
		for (int i = 1; i < N; ++i) {
			tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
		}
		for (int i = 0; i < N; ++i) {
			RA[i] = tempRA[i];
		}
		if (RA[SA[N - 1]] == N - 1) break;
	}
}

void computeLCP() {
	int L;
	Phi[SA[0]] = -1;
	for (int i = 0; i < N; ++i) {
		Phi[SA[i]] = SA[i - 1];
	}
	for (int i = L = 0; i < N; ++i) {
		if (Phi[i] == -1) {PLCP[i] = 0; continue;}
		while (T[i + L] == T[Phi[i] + L]) ++L;
		PLCP[i] = L;
		L = max(L - 1, 0);
	}
	for (int i = 0; i < N; ++i) {
		LCP[i] = PLCP[SA[i]];
	}
}

ii stringMatching() {
	int lo = 0, hi = N - 1, mid = lo;
	while (lo < hi) {
		mid = (lo + hi) / 2;
		int res = T.compare(SA[mid], T.length() - SA[mid], P);
		if (res >= 0) hi = mid;
		else lo = mid + 1;
	}
	if (T.compare(SA[lo], T.length() - SA[lo], P) != 0) return ii(-1, -1);
	ii ans; ans.first = lo;
	lo = 0; hi = N - 1; mid = lo;
	while (lo < hi) {
		mid = (lo + hi) / 2;
		int res = T.compare(SA[mid], T.length() - SA[mid], P);
		if (res > 0) hi = mid;
		else lo = mid + 1;
	}
	if (T.compare(SA[hi], T.length() - SA[hi], P) != 0) --hi;
	ans.second = hi;
	return ans;
}

ii LRS() {
	int idx = 0, maxLCP = -1;
	for (int i = 1; i < N; ++i) {
		if (LCP[i] > maxLCP) {
			maxLCP = LCP[i], idx = i;
		}
	}
	return ii(maxLCP, idx);
}

ii LCS() {
	int idx = 0, maxLCP = -1;
	for (int i = 1; i < N; ++i) {
		if (owner[SA[i]] != owner[SA[i - 1]] && LCP[i] > maxLCP) {
			maxLCP = LCP[i], idx = i;
		}
	}
	return ii(maxLCP, idx);
}

int main() {
	//freopen("standingout.in", "r", stdin);
	//freopen("standingout.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N;
	vector<int> uniqueFactor(N);
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		T += s;
		T += "$";
		for (int j = 0; j < s.length(); ++j) {
			owner.push_back(ii(i, s.length() - j));
		}
		owner.push_back(ii(-1, -1));
	}
	owner.push_back(ii(-1, -1));
	N = T.length();
	constructSA();
	computeLCP();

	for (int i = 1; i < N;) {
		int j = SA[i];
		int suffixOwner = owner[j].first;
		if (suffixOwner == -1) {++i; continue;}
		int sz = 1;
		while (i + sz < N && owner[SA[i + sz]].first == suffixOwner) {
			++sz;
		}

		int l = LCP[i];
		for (int j = i; j < i + sz; ++j) {
			l = min(l, LCP[j]);
			uniqueFactor[suffixOwner] += max(owner[SA[j]].second - max(l, LCP[j + 1]), 0);
		}
		i += sz;
	}

	for (int i: uniqueFactor) {
		cout << i << "\n";
	}

	return 0;
}