/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(nullptr == head)
            return nullptr;
        ListNode *slow1=head, *slow2=head;
        while(head && head->next) {
            head = head->next->next;
            slow1 = slow1->next;
            if(head == slow1) {
                while(slow2 != slow1) {
                    slow2 = slow2->next;
                    slow1 = slow1->next;
                }
                return slow1;
            }
        }
        return nullptr;
    }
};