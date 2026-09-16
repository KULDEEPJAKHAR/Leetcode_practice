


        














    class Solution {
public:
    static const int MOD = 1e9 + 7;

    long long modPow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1)
                res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    int numberOfSets(int n, int k) {
        int N = n + k - 1;
        int R = 2 * k;

        long long num = 1, den = 1;

        for (int i = 1; i <= R; i++) {
            num = num * (N - R + i) % MOD;
            den = den * i % MOD;
        }

        return num * modPow(den, MOD - 2) % MOD;
    }
};
