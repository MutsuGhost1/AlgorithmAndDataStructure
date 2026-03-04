class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
/*
        vector<vector<int>> dp(prices.size()+1, vector<int>(2));
        dp[0][0] = 0;
        dp[0][1] = -50001;
*/
        int empty=0, pre_empty=empty, held=-50001;
        for(int i=1; i<=prices.size(); i++) {
            empty = max(pre_empty, held+prices[i-1]-fee);
            held = max(held, pre_empty-prices[i-1]);
            pre_empty=empty;
        }
        return max(empty, held);           
///        return solve1(prices, fee);
    }

    int solve1(vector<int>& prices, int fee) {
        /// 4 steps to solve DP problems
        ///
        /// 1. find state variables and function/data struct 
        ///      that compute/contain the answer to each given states
        ///
        ///    let i is the i-th day,
        ///    let j is the state - empty = 0
        ///                       - held = 1
        ///    let dp(i) is the max profit in i-th day
        ///
        /// 2. find the recurrence relation to transition between states
        ///
        ///    dp(i, 0) = max(dp(i-1, 0), dp(i-1, 1)+nums[i-1]-fee)
        ///    dp(i, 1) = max(dp(i-1, 1), dp(i-1, 0)-nums[i-1]-fee)
        ///
        /// 3. find the base cases
        ///    dp(0, 0) = 0
        ///    dp(0, 1) = -00
        vector<vector<int>> dp(prices.size()+1, vector<int>(2));
        dp[0][0] = 0;
        dp[0][1] = -50001;
        for(int i=1; i<dp.size(); i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i-1]-fee);
            dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i-1]);
        }
        return max(dp[prices.size()][0], dp[prices.size()][1]);        
    }
};