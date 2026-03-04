/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        int a, b;
        return checkValidBST(root, a, b);
    }
    
    /// predecessor
    /// successor
    bool checkValidBST(TreeNode *node, int &lbound, int &ubound) {
        if(node) {
            int l=node->val;
            if(node->left) {
                if(!checkValidBST(node->left, lbound, ubound))
                    return false;
                if(!(node->val > ubound))
                    return false;
                l=lbound;
            }
            int u=node->val;
            if(node->right) {
                if(!checkValidBST(node->right, lbound, ubound))
                    return false;
                if(!(node->val < lbound))
                    return false;
                u=ubound; 
            }
            lbound=l;
            ubound=u;
        }
        return true;
    }
};