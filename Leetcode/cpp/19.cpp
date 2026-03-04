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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        return solve2(head, n);
    }
    
    ListNode* solve2(ListNode* head, int n) {
        ListNode *fast=head, *slow=head;
        /// guarantee len >= 1
        /// if(!head) return nullptr;
        
        while(0 < n && fast->next) {
            fast = fast->next;
            n--;
        }
        
        if(0 < n) {
            /// when n == length -> delete first element
            if(1 == n) {
                head = head->next;
                return head;     
            }
            /// invalid parameters, throw exceptions
            return head;
        }

        /// n < length
        ///
        /// [1]->[2], n=1
        while(fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;

        return head;
    }
    
    /// The navie approach
    /// 1. use fast/slow pointer
    /// 2. the slow pointer will go when the fast pointer has run n steps
    /// ...
    ListNode* solve1(ListNode* head, int n) {
/*
        The number of nodes in the list is sz.
          1 <= sz <= 30
          0 <= Node.val <= 100
          1 <= n <= sz
 */
        ///         V        
        /// [ 1, 2, 3, 4, 5], n=2
        ///  f/s
        ///   s  f            n=1
        ///   s     f         n=0
        ///      s     f
        ///         s     f
        ListNode *fast=head, *slow=head;
        while(fast->next) {
            fast = fast->next;
            if(0 >= n)
                slow = slow->next;
            else
                n--;
        }
        /// remove first node
        if(slow == head) {
            /// only one node
            if(nullptr == slow->next)
                head = nullptr;
            else {
                /// how to distinguish 2/2 and 2/1
                if(0 == n) /// 2/1
                    if(nullptr != head->next)
                        head->next = head->next->next;
                    else
                        head->next = nullptr;
                else
                    head = slow->next;
            }
        } else {
            slow->next = slow->next->next;
        }
        
        return head;        
    }
};