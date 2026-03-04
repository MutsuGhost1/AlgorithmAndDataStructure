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
//        return solve1(headA, headB);
        return solve2(headA, headB);
    }
    
    /// Find the difference of the length for A and B is D
    ///   The longger one A must wait D steps, then start to go
    ///
    ///   If the intersection of A and B is not empty,
    ///     A and B will meet eventually.
    ///
    /// Time  Complexity: O(len|A|+len|B|+min(len|A|+len|B|))
    /// Space Complexity: O(1)
    ListNode* solve2(ListNode *headA, ListNode *headB) {
        ListNode *ll = headA, *sl = headB;
        int diff_len = lenOfList(headA) - lenOfList(headB);
        if(0 > diff_len) {
            swap(ll, sl);
            diff_len = -diff_len;
        }
        while(diff_len-- > 0)
            ll = ll->next;
        while(ll && sl) {
            if (ll == sl)
                return ll;
            ll = ll->next;
            sl = sl->next;
        }
        return nullptr;
    }
    
    int lenOfList(ListNode *curr) {
        int len = 0;
        for(; curr ; curr = curr->next, len++);
        return len;
    }
    
    /// Time  Complexity: O(?)
    /// Space Complexity: O(1)
    ListNode* solve1(ListNode *headA, ListNode *headB) {
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