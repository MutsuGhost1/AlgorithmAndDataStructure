class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> paths;
        inorder(root, 0, paths);
        return paths;
    }
    
    void inorder(TreeNode* root, int cur_level, vector<vector<int>> &paths) {
        if(root) {
            if(cur_level == paths.size())
                paths.push_back(vector<int>());
            inorder(root->left, cur_level+1, paths);
            paths[cur_level].push_back(root->val);
            inorder(root->right, cur_level+1, paths);
        }
    }
};