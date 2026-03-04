class MyLinkedList {
public:

    class MyNode {
    friend class MyLinkedList;
    public:
        MyNode(int val) : val_(val), next_(nullptr), prev_(nullptr) {}
    private:
        int val_;
        MyNode *next_;
        MyNode *prev_;
    };
    
    MyLinkedList() : head_(nullptr), len_(0) {
    }

    int get(int index) {
        MyNode *curr = findNode(index);
        return curr ? curr->val_ : -1;
    }
    
    void addAtHead(int val) {
        MyNode *new_node = new MyNode(val);
        if(0 != len_) {
            new_node->next_ = head_;
            head_->prev_ = new_node;
        }
        head_ = new_node;
        len_++;
    }
    
    void addAtTail(int val) {
        if(0 == len_) {
            addAtHead(val);
        } else {
            /// len_ >= 1
            MyNode *tal_node = findNode(len_-1);
            MyNode *new_node = new MyNode(val);
            tal_node->next_ = new_node;
            new_node->prev_ = tal_node;
            len_++;
        }
    }
    
    void addAtIndex(int index, int val) {
        if(0 <= index && index <= len_) {
            if(0 == index) { /// when len_=1, the valid index only 0 or 1
                addAtHead(val);
            } else if (index == len_) {
                addAtTail(val);
            } else {
                /// 1 <= index < len_ -> 1 < len_
                MyNode *pre_node = findNode(index-1);
                MyNode *new_node = new MyNode(val);
                
                new_node->next_ = pre_node->next_;
                new_node->prev_ = pre_node;
                if(pre_node->next_)
                    pre_node->next_->prev_ = new_node;
                pre_node->next_ = new_node;
                len_++;
            }
        }
    }
    
    void deleteAtIndex(int index) {
        if(0 <= index && index < len_) {
            MyNode *del_node = nullptr;
            if(0 == index) {
                del_node = head_;
                head_ = head_->next_;
                if(head_)
                    head_->prev_ = nullptr;
            } else {
                MyNode *pre_node = findNode(index-1);
                del_node = pre_node->next_;
                pre_node->next_ = del_node->next_;
                if(del_node->next_)
                    del_node->next_->prev_ = pre_node;
            }
            delete del_node;
            len_--;
        }
    }
    
    friend ostream& operator<<(ostream &out, MyLinkedList &list); 
    
    void traverse(void(*cb_act)(void *context, int val), void *context) {
        if(nullptr == cb_act)
            return;
        MyNode *cur_node = head_;
        while(cur_node) {
            cb_act(context, cur_node->val_);
            cur_node = cur_node->next_;
        }
    }
    
private:
    
    MyNode* findNode(int index) {
        if(0 <= index && index < len_) {
            MyNode *curr = head_;
            while(0 < index) {
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

ostream& operator<<(ostream &out, MyLinkedList &my_list) {
    auto print_out = [](void *context, int val) {
        cout << "context:" << context << endl;
        cout << "val:" << val << endl;
    };
    my_list.traverse(print_out, &my_list);
    return out;
}


/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */