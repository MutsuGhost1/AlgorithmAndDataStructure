class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        stack<int> stk;
        vector<int> ans(1);
        solve(head, 0, stk, ans);
        return ans;
    }
    
    void solve(ListNode *node, int cur_idx, stack<int> &stk,vector<int> &ans) {
        if(node) {
            solve(node->next, cur_idx+1, stk, ans);
            while(!stk.empty() && node->val >= stk.top())
                stk.pop();
            /// allocate it until the tail, therefore we needn't reverse it
            if(ans.size() < cur_idx+1)
                ans.resize(cur_idx+1);
            ans[cur_idx] = 0 < stk.size() ? stk.top() : 0;
            stk.push(node->val);
        }
    }
};