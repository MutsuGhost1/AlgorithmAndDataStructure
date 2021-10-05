class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> lvl_odrs;
        int lvl = 0;
        queue<Node*> q({root});
        while(!q.empty()) {
            vector<int> lvl_odr;
            for(int i=0, lvl_size=q.size(); i<lvl_size ; i++){
                Node *curr_node=q.front();
                q.pop();
                if(curr_node) {
                    lvl_odr.push_back(curr_node->val);
                    for(auto node : curr_node->children)
                        q.push(node);

                }
            }
            if(0 < lvl_odr.size())
                lvl_odrs.emplace_back(lvl_odr);
            lvl++;
        }
        return lvl_odrs;
    }
};