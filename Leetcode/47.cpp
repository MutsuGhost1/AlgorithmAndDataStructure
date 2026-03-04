class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> visited(nums.size(), false);
        vector<int> tmp; 
        vector<vector<int>> ans;
        solve(nums, visited, tmp, ans);
        return ans;
    }

    void solve(vector<int>& nums, vector<bool> &visited, vector<int>& tmp, vector<vector<int>> &ans) {
        if(tmp.size() == nums.size()) {
            ans.push_back(tmp);
            return;
        }
        unordered_map<int, bool> used;
        for(int i=0; i<nums.size(); i++) {
            if(!visited[i] && !used[nums[i]]) {
                visited[i]=true;
                used[nums[i]] = true;
                tmp.push_back(nums[i]);
                solve(nums, visited, tmp, ans);
                tmp.pop_back();
                visited[i]=false;
            }
        }
    }
    
    /// ituition
    /// nums = [1, 1, 2]
    /// for i=0; i<3; i++
    /// nums[0] = (1, ?, ?) then choose [X, 1, 2]
    /// nums[1] = (1, ?, ?) then choose [1, X, 2] X 
    ///                     --> don't choose duplicate value in the same level
    /// nums[2] = (2, ?, ?) then choose [1, 1, X]
        
};