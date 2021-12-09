class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        int closest_sum=3000;
        for(int i=0; i<nums.size(); i++) {
            if(0!=i && nums[i-1] == nums[i])
                continue;
            int left=i+1, right=nums.size()-1;
            while(left < right) {
                int curr_sum = nums[i]+nums[left]+nums[right];
                
                if(abs(curr_sum-target) < abs(closest_sum-target))
                    closest_sum = curr_sum;
                
                if(curr_sum > target) {
                    right--;
                } else if(curr_sum < target) {
                    left++;
                } else {
                    return target;
                }
            }
        }
        return closest_sum;
    }
};