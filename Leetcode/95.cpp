class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        return generateTrees(n, 1);
    }
    
    vector<TreeNode*> generateTrees(int n, int start) {
        if(0 == n) {
            return vector<TreeNode*>({NULL});
        } else if(1 == n) {
            return vector<TreeNode*>({new TreeNode(start)});            
        } else {
            vector<TreeNode*> trees;
            for(int i=0; i<n; i++) {
                vector<TreeNode*> ltrees = generateTrees(i, start);
                vector<TreeNode*> rtrees = generateTrees(n-i-1, start+i+1);
                for(TreeNode *ltree : ltrees)
                    for(TreeNode *rtree : rtrees)
                        trees.push_back(new TreeNode(start+i, ltree, rtree));
            }
            return trees;
        }
    }
};