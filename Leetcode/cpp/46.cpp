class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> cur;
        vector<vector<int>> ans;
        vector<bool> visited(nums.size(), false);
        solve(nums, visited, cur, ans);
        return ans;
    }
    
    void solve(vector<int>& nums, vector<bool> &visited, vector<int> &cur, vector<vector<int>> &ans) {
        if(nums.size() == cur.size()) {
            ans.emplace_back(cur);
            return;
        }
        for(int i=0; i<nums.size(); i++) {
            if(!visited[i]) {
                visited[i] = true;
                cur.push_back(nums[i]);
                solve(nums, visited, cur, ans);
                cur.pop_back();
                visited[i] = false;
            }
        }
    }
};