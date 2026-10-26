#include <string>
class Solution {
    public:
    int lengthOfLastWord(std::string s) {
        int idx = s.length() - 1;
        while (idx >= 0 && s[idx] == ' ') {
            idx--;
        }
        int cnt = 0;
        while (idx >= 0 && s[idx] != ' ') {
            cnt++;
            idx--;
            }
            return cnt;
            }
            };
        
        
    
