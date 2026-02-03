class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length()!=t.length()) return false;
        vector<int>frequency(26,0);
        for(int i=0;i<s.length();i++) frequency[s[i]-'a']++;
        for(int j = 0;j<t.length();j++) frequency[t[j]-'a']--;
        for(int i = 0;i<frequency.size();i++){
            if(frequency[i]!=0) return false;
        }
        return true;
    }
};