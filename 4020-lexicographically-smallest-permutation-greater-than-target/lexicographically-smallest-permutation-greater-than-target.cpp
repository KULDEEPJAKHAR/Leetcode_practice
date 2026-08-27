class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26);

        for (char c : s)
            cnt[c - 'a']++;

        int i = 0;

        for (; i < n; i++) {
            int x = target[i] - 'a';

            if (cnt[x] == 0)
                break;

            cnt[x]--;
        }

        for (int j = min(i, n - 1); j >= 0; j--) {
            if (j < i)
                cnt[target[j] - 'a']++;

            int x = target[j] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] == 0)
                    continue;

                string res = target.substr(0, j);
                res += char('a' + c);
                cnt[c]--;

                for (int k = 0; k < 26; k++)
                    res += string(cnt[k], char('a' + k));

                return res;
            }
        }

        return "";
    }
};