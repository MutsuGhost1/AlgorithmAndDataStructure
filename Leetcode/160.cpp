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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        return solve1(headA, headB);
    }
    
    ListNode *solve1(ListNode *headA, ListNode *headB) {
        /// Time Complexity: O(M+N)

        /// 1. Note that the linked lists must retain 
        ///      their original structure after the function returns.
        /// 2. Could you write a solution that runs in O(n) time and use only O(1) memory?

        if(nullptr == headA || nullptr == headB)
            return nullptr;

        /// 1. Make L1 as circular list
        ListNode *tailA=headA;
        while(tailA && tailA->next)
            tailA = tailA->next;
        tailA->next = headA;
        /// 2. Use fast/slow pointer to find the entry of the loop
        ListNode *intersect_node = nullptr;
        ListNode *slow=headB, *fast=headB;
        while(fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if(slow == fast) {
                while(headB && headB != slow) {
                    headB = headB->next;
                    slow = slow->next;
                }
                if(headB)
                    intersect_node = headB;
                break;
            }
        }
        /// 3. Restore L1
        tailA->next = NULL;
        
        return intersect_node;        
    }
};