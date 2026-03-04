class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head)
            return nullptr;
        /// [  1,  2,  3,  4,  5]
        int idx = 0;
        ListNode *currs[2] ={nullptr}, *curr=head, *e_head=nullptr;
        while(curr) {
            if(nullptr == currs[idx]) {
                currs[idx] = curr;
                if(1 == idx)
                    e_head = curr;                
            } else {
                currs[idx]->next = curr;
                currs[idx] = curr;
            }
            idx ^= 1;
            curr = curr->next;
        }
        currs[0]->next = e_head;
        if(currs[1])
            currs[1]->next = nullptr;
        return head;
    }
};