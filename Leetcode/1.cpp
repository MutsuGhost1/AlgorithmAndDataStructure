class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        int i=0, j=nums.size()-1;
        while(i <= j) {
            if(nums[i]+nums[j] > target)
                j--;
            else if(nums[i]+nums[j] < target)
                i++;
            else
                return {i, j};
        }
        return {};
    }
};