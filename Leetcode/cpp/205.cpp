class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size() != t.size())
            return false;
        /*
            No two characters may map to the same character, 
            but a character may map to itself.
            
            s = "ac"
            t = "bb"
         */
        
        unordered_map<char,char> h1,h2;
        for(int i=0; i<s.size(); i++) {
            if(h1.count(s[i]) == 0 && h2.count(t[i]) == 0) {
                h1[s[i]] = t[i];
                h2[t[i]] = s[i];
            } else {
                if(h1[s[i]] != t[i] || h2[t[i]] != s[i])
                    return false;
            }
        }
        return true;
    }
};