class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        /// SOP to solve DP problems - 3 steps
        ///
        /// 1. find your state variable and define your function to solve problems for each given states
        ///    Let Ni is a sequence with # i elements and it represents N[0:i]
        //         Nj is a sequence with # j elements and it represents N[0:j]
        ///
        ///    Let dp(Ni) that can determine the max length of LIS of Ni
        ///
        /// 2. find the recurrence relation between states
        ///
        ///    dp(Ni) = max(dp(Nj))+1 if S[i] > S[j], for all j=1 to i-1
        ///
        /// 3. find the base cases
        ///    dp(N0) = 0
        return solve1(nums);   
    }
    
    int solve1(vector<int>& nums) {
        if(1 == nums.size())
            return 1;
        /// 1. initialize an array dp for state variables
        vector<int> dp(nums.size()+1);
        /// 2. set your base cases
        dp[1]=1;
        /// 3. iterate all the state variables
        for(int l=2; l<dp.size(); l++) {
            int max_len = 1;
            for(int i=1; i<l; i++)
                if(nums[l-1] > nums[i-1])
                    max_len = max(max_len, dp[i]+1);
            dp[l] = max_len;
        }
        return *max_element(dp.begin(), dp.end());
    }
    
    int solve2(vector<int>& nums) {
        nums_=nums;
        memo.clear();
        int max_val=0;
        for(int l=1; l<=nums.size(); l++)
            max_val=max(max_val, dp(l));
        return max_val;
    }

    vector<int> nums_;
    unordered_map<int,int> memo;
    int dp(int l) {
        if(1 == l)
            return 1;
        if(0 == memo[l]) {
            int max_len = 1;
            for(int i=1; i<l; i++)
                if(nums_[l-1] > nums_[i-1])
                    max_len = max(max_len, dp(i)+1);
            memo[l] = max_len;
        }
        return memo[l];
    }
    
    ///       0  1  2  3  4  5  6  7  8
    ///       1  2  3  4  5  6  7  8  9
    /// N = [ 1, 3, 6, 7, 9, 4,10, 5, 6]
    ///
    /// dp(N9) = max(dp(N8)+1, dp(N6)+1, dp(N2)+1, dp(N1)+1)
    /// > dp(N8) = max(dp(N6)+1, dp(N2)+1, dp(N1)+1)  = max(4,)
    /// > dp(N6) = max(dp(N2)+1, dp(N1)+1) = max(3,2) = 3
    /// > dp(N2) = max(dp(N1)+1) = 2
    /// > dp(N1) = 1
};
