class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        vector<int> tmp;
        nSum(nums, tmp, ans, 0, 3, 0);
        return ans;
    }
    
    void nSum(vector<int>& nums, vector<int> &tmp, vector<vector<int>> &ans, int idx, const int n, int target) {
        /// base cases
        if(tmp.size() == n-2) {
            int left=idx, right=nums.size()-1;
            while(left < right) {
                if(left != idx && nums[left-1] == nums[left]) {
                    left++;
                    continue;
                }
                if(right != nums.size()-1 && nums[right] == nums[right+1]) {
                    right--;
                    continue;
                }
                if(nums[left]+nums[right] > target)
                    right--;
                else if (nums[left]+nums[right] < target)
                    left++;
                else {
                    tmp.push_back(nums[left]);
                    tmp.push_back(nums[right]);
                    ans.push_back(tmp);
                    tmp.pop_back();
                    tmp.pop_back();
                    left++;
                    right--;
                }
            }
            return;
        }
        for(int i=idx; i<nums.size(); i++) {
            /// remove the duplicate pairs
            if(i != idx && nums[i-1] == nums[i])
                continue;
            /// pruning
            if(0 < target && nums[i] > target || 0 > target && nums[i] >= 0)
                break;
            tmp.push_back(nums[i]);
            nSum(nums, tmp, ans, i+1, n, target-nums[i]);
            tmp.pop_back();
        }
    }
};