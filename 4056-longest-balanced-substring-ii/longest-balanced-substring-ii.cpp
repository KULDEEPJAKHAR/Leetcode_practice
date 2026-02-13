class Solution {
public:
    int longestBalanced(string s) {
        int n = s.length();
        int maxLen = 0;
        
        // pref[i][char] stores the count of 'a', 'b', or 'c' up to index i-1
        vector<vector<int>> pref(n + 1, vector<int>(3, 0));
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i];
            pref[i + 1][s[i] - 'a']++;
        }

        // For each possible non-empty subset of {'a', 'b', 'c'}
        for (int mask = 1; mask <= 7; ++mask) {
            vector<int> chars;
            for (int i = 0; i < 3; ++i) {
                if ((mask >> i) & 1) chars.push_back(i);
            }

            // We use a map to find the earliest index 'j' such that 
            // the characters in 'mask' have the same relative differences.
            // For a subset like {a, b}, we need (cntA_i - cntB_i) == (cntA_j - cntB_j)
            // AND we need to ensure no characters OUTSIDE the mask appeared.
            unordered_map<long long, int> seen;
            int lastInvalid = -1;

            for (int i = 0; i <= n; ++i) {
                // Check if the current character (if not at start) is in our mask
                if (i > 0 && !((mask >> (s[i-1] - 'a')) & 1)) {
                    lastInvalid = i - 1;
                    seen.clear(); 
                }

                long long state = 0;
                if (chars.size() == 1) {
                    state = 0; // Relative difference is trivial
                } else if (chars.size() == 2) {
                    state = pref[i][chars[0]] - pref[i][chars[1]];
                } else {
                    long long d1 = pref[i][0] - pref[i][1];
                    long long d2 = pref[i][1] - pref[i][2];
                    // Encode two differences into one 64-bit integer
                    state = (d1 + 100001) << 32 | (d2 + 100001);
                }

                if (seen.count(state)) {
                    int j = seen[state];
                    // The substring is s[j...i-1]. We must ensure every character 
                    // in the mask actually appeared at least once.
                    bool allPresent = true;
                    for (int c : chars) {
                        if (pref[i][c] - pref[j][c] == 0) {
                            allPresent = false;
                            break;
                        }
                    }
                    if (allPresent) {
                        maxLen = max(maxLen, i - j);
                    }
                } else {
                    seen[state] = i;
                }
            }
        }

        return maxLen;
    }
};