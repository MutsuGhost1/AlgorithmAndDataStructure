/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        return solve2(root);
    }

    /// intuition
    /// > convert binary tree to double linked list
    ///   > process a node by assigning 
    ///     > its left  to its left max
    ///     > its right to its right min
    ///   > finally link its left min and right max to form a circular double linked list
    
    Node* solve2(Node *root) {       
        Node *pmin_node=NULL, *pmax_node=NULL;
        solve2Helper(root, &pmin_node, &pmax_node);
        if(pmin_node)
            pmin_node->left = pmax_node;
        if(pmax_node)
            pmax_node->right= pmin_node;
        return pmin_node;        
    }
    
    void solve2Helper(Node *node, Node **pp_min, Node **pp_max) {
        if(node){
            *pp_min = node;
            if(node->left) {
                Node *pl_min=NULL, *pl_max=NULL;
                solve2Helper(node->left, &pl_min, &pl_max);
                pl_max->right = node;
                node->left = pl_max;
                *pp_min = pl_min;
            }
            *pp_max = node;
            if(node->right) {
                Node *pr_min=NULL, *pr_max=NULL;
                solve2Helper(node->right, &pr_min, &pr_max);
                node->right = pr_min;
                pr_min->left = node;
                *pp_max = pr_max;
            }
        }
    }
    
    Node *solve1(Node* root) {
        Node *head=NULL;
        vector<Node*> order;
        treeToDoublyListR(root, order);
        const int kSize=order.size();
        for(int i=0; i<kSize-1; i++) {
            order[i]->right = order[i+1];
            order[i+1]->left = order[i];
        }
        if(kSize > 0) {
            order[0]->left = order[order.size()-1];
            order[order.size()-1]->right = order[0];
            head = order[0];
        }
        return head;        
    } 
    
    void treeToDoublyListR(Node* node, vector<Node*> &order) {
        if(node){
            treeToDoublyListR(node->left, order);
            order.push_back(node);
            treeToDoublyListR(node->right, order);
        }
    }

};