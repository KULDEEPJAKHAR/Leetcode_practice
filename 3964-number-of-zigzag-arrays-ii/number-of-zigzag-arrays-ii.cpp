class Solution {
public:
    static const long long MOD = 1000000007LL;
    using Matrix = vector<vector<long long>>;
    Matrix multiply(const Matrix& A, const Matrix& B) {
        int m = A.size();
        Matrix C(m, vector<long long>(m, 0));
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < m; k++) {
                if (A[i][k] == 0) continue;
                long long aik = A[i][k];
                for (int j = 0; j < m; j++) {
                    C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }
    vector<long long> multiply(const Matrix& A, const vector<long long>& v) {
        int m = A.size();
        vector<long long> res(m, 0);
        for (int i = 0; i < m; i++) {
            long long cur = 0;
            for (int j = 0; j < m; j++) {
                cur = (cur + A[i][j] * v[j]) % MOD;
            }
            res[i] = cur;
        }
        return res;
    }
    vector<long long> powerApply(Matrix A, long long exp,
                                 vector<long long> vec) {
        int m = A.size();
        while (exp > 0) {
            if (exp & 1) vec = multiply(A, vec);
            A = multiply(A, A);
            exp >>= 1;
        }
        return vec;
    }
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        Matrix A(m, vector<long long>(m, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                A[i][j] = min(i, j);
            }
        }
        vector<long long> base(m);
        long long p;
        if (n % 2 == 0) {
            for (int i = 0; i < m; i++) {
                base[i] = i;
            }
            p = (n - 2) / 2;
        } else {
            for (int v = 0; v < m; v++) {
                long long x = 1LL * v * (m - 1)
                            - 1LL * v * (v - 1) / 2;
                base[v] = x % MOD;
            }
            p = (n - 3) / 2;
        }
        vector<long long> up = powerApply(A, p, base);
        long long sumUp = 0;
        for (long long x : up) {
            sumUp = (sumUp + x) % MOD;
        }
        return (int)(2LL * sumUp % MOD);
    }
};