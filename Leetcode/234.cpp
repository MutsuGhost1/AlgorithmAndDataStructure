 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        front_=head;
        return solve1(head);
    }

    /// Time  Complexity: O(N)
    /// Space Complexity: O(1)
    bool solve1(ListNode* head) {
        int len=0;
        ListNode *lhead = findSecondHalf(head, len);
        if(1 == len)
            return true;
        /// 2. compare the first half and reverse second half
        bool res = true;
        lhead = reverseList(lhead);
        ListNode *first_half=head, *second_half=lhead;
        while(second_half) {
            if(second_half->val != first_half->val) {
                res = false;
                break;
            }
            second_half = second_half->next;
            first_half = first_half->next;
        }
        /// 3. restore
        reverseList(lhead);
        return res;        
    }
    
    /// findMiddle will give us the length of list and the head of next
    /// 1         -> m=1
    /// 1 2 3     -> m=2
    /// 1 2 3 4 5 -> m=3
    /// 1 2       -> m=2
    /// 1 2 3 4   -> m=3
    ListNode * findSecondHalf(ListNode *head, int &len) {
        len=0;
        ListNode *fast=head;
        while(fast && fast->next) {
            len += 2;
            fast = fast->next->next;
            head = head->next;
        }
        if(fast) {
            len++;
            /// without this line, it's also correct
            /// e.g.
            /// >  [1] -> [2] -> [1]
            ///            m
            ///           [1] -> [2]
            ///    [1] -> [2]
            /// it also works, except to compare with extra node
            head = head->next;        
        }
        return head;
    }
    
    /// [1] -> [2] -> [3]
    ///                p   c
    ListNode* reverseList(ListNode *curr, ListNode *prev=nullptr) {
        if(curr) {
            ListNode *head = reverseList(curr->next, curr);
            curr->next = prev;
            return head;
        }
        return prev;
    }

    bool solve2(ListNode* curr) {
        if(curr) {
            if(solve(curr->next)) {
                if(front_) {
                    ListNode *front = front_;
                    front_ = front_->next;
                    return front->val == curr->val;
                }
            }
            return false;
        }
        return true;
    }
private:
    ListNode *front_;
};