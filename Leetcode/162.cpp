class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int lo=0, hi=nums.size()-1, idx=-1;
        while(lo <= hi) {
            int mid = lo+(hi-lo)/2;
            if(isAscending(nums, mid)) {
                idx = mid;
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }
        return idx;
    }
    
    bool isAscending(vector<int>& nums, int idx) {
        /// if an element idx is ascending, it means nums[idx-1] < nums[idx]
        /// if idx = 0             -> true 
        /// if idx = nums.size()-1 -> false
        if(0 == idx)
            return true;
        else
            return nums[idx-1] < nums[idx];
    }
};

/// Find Peak Element
/// nums[-1] = nums[n] = -00