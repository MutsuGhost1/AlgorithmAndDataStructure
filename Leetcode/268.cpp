class Solution {
public:
    int missingNumber(vector<int>& nums) {
/*
        int ans = nums.size()*(nums.size()+1)/2;
        for(int num: nums)
            ans -= num;
*/
        int ans = 0;
        for(int i=0; i<nums.size(); i++)
            ans += (nums[i]-i-1);
        return -ans;
    }
    
    int solve1(vector<int>& nums) {
        /// dry run
        ///           0 1 2
        /// > nums = [3,0,1]
        bool is_zero_marked = false;
        int miss_num = nums.size();
        for(int num : nums) {
            if(miss_num > abs(num) && nums[abs(num)] >= 0)
                if(0 == nums[abs(num)])
                    is_zero_marked = true;
                else
                    nums[abs(num)] = -nums[abs(num)];
        }

        for(int i=0; i<nums.size(); i++)
            if(nums[i] > 0 || (nums[i] == 0 && !is_zero_marked))
                miss_num = i;
        return miss_num;        
    }
};