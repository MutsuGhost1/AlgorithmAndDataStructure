class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        string tmp;
        vector<string> ans;
        solve(s, wordDict, tmp, ans);
        return ans;
    }
    
    void solve(string s, vector<string>& wordDict, string tmp, vector<string> &ans) {
        if(0 == s.size()) {
            ans.push_back(tmp);
            return;
        }
        for(string &prefix : wordDict) {
            if(!s.compare(0, prefix.size(), prefix)) {
                solve(s.substr(prefix.size()), wordDict, (tmp.size()) ? tmp + " " + prefix : prefix, ans);
            }
        }
    }
};