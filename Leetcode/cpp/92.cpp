/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *tmp1=nullptr, *tmp2=nullptr;
        return reverseBetweenHelper(head, nullptr, &tmp1, &tmp2, left, right);
    }
    
    ListNode* reverseBetweenHelper(ListNode *curr, ListNode *prev, ListNode **ppr, ListNode **pprn,
                                   int left, int right, int idx=1) {
        if(left == right)
            return curr;
        if(curr) {
            reverseBetweenHelper(curr->next, curr, ppr, pprn, left, right, idx+1);
            if(idx == right) {
                *ppr = curr;
                *pprn = curr->next;
            }
            if(left < idx && idx <= right) {
                curr->next = prev;
            } else if(idx == left) {
                curr->next = *pprn;
                if(nullptr != prev) {
                    prev->next = *ppr;
                }
            }            
        }
        return (1 != left) ? curr : *ppr ; 
    }
};