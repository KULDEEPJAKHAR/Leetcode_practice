class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for(int i = 0; i < s.size(); i++) {
            
            
            if(s[i]=='(' || s[i]=='[' || s[i]=='{') {
                st.push(s[i]);
            }
            else {
                // If stack empty → no matching opening bracket
                if(st.empty()) return false;

                char top = st.top();
                st.pop();

                // If not matching pair → invalid
                if((top=='(' && s[i]!=')') ||
                   (top=='[' && s[i]!=']') ||
                   (top=='{' && s[i]!='}')) {
                    return false;
                }
            }
        }

        return st.empty(); 
    }
};
