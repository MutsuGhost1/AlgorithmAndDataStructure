class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        return solve1(s, wordDict);
    }
    
    /// approach 1 - dynamic programming
    /// > convert top-down to bottom-up
    bool solve1(string s, vector<string>& wordDict) {
        /// 1. initialized an array dp that is sized according to your state variables
        vector<bool> dp(s.size()+1, false);
        /// 2. set your base cases
        dp[0]=true;
        /// 3. write a for loop to iterate your state variable
        ///      continue with your base cases
        for(int i=1; i<dp.size(); i++) {
            bool match_any = false;
            for(string &word : wordDict)
                if(i >= word.size() && !s.compare(i-word.size(), word.size(), word) && dp[i-word.size()]) {
                    match_any = true;
                    break;
                }
            dp[i] = match_any;
        }
        return dp[s.size()];
    }
    
    /// approach 2 - recursive + memoization (TLE)
    ///
    /// Framework to DP problem - 3 Steps
    ///
    /// 1. find state variables
    ///    - we define state variable Si which means the length of a S and represent s[0:i]
    ///      assume dp(Si) is a function that can determine whether Si can be formed by wordDict or not
    ///
    /// 2. find the recurrence relation equations
    ///      dp(Si) = dp(Si-Ti) if Ti is a prefix of Si for all Ti in wordDict
    ///
    /// 3. base cases
    ///      dp(S0) = true
    ///
    bool solve2(string s, vector<string>& wordDict) {
        word_dict_ = wordDict;
        memo.clear();
        return dp(s, s.size());
    }
    
    vector<string> word_dict_;
    unordered_map<int, bool> memo;
    bool dp(string s, int n) {
        if(0 == n)
            return true;
        if(auto iter = memo.find(n); iter == memo.end()) {
            bool match_any=false;
            for(string &word : word_dict_) {
                if(n >= word.size() && !s.compare(n-word.size(), word.size(), word) && dp(s, n-word.size())) {
                    match_any = true;
                    break;
                }
            }
            memo[n] = match_any;
        }
        return memo[n];            
    }
};

/// s= "leetcode", wordDict = ["leet", "code"]
///
/// let Sn is a string with length n
///     wb(Sn) is a function to check wether Sn can be composed by wordDict
///
/// 
/// wb(Sn) = wb(Sn-Ti) for all Ti in wordDict and Ti is prefix of Sn
/// wb(S0) = true
///
///