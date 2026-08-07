class Solution {
 public:
  string smallestNumber(string num, long long t) {
    const auto [primeCount, ok] = getPrimeCount(t);
    if (!ok)
      return "-1";

    const unordered_map<int, int> factorCount = getFactorCount(primeCount);
    if (sumValues(factorCount) > num.length())
      return construct(factorCount);

    unordered_map<int, int> prefix = getPrimeCount(num);

    int firstZero = num.find('0');
    if (firstZero == string::npos) {
      firstZero = num.length();
      if (isSubset(primeCount, prefix))
        return num;
    }

    for (int i = num.length() - 1; i >= 0; --i) {
      int d = num[i] - '0';
      prefix = subtract(prefix, FACTORS.at(d));

      int rem = num.length() - 1 - i;

      if (i > firstZero)
        continue;

      for (int nd = d + 1; nd <= 9; ++nd) {
        auto need = getFactorCount(
            subtract(subtract(primeCount, prefix), FACTORS.at(nd)));

        if (sumValues(need) <= rem) {
          int ones = rem - sumValues(need);
          return num.substr(0, i) + char('0' + nd) +
                 string(ones, '1') + construct(need);
        }
      }
    }

    auto need = getFactorCount(primeCount);
    return string(num.length() + 1 - sumValues(need), '1') +
           construct(need);
  }

 private:
  const unordered_map<int, unordered_map<int, int>> FACTORS = {
      {0, {}},
      {1, {}},
      {2, {{2, 1}}},
      {3, {{3, 1}}},
      {4, {{2, 2}}},
      {5, {{5, 1}}},
      {6, {{2, 1}, {3, 1}}},
      {7, {{7, 1}}},
      {8, {{2, 3}}},
      {9, {{3, 2}}},
  };

  pair<unordered_map<int, int>, bool> getPrimeCount(long long t) {
    unordered_map<int, int> cnt{{2,0},{3,0},{5,0},{7,0}};

    for (int p : {2,3,5,7}) {
      while (t % p == 0) {
        t /= p;
        cnt[p]++;
      }
    }

    return {cnt, t == 1};
  }

  unordered_map<int, int> getPrimeCount(const string& s) {
    unordered_map<int, int> cnt{{2,0},{3,0},{5,0},{7,0}};

    for (char c : s)
      for (auto [p, f] : FACTORS.at(c - '0'))
        cnt[p] += f;

    return cnt;
  }

  unordered_map<int, int> getFactorCount(
      const unordered_map<int, int>& cnt) {

    unordered_map<int, int> res;

    int c8 = cnt.at(2) / 3;
    int rem2 = cnt.at(2) % 3;

    int c9 = cnt.at(3) / 2;
    int c3 = cnt.at(3) % 2;

    int c4 = rem2 / 2;
    int c2 = rem2 % 2;

    int c6 = 0;

    if (c2 && c3) {
      c2 = c3 = 0;
      c6 = 1;
    }

    if (c3 && c4) {
      c2 = 1;
      c6 = 1;
      c3 = c4 = 0;
    }

    res[2] = c2;
    res[3] = c3;
    res[4] = c4;
    res[5] = cnt.at(5);
    res[6] = c6;
    res[7] = cnt.at(7);
    res[8] = c8;
    res[9] = c9;

    return res;
  }

  string construct(const unordered_map<int, int>& f) {
    string ans;
    for (int d = 2; d <= 9; d++)
      ans += string(f.at(d), char('0' + d));
    return ans;
  }

  bool isSubset(const unordered_map<int, int>& a,
                const unordered_map<int, int>& b) {
    for (auto [k, v] : a)
      if (b.at(k) < v)
        return false;
    return true;
  }

  unordered_map<int, int> subtract(
      unordered_map<int, int> a,
      const unordered_map<int, int>& b) {
    for (auto [k, v] : b)
      a[k] = max(0, a[k] - v);
    return a;
  }

  int sumValues(const unordered_map<int, int>& mp) {
    int s = 0;
    for (auto [_, v] : mp)
      s += v;
    return s;
  }
};