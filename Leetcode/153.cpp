class Solution {
public:
    int findMin(vector<int>& nums) {
///     return solve3(nums, 0, nums.size()-1);
        int lo=0, hi=nums.size()-1, ans=INT_MAX;
        while(lo <= hi) {
            int mid = lo+(hi-lo)/2;
            if(nums[lo] <= nums[mid]) {
                ans = min(ans, nums[lo]);
                lo=mid+1;
            } else {
                ans = min(ans, nums[mid]);
                hi=mid-1;
            }
        }
        return ans;
    }
    
    /// time complexity:  O(N)
    /// space complexity: O(1)
    int solve1(vector<int>& nums) {
        return *min_element(nums.begin(), nums.end());
    }

    /// divide and conquer
    ///
    /// time  complexity: T(N)=2*T(N/2)+1 ~= O(N)
    /// space complexity: O(1)
    int solve2(vector<int>& nums, int lo, int hi) {
        /// nums = [0,1,2,4,5,6,7]
        ///
        ///         l     m     h
        ///         0 1 2 3 4 5 6
        /// nums = [4,5,6,7,0,1,2]
        ///         ^           ^
        ///         l h
        ///         m
        /// nums = [1,2]
        if(lo == hi || nums[lo] <= nums[hi])
            return nums[lo];
        int mid = lo+(hi-lo)/2;
        return min(solve2(nums, lo, mid), solve2(nums, min(mid+1,hi), hi));
    }
    
    /// divide and conquer
    /// time  complexity: T(N)=T(N/2)+1 ~= O(LogN)
    /// space complexity: O(1)
    int solve3(vector<int>& nums, int lo, int hi) {
        if(lo == hi)
            return nums[lo];
        /// prevent from overflow
        int mid = lo+(hi-lo)/2;
        if(nums[lo] <= nums[mid])
            return min(nums[lo], solve3(nums, mid+1, hi));
        else
            return min(nums[mid], solve3(nums, lo, mid-1));
    }
};

/// uniques elements
///
///      
/// nums = [0,1,2,4,5,6,7]
///
/// nums = [3,4,5,1,2]
///               V
/// nums = [4,5,6,7,0,1,2]
///                 V

/// Given the sorted rotated array nums of unique elements, return the minimum element of this array.