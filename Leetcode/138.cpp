/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    /// clone graph is easier than the question
    Node* copyRandomList(Node* head) {
        unordered_map<Node*,Node*> hmap;
        return solve2(head, hmap);
    }
    
    Node* solve1(Node* head) {
        /// > use hash map to map the original node to new node
        ///   then we can look up the random by address
        /// > two pass algorithm
        if(!head)
            return nullptr;
        Node *curr=head;
        unordered_map<Node*,Node*> hmap;
        while(curr) {
            Node *node = new Node(curr->val);
            hmap[curr] = node;
            curr = curr->next;
        }
        curr=head;
        while(curr) {
            hmap[curr]->next = hmap[curr->next];
            hmap[curr]->random = hmap[curr->random];
            curr = curr->next;
        }
        return hmap[head];        
    }
    
    Node* solve2(Node* curr, unordered_map<Node*,Node*> &hmap) {
        if(curr) {
            if(!hmap[curr]) {
                hmap[curr] = new Node(curr->val);
                if(curr->next)
                    hmap[curr]->next = solve2(curr->next, hmap);
                if(curr->random)
                    hmap[curr]->random = solve2(curr->random, hmap);
            }
            return hmap[curr];
        }
        return nullptr;
    }
};