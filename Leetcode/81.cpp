class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size()-1;
        while(lo <= hi) {                       
            int mid = lo + (hi-lo)/2;
            if(target == nums[mid]) {
                return true;
            }

            if(nums[lo] == nums[hi]) {
                if(target == nums[lo])
                    return true;
                lo++;
                hi--;
                continue;
            }

                
            /// find the sorted part
            if(nums[lo] <= nums[mid]) {
                if(nums[lo] <= target && target < nums[mid])
                    /// if target in the sorted part
                    hi = mid-1;
                else
                    /// if target is not in the sorted part
                    lo = mid+1;
            } else { /// nums[mid] < nums[hi]
                if(nums[mid] < target && target <= nums[hi])
                    /// if target in the sorted part
                    lo = mid+1;
                else
                    /// if target is not in the sorted part
                    hi = mid-1;                    
            }
        }
        return false;
    }
};

/// not necessarily with distinct values
///   不回傳 idx 回傳 true or false, 因為有多個值
///
/// dry run
///
/// case 1
///  idx =  0  1  2  3  4  5
/// nums = [1, 6, 1, 1, 1, 1]
///         l     m        r
/// case 2
///  idx =  0  1  2  3  4 
/// nums = [5, 6, 0, 0, 1]
///         l     m     r
///
/// a. [A'][A'']
/// b. [A''][A']
/// c. [A]