class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        
        /// |s1|+|s2| == |s3|

        /// 1.2
        /// let l1 is the length of s1 and it means s1[0:l1]
        /// let l2 is the length of s2 and it means s2[0:l2]
        /// let dp(l1, l2) means s3 is formed by intervaling of s1 & s2
        /// 3.
        ///   dp(l1, l2) = any({s1[|s1|-l1] == s3[|s3|-l1-l2] && dp(l1-1, l2) if l1 > 0,
        ///                     s2[|s2|-l2] == s3[|s3|-l1-l2] && dp(l1, l2-1) if l2 > 0})
        
        if(s1.size()+s2.size() != s3.size())
            return false;
        if("" == s1 && "" == s2 && "" == s3)
            return true;
        
        vector<vector<bool>> dp(s1.size()+1, vector<bool>(s2.size()+1));
        dp[0][0] = true;
        for(int l1=0; l1<dp.size(); l1++)
            for(int l2=0; l2<dp[l1].size(); l2++) {
                if(0 == l1 && 0 == l2)
                    continue;
                if(0 < l1)
                    dp[l1][l2] = dp[l1-1][l2] && s1[s1.size()-l1] == s3[s3.size()-l1-l2];
                if(!dp[l1][l2] && 0 < l2)
                    dp[l1][l2] = dp[l1][l2-1] && s2[s2.size()-l2] == s3[s3.size()-l1-l2];
            }
        return dp[s1.size()][s2.size()];
    }
    
    bool solve1(string s1, string s2, string s3) {
        if(s1.size()+s2.size() != s3.size())
            return false;
        if("" == s1 && "" == s2 && "" == s3)
            return true;
        this->s1 = s1;
        this->s2 = s2;
        this->s3 = s3;
        return dp(s1.size(), s2.size());
    }
    
    string s1;
    string s2;
    string s3;
    unordered_map<int,unordered_map<int,bool>> memo;
    bool dp(int l1, int l2) {
        if(0 == l1 && 0 == l2)
            return true;
        
        if(auto iter1=memo.find(l1); iter1!=memo.end())
            if(auto iter2=iter1->second.find(l2); iter2!=iter1->second.end())
                return memo[l1][l2];

        bool is_match = false;
        if(0 < l1)
            is_match = s1[s1.size()-l1]==s3[s3.size()-l1-l2] && dp(l1-1, l2);
        if (!is_match && 0 < l2)
            is_match = s2[s2.size()-l2] == s3[s3.size()-l1-l2] && dp(l1, l2-1);
        return memo[l1][l2] = is_match;        
    }
};