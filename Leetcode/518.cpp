class Solution {
public:
    int change(int amount, vector<int>& coins) {
        /// amount = 5, coins = [1,2,5]
        ///   return the number of combinations that make up that amount
        ///   If that amount of money cannot be made up by any combination of the coins, return 0
        
        sort(coins.begin(), coins.end());
        return solve1(amount, coins);
    }
    
    int solve1(int amount, vector<int>& coins) {
        /// 5 steps to convert top-down to bottom-up
        ///
        /// 1. initialize an array dp for each states
        vector<vector<int>> dp(amount+1, vector<int>(coins.size()+1, 0));
        /// 2. set base cases
        for(int i=0; i<dp[0].size(); i++)
            dp[0][i] = 1;
        /// 3. iterate all state variable
        for(int m=1; m<dp.size(); m++)
            for(int i=0; i<dp[m].size(); i++) {
                int sum = 0;
                for(int idx=i; idx<coins.size(); idx++)
                    if(m-coins[idx] >= 0)
                        sum += dp[m-coins[idx]][idx];
                dp[m][i]=sum;
            }
         return dp[amount][0];
    }
    
    /// 3 steps to find DP solution
    ///
    /// 1. find the state variable and function that return the ans to the given states
    ///    let m is the current amount want to change
    ///    let i is the start position that we can use to change
    ///        dp(m, i) is number of combinations that make up that amount
    ///
    /// 2. find recurrence relation to transition between states
    ///
    ///    dp(m, i) = sum(dp(m-coin[i], i)) 0 <= i < coins.size() if m-coin[i] >= 0
    ///             = 0                                 otherwise if m-coin[i] < 0
    ///
    /// 3. find base cases
    ///    dp(0, i) = 1
    ///    dp(0, n) = 0    
    vector<int> coins_;
    unordered_map<int,unordered_map<int,int>> memo;
    int solve2(int amount, vector<int>& coins) {
        coins_ = coins;
        return dp(amount, 0);
    }
    
    int dp(int m, int i) {
        if(0 == m)
            return 1;
        if(i == coins_.size())
            return 0;
        /// two level check
        if(auto iter1 = memo.find(m); iter1 != memo.end())
            if(auto iter2 = iter1->second.find(i); iter2 != iter1->second.end())
                return memo[m][i];
        int sum=0;
        for(int idx=i; idx<coins_.size(); idx++)
            if(m-coins_[idx] >= 0)
                sum += dp(m-coins_[idx], idx);
        memo[m][i]=sum;
        return memo[m][i];
    }
};