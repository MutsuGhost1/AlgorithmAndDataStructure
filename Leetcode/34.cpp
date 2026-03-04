class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return vector<int>({search(nums, target), search(nums, target, false)});
    }
private:
    
    int search(const vector<int>& nums, int target, const bool left_most=true) {
        int lo=0, hi=nums.size()-1, idx=-1;
        while(lo <= hi) {
            int mid = lo+(hi-lo)/2;
            if(target == nums[mid]) {
                idx = mid;
                if(left_most)
                    hi = mid-1;
                else
                    lo = mid+1;
            } else if (target > nums[mid]) {
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }
        return idx;
    }
};