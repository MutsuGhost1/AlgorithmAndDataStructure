class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        /// kandane's algorithm
        int current = nums[0], best = current;
        for (int i = 1; i < nums.size(); i++) {
            current = nums[i] + max(current, 0);
            best = max(best, current);
        }
        return best;
    }
    
    int solve0(vector<int>& nums) {
        if(1 == nums.size())
            return nums[0];
        int current = nums[0];
        int max_val = current;
        for(int i=1; i<nums.size(); i++) {
            current = max(current+nums[i], nums[i]);
            max_val = max(max_val, current);
        }
        return max_val;
    }
    
    int solve1(vector<int>& nums) {
        /// 1. initialize an array dp for each state variables
        vector<int> dp(nums.size());
        /// 2. set base case
        dp[0] = nums[0];
        /// 3. iterate over each states
        int max_val = dp[0];
        for(int i=1; i<dp.size(); i++) {
            dp[i] = max(dp[i-1]+nums[i], nums[i]);
            max_val = max(max_val, dp[i]);
        }
        return max_val;
    }
    
    int solve2(vector<int>& nums) {
        nums_ = nums;
        int max_val = INT_MIN;
        for(int i=0; i<nums_.size(); i++)
            max_val = max(max_val, dp(i));
        return max_val;
    }

    unordered_map<int,int>memo;
    vector<int> nums_;
    int dp(int i) {
        if(0 == i)
            return nums_[i];
        if(auto iter=memo.find(i); iter==memo.end())
            memo[i] = max(dp(i-1)+nums_[i], nums_[i]);
        return memo[i];
    }
    
///          0  1  2  3  4
/// nums = [ 5, 4,-1, 7, 8]
///
/// dp(4) = max(dp(3)+nums[4], nums[4])
/// dp(3) = max(dp(2)+nums[3], nums[3])

/// 1. let dp(i) is the maximum sum of subarray that include i
///    dp(i) = max(dp(i-1)+nums[i], nums[i])
///
/// 2. ans is max(dp(i)) for i=1 ~ n
    
    
/// 1.2. let dp(i, j) is the maximum sum of subarray
///
/// wrong:
///    dp(i, j) = max(dp(i+1, j), dp(i, j-1), dp(i+1, j)+nums[i], dp(i, j-1)+nums[j])
///                   0 <= i < |S|
///                   i <= j < |S| 
///    dp(i, j) 不代表它就是 i~j 的區間, 因此 dp(i+1, j)+nums[i] 代表的是找出正數和
///
/// 3. find the base cases
///        dp(i, j) = nums[i] if i == j
///
///    idx  =  0  1  2  3  4  
///    nums = [5, 4,-1, 7, 8]
///
///   > dp(0, 4) = max(dp(1, 4)+nums[0], dp(0, 3)+nums[4], dp(1, 4), dp(0, 3))
///   >> dp(1, 4) = max(dp(2, 4)+nums[1], dp(1, 3)+nums[4], dp(2, 4), dp(1, 3))
///   >>> dp(2, 4) = max(dp(3, 4)+nums[2], dp(2, 3)+nums[4], dp(3, 4), dp(2, 3))
///                = max(15-1, 7+8, 15, 7) = 15  <--- wrong
///   >>>> dp(3, 4) = max(dp(4, 4)+nums[3], dp(3, 3)+nums[4], dp(4, 4), dp(3, 3))
///                 = max(8+7,  7+8, 8,  7) = 15
///   >>>>> dp(4, 4) = nums[4] = 8
///   >>>>> dp(3, 3) = nums[3] = 7
///   >>>> dp(2, 3) = max(dp(3,3)+nums[2], dp(2,2)+nums[3], dp(3,3), dp(2,2))
///                 = max(7-1, -1+7, 7, -1) = 7
///   >>>>> dp(3,3) = nums[3] =  7
///   >>>>> dp(2,2) = nums[2] = -1
///
/// 4. ans is

    int solve2(vector<int>& nums, int i, int j) {
        if(i == j)
            return nums[i];
        return max(max(nums[i], solve2(nums, i+1, j)+nums[i]), 
                   max(nums[j], solve2(nums, i, j-1)+nums[j]));
    }
    
    int solve3(vector<int>& nums) {
        /// approach 1 - brust force - TLE
        /// O(N^3)
        int max_sum=INT_MIN;
        for(int k=1; k<=nums.size(); k++) {
            for(int i=0; i<=nums.size()-k; i++) {
                int sum=0;
                for(int j=i; j<nums.size() && j<i+k; j++)
                    sum += nums[j];
                max_sum=max(max_sum, sum);
            }
        }
        return max_sum;        
    }
};

///
/// nums = [-2, 1,-3, 4,-1, 2, 1,-5, 4]
///             1,-3, 4, 
///
///
