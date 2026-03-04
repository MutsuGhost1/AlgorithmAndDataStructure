class Solution {
public:
    const int kMod=1000000007;
    int numRollsToTarget(int d, int f, int target) {
        /// 1. define state variables and function/data struct compute/contains the answer to each states
        ///    let d is # of dice we should roll
        ///    let t is the target sum for our all dice
        ///    let dp(d, target) is the number of possible ways 
        ///        to roll the dice so the sum of the face-up numbers equals target
        ///
        /// 2. find the recurrence relation to transition between states
        ///    dp(d, t) = accumulate({dp(d-1, t-k) for all 1<=k<=f }, 0) if 0 != d && 0 != t
        ///
        /// 3. find the base cases
        ///    dp(d, t) = 1 if 0 == d && 0 == t
        ///               0 if 0 == d && 0 != t
        ///               0 if 0 != d && 0 == t
        ///
        /// 4. the ans is dp(d, t)
        
        /// 1. initialize an array dp for each state variables
        vector<vector<int>> dp(d+1, vector<int>(target+1));
        /// 2. set the base cases
        dp[0][0] = 1;
        /// 3. iterate all state variables
        for(int i=1; i<dp.size(); i++)
            for(int j=1; j<dp[i].size(); j++)
                for(int k=1; k<=f; k++)
                    if(0 <= j-k)
                        dp[i][j] = (dp[i][j]+dp[i-1][j-k])%kMod;
        return dp[d][target];
    }
    int solve1(int d, int f, int target) {
        e = f;
        return dp(d, target);
    }

    int e;
    unordered_map<int,unordered_map<int,int>> memo;
    int dp(int d, int target) {
        if(0 == d && 0 == target)
            return 1;
        /// d=2, f=6, target=7
        /// dp(2, 1, 7), e=6
        ///     num = 0
        ///     for(int i=1; i<=6; i++)
        ///         num += dp(2-1, 1, 7-1)
        ///                dp(1,   1,   6)
        ///                num=0
        ///                for(int i=1; i<=6; i++)
        ///                    num += dp(1-1, 1, 6-1) = 0
        ///                    num += dp(1-1, 2, 6-2) = 0
        ///                    num += dp(1-1, 3, 6-3) = 0
        ///                    num += dp(1-1, 4, 6-4) = 0
        ///                    num += dp(1-1, 5, 6-5) = 0
        ///                    num += dp(1-1, 6, 6-6) = 1
        ///                num=1
        ///         num += dp(2-1, 2, 7-2)
        ///                dp(1,   2,   5)
        ///                num=0
        ///                for(int i=2; i<=6; i++)
        ///                    num += dp(1-1, 2, 5-2) = 0
        ///                    num += dp(1-1, 3, 5-3) = 0
        ///                    num += dp(1-1, 4, 5-4) = 0
        ///                    num += dp(1-1, 5, 5-5) = 1
        ///                    num += dp(1-1, 6, 5-6) = 0
        ///         num += dp(2-1, 3, 7-3)
        ///                dp(1,   3,   4)
        ///                num=0
        ///                for(int i=3; i<=6; i++)
        ///                    num += dp(1-1, 3, 5-3) = 0
        ///                    num += dp(1-1, 4, 5-4) = 0
        ///                    num += dp(1-1, 5, 5-5) = 1
        ///                    num += dp(1-1, 6, 5-6) = 0
        ///         num += dp(2-1, 4, 7-4)
        ///                dp(1,   4,   3)
        ///         num += dp(2-1, 5, 7-5)
        ///                dp(1,   5,   2)
        ///         num += dp(2-1, 6, 7-6)
        ///                dp(1,   6,   1)
        /// 
        if(auto iter=memo.find(d); iter!=memo.end())
            if(auto iter2=iter->second.find(target); iter2!=iter->second.end())
                return memo[d][target];
        if(0 < d && 0 < target) {
            int num = 0;
            for(int i=1; i<=e; i++)
                if(0 <= target-i)
                    num = (num + dp(d-1, target-i))%(1000000007);
            return memo[d][target] = num;
        }
        return 0;
    }
};