class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = s.size();
        int total = 1 << k; 
        if (n < total + k - 1) return false;
        unordered_set<string> seen;
        for (int i = 0; i <= n - k; i++) {
            seen.insert(s.substr(i, k));
            if (seen.size() == total)
                return true;
        }
        return seen.size() == total;
    }
};