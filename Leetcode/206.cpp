class Solution {
public:
    ListNode* reverseList(ListNode *head) {
        return reverseListR(nullptr, head);
    }
    
    ListNode* reverseListR(ListNode *prev, ListNode *curr) {
        ///            p  c
        ///            
        /// [ 1, 2, 3, 4, 5]
        ///
        if(curr) {
            ListNode *head = reverseListR(curr, curr->next);
            curr->next = prev;
            return head;
        }
        return prev;
    }
};