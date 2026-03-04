class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words = split(s);
        if(words.size() != pattern.size())
            return false;
        
        array<bool, 26> visited = {false};
        unordered_map<string, char> s2p;
        for(int i=0; i<words.size(); i++) {
            if(0 == s2p[words[i]] && !visited[pattern[i]-'a']) {
                s2p[words[i]] = pattern[i];
                visited[pattern[i]-'a'] = true;
            }
            if(s2p[words[i]] != pattern[i])
                return false;
        }
        return true;
    }
    
    vector<string> split(string &s, const string &delimeter=" ") {
        vector<string> tokens;
        int start = 0, end= 0;
        while(end != string::npos) {
            start = s.find_first_not_of(delimeter, end);
            end = s.find_first_of(delimeter, start);
            tokens.push_back(s.substr(start, end-start));
        }
        return tokens;
    }
};