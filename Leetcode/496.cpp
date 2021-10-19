class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> stk;
        unordered_map<int, int> hmap;
        for(int i=nums2.size()-1; i>=0; i--) {
            while(!stk.empty() && nums2[i] >= stk.top()) {
                stk.pop();
            }
            hmap[nums2[i]] = stk.size() !=0 ? stk.top() : -1;
            stk.push(nums2[i]);
        }
        /// all the number is unique
        vector<int> ans;
        for(int i=0; i<nums1.size(); i++)
            ans.push_back(hmap[nums1[i]]);
        return ans;
    }
};