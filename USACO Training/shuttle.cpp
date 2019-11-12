#include <bits/stdc++.h>

using namespace std;

#define MAXBITMASK 16777226

typedef long long ll;
typedef pair<int, int> ii;

struct State {
	int bitmask, space, dist;
};

int N;
int st, en;
int prev[MAXBITMASK][24];

int main() {
	//freopen("shuttle.in", "r", stdin);
	//freopen("shuttle.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	cin >> N;
	//0 = white; 1 = black
	string s, e;
	for (int i = 0; i < N; ++i) {
		s += "1";
		e += "0";
	}
	for (int i = 0; i < N; ++i) {
		s += "0";
		e += "1";
	}
	st = stoi(s, nullptr, 2), en = stoi(e, nullptr, 2);

	for (int i = 0; i < MAXBITMASK; ++i) fill(prev[i], prev[i] + N, -1);

	//space is ahead of index
	queue<State> q; q.push(State{st, N - 1, 0});
	while (!q.empty()) {
		State curr = q.front(); q.pop();
		int bitmask = curr.bitmask, space = curr.space, dist = curr.dist;

		//move left into space
		if (space != -1 && dist + 1 < prev[bitmask][space - 1]) {
			prev[bitmask][space - 1] = dist + 1;
			q.push(State{bitmask, space - 1, dist + 1});
		}
		//move right into space
		if (space != N - 1 && dist + 1 < prev[bitmask][space + 1]) {
			prev[bitmask][space + 1] = dist + 1;
			q.push(State{bitmask, space + 1, dist + 1});
		}
		if (((1 << space) & bitmask) != ((1 << (space - 1)) & bitmask) && ) 
	}

	return 0;
}