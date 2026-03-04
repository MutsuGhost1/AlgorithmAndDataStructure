class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
/*
        vector<vector<int>> dp(costs.size(), vector<int>(3));
        dp[0][0] = costs[0][0];
        dp[0][1] = costs[0][1];
        dp[0][2] = costs[0][2];
*/
        int red=costs[0][0], blue=costs[0][1], green=costs[0][2];
        int p_red=red, p_blue=blue;
        for(int i=1; i<costs.size(); i++) {
            red = min(p_blue, green) + costs[i][0];
            blue = min(green, p_red) + costs[i][1];
            green = min(p_red, p_blue) + costs[i][2];
            p_red = red;
            p_blue = blue;
        }
        return min({red, blue, green});
    }
    
    int solve1(vector<vector<int>>& costs) {
        /// PD
        ///
        /// There is a row of n, where each house can be painted one of three colors: red, blue, or green.
        /// he cost of painting each house with a certain color is different.
        /// You have to paint all the houses such that no two adjacent houses have the same color.
        ///
        /// 4 steps to solve DP problem
        ///
        /// 1. find the state variables and function/data struct that compute/contain the answer to given state
        ///    let i means the i-th house
        ///    let dp(i, 0) is the min cost if the i-th house with red color
        ///        dp(i, 1) is the min cost if the i-th house with blue color
        ///        dp(i, 2) is the min cost if the i-th house with green color
        ///
        /// 2. find the recurrence relation to transition between states
        ///    let dp(i, 0) = min(dp(i-1, 1), dp(i-1, 2)) + cost[i][0]
        ///        dp(i, 1) = min(dp(i-1, 0), dp(i-1, 2)) + cost[i][1]
        ///        dp(i, 2) = min(dp(i-1, 0), dp(i-1, 1)) + cost[i][2]
        ///
        /// 3. set the base cases
        ///    dp(0, 0) = cost[0][0]
        ///    dp(0, 1) = cost[0][1]
        ///    dp(0, 2) = cost[0][2]
        ///
        /// 4. the ans is
        ///    min(dp(costs.size()-1, 0), dp(costs.size()-1, 1), dp(costs.size()-1, 2))
        

        vector<vector<int>> dp(costs.size(), vector<int>(3));
        dp[0][0] = costs[0][0];
        dp[0][1] = costs[0][1];
        dp[0][2] = costs[0][2];
        for(int i=1; i<dp.size(); i++) {
            dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0];
            dp[i][1] = min(dp[i-1][2], dp[i-1][0]) + costs[i][1];
            dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2];
        }
        return min({dp[dp.size()-1][0], dp[dp.size()-1][1], dp[dp.size()-1][2]});        
    }
};