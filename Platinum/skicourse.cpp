#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<long long, long long> pl;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const double EPS = 1e-6;
const int MAX_N = 105;

int N, M;
char grid[MAX_N][MAX_N];
int dpR[MAX_N][MAX_N], dpS[MAX_N][MAX_N];

int main() {
    freopen("skicourse.in", "r", stdin); freopen("skicourse.out", "w", stdout);
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> grid[i][j];
        }
    }

    int ans = min(N, M);
    while (true) {
        int maxi = 0, best_r, best_c;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                dpR[i][j] = grid[i][j] == 'R' || grid[i][j] == 'W' ? min({dpR[i - 1][j], dpR[i][j - 1], dpR[i - 1][j - 1]}) + 1 : 0;
                dpS[i][j] = grid[i][j] == 'S' || grid[i][j] == 'W' ? min({dpS[i - 1][j], dpS[i][j - 1], dpS[i - 1][j - 1]}) + 1 : 0;
                if ((dpR[i][j] > maxi || dpS[i][j] > maxi) && dpR[i][j] != dpS[i][j]) {
                    maxi = max(dpR[i][j], dpS[i][j]);
                    best_r = i; best_c = j;
                }
            }       
        }

        if (maxi == 0) break;

        ans = min(ans, maxi);
        for (int i = best_r; i >= best_r - maxi + 1; --i) {
            for (int j = best_c; j >= best_c - maxi + 1; --j) {
                grid[i][j] = 'W';
            }
        }
    }

    cout << ans << '\n';

    return 0;   
}