class MyLinkedList {
public:

    class MyNode {
    friend class MyLinkedList;
    public:
        MyNode(int val) : val_(val), next_(nullptr) {}
    private:
        int val_;
        MyNode *next_;
    };
    
    MyLinkedList() : head_(nullptr), len_(0) {
    }

    int get(int index) {
        MyNode *curr = findNode(index);
        return curr ? curr->val_ : -1;
    }
    
    void addAtHead(int val) {
        MyNode *new_node = new MyNode(val);
        new_node->next_ = head_;
        head_ = new_node;
        len_++;
    }
    
    void addAtTail(int val) {
        /// error - 1
        if(0 == len_)
            addAtHead(val);
        else {
            MyNode *last = findNode(len_-1);
            last->next_ = new MyNode(val);
            len_++;
        }
    }
    
    void addAtIndex(int index, int val) {
        /// errr 2 -> can add index = len
        if(0 <= index && index <= len_) {
            if(0 == index)
                addAtHead(val);
            else if(index == len_+1)
                addAtTail(val);
            else {
                /// pre_node never be nullptr
                MyNode *pre_node = findNode(index-1);
                MyNode *new_node = new MyNode(val);
                new_node->next_ = pre_node->next_;
                pre_node->next_ = new_node;
                len_++;
            }            
        }
    }
    
    void deleteAtIndex(int index) {
        if(0 <= index && index < len_) {
            MyNode *del_node = nullptr;
            /// index = 0 && _len > 1
            if(0 == index) {
                del_node = head_;
                head_ = del_node->next_;
            } else {
            /// 1 <= index < len_
                MyNode *pre_node = findNode(index-1);
                del_node = pre_node->next_;
                pre_node->next_ = del_node->next_;
            }
            delete del_node;
            len_--;
        }
    }
private:
    
    MyNode* findNode(int index) {
        if(0 <= index && index < len_) {
            MyNode *curr = head_;
            while(0 < index && curr) {
                curr = curr->next_;
                index--;
            }
            return curr;            
        }
        return nullptr;
    }
    
    MyNode *head_;
    int len_;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */