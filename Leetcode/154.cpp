class Solution {
public:
    int findMin(vector<int>& nums) {
        return solve(nums, 0, nums.size()-1);
    }
    
    int solve(vector<int>& nums, int lo, int hi) {
        if(lo > hi)
            return INT_MAX;
        if(lo == hi)
            return nums[lo];
        if(nums[lo] == nums[hi]) {
            return min(nums[lo], solve(nums, lo+1, hi-1));
        }
        int mid = lo+(hi-lo)/2;
        if(nums[lo] <= nums[mid])
            return min(nums[lo], solve(nums, mid+1, hi));
        else
            return min(nums[mid],solve(nums, lo, mid-1));
    }
};