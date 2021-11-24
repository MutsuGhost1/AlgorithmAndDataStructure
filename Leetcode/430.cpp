/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        return flattenR(head);
    }
    
    /// [11, 12]
    /// [11]-> 
    ///        [12] ->
    ///                null,null
    ///         c/t
    /// [11]-> [12]
    
    
    Node* flattenR(Node* curr, Node **pptail=NULL) {
        if(curr) {
            Node *head=curr, *tail=curr;
            Node *nhead=nullptr, *ntail=nullptr;
            if(curr->next) {
                nhead = flattenR(curr->next, &ntail);
            }
            if(curr->child) {
                Node *ctail = nullptr;
                Node *chead = flattenR(curr->child, &ctail);
                curr->child = nullptr; /// reset child
                curr->next = chead;
                chead->prev = curr;
                ctail->next = nhead;
                if(nhead)
                    nhead->prev = ctail;
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
};