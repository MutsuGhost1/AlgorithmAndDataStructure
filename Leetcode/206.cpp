class Solution {
public:
    ListNode* reverseList(ListNode *head) {
        return reverseListR(head, NULL);
    }
    
    ListNode* reverseListR(ListNode *c_node, ListNode *p_node) {
        if(c_node) {
            ListNode *head=c_node;
            if(c_node->next)
                head = reverseListR(c_node->next, c_node);
            c_node->next = p_node;
            return head;
        }
        return c_node;
    }
};