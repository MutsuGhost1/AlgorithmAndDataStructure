class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        return solve1(s, wordDict);
    }
    
    /// dynamic programming
    bool solve2(string s, vector<string>& wordDict) {
        ///
        /// i    01234567   prefix.size()     4      4
        /// s = "leetcode", wordDict      = ["leet","code"]
        ///
        ///
        ///
        for(int i=0; i < s.size(); i++)
            for(string &prefix : wordDict)
                if(!memo[i+prefix.size()-1] && !s.compare(i, prefix.size(), prefix) && (i-1 < 0 || memo[i-1]))
                    memo[i+prefix.size()-1] = true;
        return memo[s.size()-1];        
    }
    
    /// recursive + memorization
    bool solve1(string s, vector<string>& wordDict) {
        if(0 == s.size())
            return true;
        if(0 != memo[s.size()-1])
            return memo[s.size()-1] == 1;

        for(string &prefix : wordDict) {
            if(!s.compare(0, prefix.size(), prefix)) {
                if(solve1(s.substr(prefix.size()), wordDict)) {
                    memo[s.size()-1] = 1;
                    return true;
                }
            }
        }
        memo[s.size()-1] = -1;
        return false;
    }
    array<int, 300> memo;
};