class Solution {
public:
    string reverseParentheses(string s) {
        string res;
        for (char c : s) {
            if (c == '(') {
                res.push_back(c);
            } else if (c == ')') {
                string temp;
                while (res.back() != '(') {
                    temp += res.back();
                    res.pop_back();
                }
                res.pop_back();
                for (char x : temp)
                    res.push_back(x);
            } else {
                res.push_back(c);
            }
        }

        return res;
    }
};