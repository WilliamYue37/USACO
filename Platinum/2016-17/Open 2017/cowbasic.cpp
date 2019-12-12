#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
#define MOD 1000000007

typedef long long ll;
typedef pair<int, int> pi;

struct Matrix {
    vector<vector<ll>> mat;
    int a, b;
    
    Matrix() { a = b = 0; }

    Matrix(int a, int b) {
        this->a = a, this->b = b;
        mat = vector<vector<ll>>(a);
        for (int i = 0; i < a; ++i) {
            mat[i] = vector<ll>(b);
            for (int j = 0; j < b; ++j) mat[i][j] = 0;
        }
    }
    
    Matrix(vector<vector<int>> v) : Matrix(v.size(), v[0].size()) {
        for (int i = 0; i < a; ++i) for (int j = 0; j < b; ++j) mat[i][j] = v[i][j];
    }
    
    void print() {
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < b; ++j) cout << mat[i][j] << " ";
            cout << "\n";
        }
        cout << "------------\n";
    }
    
    Matrix operator+(const Matrix& m) {
        Matrix ret(a, b);
        for (int i = 0; i < a; ++i) for (int j = 0; j < b; ++j) ret.mat[i][j] = (mat[i][j] + m.mat[i][j]) % MOD;
        return ret;
    }
    
    Matrix operator*(const Matrix& m) {
        Matrix ret(a, m.b);
        for (int i = 0; i < a; ++i) for (int j = 0; j < b; ++j) for (int k = 0; k < m.b; ++k) 
            ret.mat[i][k] = (ret.mat[i][k] + mat[i][j] * m.mat[j][k] % MOD) % MOD;
        return ret;
    }

    Matrix operator^(ll pow) {
        Matrix ret(a, a), base(*this);
        for (int i = 0; i < a; ++i) ret.mat[i][i] = 1;
        while (pow) {
            if (pow & 1) ret = ret * base;
            base = base * base;
            pow /= 2;
        }
        return ret;
    }
};

int numOfVar = 0;
queue<string> operations;
map<string, int> idx; //key = variable name, value = index in maxtrix

void computeExpression(Matrix& expression, int var) {
	if (operations.front() == "(") {
		operations.pop(); 
		computeExpression(expression, var);
		operations.pop(); operations.pop(); operations.pop();
		computeExpression(expression, var);
		operations.pop();
	}
	else if ('0' <= operations.front()[0] && operations.front()[0] <= '9') {
		expression.mat[var][idx.size()] += stoi(operations.front()); operations.pop();
	}
	else {
		++expression.mat[var][idx[operations.front()]]; operations.pop();
	}
}

Matrix getMatrix() {
	Matrix ret(idx.size() + 1, idx.size() + 1); for (int i = 0; i <= idx.size(); ++i) ret.mat[i][i] = 1;
	while (operations.front() != "}") {
		string s = operations.front(); operations.pop();
		if ('a' <= s[0] && s[0] <= 'z') {
			operations.pop();
			Matrix expression(idx.size() + 1, idx.size() + 1); for (int i = 0; i <= idx.size(); ++i) expression.mat[i][i] = 1; expression.mat[idx[s]][idx[s]] = 0;
			computeExpression(expression, idx[s]);
			ret = expression * ret;
		}
		else if (s == "RETURN") {
			return ret;
		}
		else {
			int pow = stoi(s); operations.pop(); operations.pop();
			ret = (getMatrix() ^ pow) * ret;
		}
	}
	operations.pop();
	return ret;
}

int main() {
	freopen("cowbasic.in", "r", stdin);
	freopen("cowbasic.out", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	string s;
	while (cin >> s) {
		operations.push(s);
		if ('a' <= s[0] && s[0] <= 'z' && idx.count(s) == 0) {
			idx[s] = numOfVar++;
		}
	}

	Matrix F(idx.size() + 1, 1), M = getMatrix(); F.mat[idx.size()][0] = 1;
	F = M * F;

	cout << F.mat[idx[operations.front()]][0] << "\n";

	return 0;
}