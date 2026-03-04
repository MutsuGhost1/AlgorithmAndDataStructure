class Solution {
public:
    int change(int amount, vector<int>& coins) {
        sort(coins.begin(), coins.end());
        /// amount = 5, coins = [1,2,5]
        ///   return the number of combinations that make up that amount
        ///   If that amount of money cannot be made up by any combination of the coins, return 0        
        return solve0(amount, coins);
    }
    
    int solve0(int amount, vector<int>& coins) {
    /// 4 steps to find DP solution
    ///
    /// 1. find the state variable and function that return the ans to the given states
    ///    let m is the current amount want to change
    ///    let i is the start position of coins that we can use to change - coins[i:]
    ///        dp(m, i) is number of combinations that make up that amount
    ///
    /// 2. find recurrence relation to transition between states
    ///
    ///    dp(m, i) = accumulate({dp(m-coin[idx], idx) i <= idx < coins.size() if m-coin[idx] >= 0 }, 0)
    ///
    /// 3. find base cases
    ///    dp(0, i) = 1, means the amount can be changed by our coins
    ///       is it possible to m=0 & i=n ?
        vector<vector<int>> dp(amount+1, vector<int>(coins.size()));
        /// 2. set base cases
        fill(dp[0].begin(), dp[0].end(), 1);
        for(int m=1; m<dp.size(); m++)
            for(int i=0; i<dp[m].size(); i++) {
                int sum = 0;
                /// dp[m][i] is only contributed by those coins[i:]
                for(int idx=i; idx<coins.size(); idx++)
                    if(0 <= m-coins[idx])
                        sum += dp[m-coins[idx]][idx];
                dp[m][i] = sum;
            }
        return dp[amount][0];
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
    
    /// 4 steps to find DP solution
    ///
    /// 1. find the state variable and function that return the ans to the given states
    ///    let m is the current amount want to change
    ///    let i is the start position of coins that we can use to change - coins[i:]
    ///        dp(m, i) is number of combinations that make up that amount
    ///
    /// 2. find recurrence relation to transition between states
    ///
    ///    dp(m, i) = accumulate({dp(m-coin[i], i) 0 <= i < coins.size() if m-coin[i] >= 0 }, 0)
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