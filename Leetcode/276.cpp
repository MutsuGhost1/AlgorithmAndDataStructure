class Solution {
public:
    int numWays(int n, int k) {
        return solve(n, k);
    }
    
    int solve(int n, int k) {
        /// 1. initialize an arrary dp for state variables
        ///vector<vector<int>> dp(n+1, vector<int>(3));
        /// 2. set the base cases
        ///dp[1][1] = k;
        ///dp[1][2] = 0;
        
        int c1=k, c2=0, pre_c1=c1;
        
        /// 3. iterate all state variables
///     for(int i=2; i<dp.size(); i++) {
        for(int i=2; i<=n; i++) {
            c1 = c1*(k-1) + c2*(k-1);
            c2 = pre_c1;
            pre_c1 = c1;
            ///dp[i][1] = dp[i-1][1]*(k-1) + dp[i-1][2]*(k-1);
            ///dp[i][2] = dp[i-1][1];
        }
        /// 4. ans
        /// return dp[n][1] + dp[n][2];        
        return c1+c2;
    }
        
    int solve1(int n, int k) {
        /// 1. initialize an arrary dp for state variables
        vector<vector<int>> dp(n+1, vector<int>(3));
        /// 2. set the base cases
        dp[1][1] = k;
        dp[1][2] = 0;
        /// 3. iterate all state variables
        for(int i=2; i<dp.size(); i++) {
            dp[i][1] = dp[i-1][1]*(k-1) + dp[i-1][2]*(k-1);
            dp[i][2] = dp[i-1][1];
        }
        /// 4. ans
        return dp[n][1] + dp[n][2];
    }
    
    /// 1. find the state variables and function that return the ans to given states
    ///    let i means the i-th post, 1 <= i <= n
    ///    let j means there's j consecutive same colors, 1 <= j <= 2
    ///    let dp(i, j) means the # painting colors in the post n that ends with j consecutive same colors
    ///
    /// 2. find the recurrence replation
    ///      dp(i, 1) = dp(i-1, 1)*(k-1) + dp(i-1, 2)*(k-1)
    ///      dp(i, 2) = dp(i-1, 1)*1
    ///
    /// 3. find the base cases
    ///      dp(1, 1) = k
    ///      dp(1, 2) = 0
    ///
    /// 4. ans = sum({dp(n, 1), dp(n, 2)})
    ///      it means the # painting colors in the post n
    ///
    int k_;
    unordered_map<int, unordered_map<int,int>> memo;
    int solve2(int n, int k) {
        k_ = k;
        return dp(n, 1) + dp(n, 2);
    }
    
    int dp(int i, int j) {
        if(1 == j) {
            /// base cases
            if(1 == i)
                return k_;
            if(0 == memo[i][j])
                memo[i][j] = dp(i-1, 1)*(k_-1) + dp(i-1, 2)*(k_-1);
            return memo[i][j];
        } else {
        /// 2 == j
            if(1 == i)
                return 0;
            if(0 == memo[i][j])
                memo[i][j] = dp(i-1, 1);
            return memo[i][j];
        }
    }
};