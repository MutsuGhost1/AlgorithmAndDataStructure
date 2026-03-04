class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        /// copy the cyclic data to the end of nums
        int kOSize=nums.size();
        nums.insert(nums.end(), nums.begin(), nums.end()-1);
        stack<int> stk;
        vector<int> ans;
        for(int i=nums.size()-1; i>=0; i--) {
            while(!stk.empty() && nums[i]>=stk.top()) {
                stk.pop();
            }
            ans.push_back(0 < stk.size() ? stk.top() : -1);
            stk.push(nums[i]);
        }
        return vector<int>(ans.rbegin(), ans.rbegin()+kOSize);
    }
};