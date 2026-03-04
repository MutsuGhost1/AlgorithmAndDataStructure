class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        return solve2(coins, amount);
    }
    
    int solve1(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, INT_MAX);
        /// base cases
        dp[0] = 0;
        for(int i=1; i<=amount; i++) {
            for(int j=0; j<coins.size(); j++) {
                if(i-coins[j] >= 0)
                    dp[i] = min(dp[i],dp[i-coins[j]]);
            }
            if(INT_MAX != dp[i])
                dp[i]++;
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];        
    }
    
    int solve2(vector<int>& coins, int amount) {
        coins_ = coins;
        int ans = dp(amount);
        return ans == INT_MAX ? -1 : ans;        
    }

    unordered_map<int,int> memo;
    vector<int> coins_;
    int dp(int n) {
        /// base cases
        if(0 == n)
            return 0;
        /// recurrence relation equations
        if(0 == memo[n]) {
            /// coins = [2], amount=3
            /// dp(3) = max(dp(1))
            /// dp(1) = max(dp(-1))
            /// ...
            int num=INT_MAX;
            for(int i=0; i<coins_.size(); i++)
                if(n-coins_[i] >= 0)
                    num = min(num, dp(n-coins_[i]));
                else
                    memo[n-coins_[i]] = INT_MAX;
            if(INT_MAX != num)
                num++;
            memo[n] = num;
        }
        return memo[n];
    }

};