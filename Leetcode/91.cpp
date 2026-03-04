class Solution {
public:
    int numDecodings(string s) {
        ///
        /// dp(i) = sum(dp(i-|k|)) if i-|k| >= 0 for all 0<=k<=26
        ///       = 0       otherwise i-|k| < 0
        /// to_string(i)
        
        /// dp(i) = 1 if i == 0
        
        vector<int> dp(s.size()+1);
        dp[0] = 1;
        for(int i=1; i<dp.size(); i++) {
            int sum = 0;
            for(int k=1; k<=26; k++) {
                string sub_str = to_string(k);
                int l = sub_str.size();
                if(i-l >= 0 && 0 == s.compare(i-l, l, sub_str))
                   sum += dp[i-l];
            }
            dp[i]=sum;
        }
    
        return dp[s.size()];
    }
};