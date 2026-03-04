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
    void flatten(TreeNode* root) {
        flattenR(root);
    }
    
    /// same as 430. Flatten a Multilevel Doubly Linked List
    TreeNode* flattenR(TreeNode* curr, TreeNode **pptail=NULL) {
        if(curr) {
            TreeNode *head=curr, *tail=curr;
            TreeNode *nhead=nullptr, *ntail=nullptr;
            if(curr->right) {
                nhead = flattenR(curr->right, &ntail);
            }
            if(curr->left) {
                TreeNode *ctail = nullptr;
                TreeNode *chead = flattenR(curr->left, &ctail);
                curr->left = nullptr; /// reset child
                curr->right = chead;
                ctail->right = nhead;
                if(ctail)
                    tail = ctail;
            }
            if(ntail)
                tail = ntail;
            if(pptail)
                *pptail = tail;
            return head;
        }
        return curr;
    }

    void solve1(TreeNode* root) {
        if(!root) return;
        
        TreeNode *prev = nullptr;
        stack<TreeNode*> stk({root});
        while(!stk.empty()) {
            TreeNode *curr = stk.top();
            stk.pop();
            if(curr->right)
                stk.push(curr->right);
            if(curr->left)
                stk.push(curr->left);
            if(!prev)
                prev = curr;
            else {
                prev->right = curr;
                prev->left = nullptr;
                prev = curr;
            }
        }        
    }

};