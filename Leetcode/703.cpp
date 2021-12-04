class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : k_(k) {
        for(int num:nums)
            add(num);
    }
    
    int add(int val) {
        if(pq_.size() == k_ && val > pq_.top())
            pq_.pop();
        if(pq_.size() < k_)
            pq_.push(val);
        return pq_.top();
    }
private:
    int k_;
    priority_queue<int,vector<int>,greater<int>> pq_;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */