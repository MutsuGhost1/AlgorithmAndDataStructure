class Solution {
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        return solve1(nums, k);
    }
    
    int solve2(vector<int>& nums, int k) {
        /// Time complexity: O(N^2)
        int max_val = INT_MIN;
        for(int i=0; i<nums.size(); i++)
            for(int j=i+1; j<nums.size(); j++)
                if(nums[i]+nums[j] < k)
                    max_val = max(max_val, nums[i]+nums[j]);
        return max_val == INT_MIN ? -1 : max_val;
    }
    
    int solve1(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        int max_val=-1;
        int left=0, right=nums.size()-1;
        while(left < right) {
            if(nums[left]+nums[right] < k) {
                max_val = max(max_val, nums[left]+nums[right]);
                left++;
            } else {
            /// nums[left]+nums[right] >= k
                right--;
            }
        }
        return max_val;
    }
};