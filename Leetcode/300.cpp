class Solution {
public:
/*
    3 Steps to find the solution of the DP problems

      1. find the state variables and the function that return the answer to given states
         let Ni is a # of sequence N[0:i]
            dp(Ni) is the lenght of the longest increasing number to Ni

      2. find the recurrence relation to transtion between states
         dp(Ni) = max(dp(Nj)+1) if N[i-1] > N[j-1] else 1, for 1 <= j <= i-1 if i > 1

      3. find the base cases
         dp(N1) = 1

      4. wrap it up
         dp(Ni) = max(dp(Nj)+1) if N[i-1] > N[j-1] else 1, for 1 <= j <= i-1 if i > 1
         dp(Ni) = 1, otherwise (i <= 1)
      
      5. ans
         the ans is max(dp(i)) for 1<=i<=|N|
 */
    int lengthOfLIS(vector<int>& nums) {
        return solve1(nums);
    }
    
    int solve1(vector<int>& nums) {
        /// 1. initialize an array dp for state variables
        vector<int> dp(nums.size()+1, 1);
        /// 2. set the base cases
        ///dp[1] = 1;
        /// 3. iterate over all the state variables
        for(int i=2; i<dp.size(); i++) {
            /// int max_val=1;
            for(int j=1; j<i ; j++)
                if(nums[i-1] > nums[j-1])
                    /// max_val = max(max_val, dp[j]+1);
                    dp[i] = max(dp[i], dp[j]+1);
            ///dp[i]=max_val;
        }
        return *max_element(dp.begin(), dp.end());
    }
    
    vector<int> nums_;
    int solve2(vector<int>& nums) {
        nums_=nums;
        int max_val=1;
        for(int i=1; i<=nums.size(); i++)
            max_val = max(max_val, dp(i));
        return max_val;
    }
    
    int dp(int i) {
        if(1 == i)
            return 1;
        int max_val = 1;
        for(int j=1; j<i ; j++)
            if(nums_[i-1] > nums_[j-1])
                max_val = max(max_val, dp(j)+1);
        return max_val;
    }
};