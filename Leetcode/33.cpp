class Solution {
public:
    ///                l     m     h, 
    ///                0 1 2 3 4 5 6
    /// Input: nums = [4,5,6,0,1,2,3], target = 0
    ///
    ///
    /// We must design an algorithm to handle search in a roated/sorted array array/
    ///
    /// [5, 5, 1, 2, 5]
    ///
    int search(vector<int>& nums, int target) {
        int lo=0, hi=nums.size()-1;
        while(lo <= hi) {
            int mid = lo+(hi-lo)/2;
            if(target == nums[mid])
                return mid;
            /// the left part is sorted
            if(nums[lo] <= nums[mid]) {
                /// target is in left part
                if(nums[lo] <= target && target < nums[mid])
                    hi = mid-1;
                else
                /// target is not in left part
                    lo = mid+1;
            } else {
                /// target is in right part
                if(nums[mid] < target && target <= nums[hi])
                    lo = mid+1;
                else
                /// target is not in right part
                    hi = mid-1;
            }
        }
        return -1;
    }
};