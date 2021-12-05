class MedianFinder {
public:
    MedianFinder() {
    }


    void addNum(int num) {
        updateMedian(num);
    }
    
    double findMedian() {
        return median_;
    }
private:
    
    /// Time Complexity: O(KN) that K = 5 * 10^4
    void updateMedian(int num) {
        /// Time  Complexity: O(N)
        /// Space Complexity: O(N)
        insert(num);
        /// initial
        if(data_.end() == curr_median_) {
            curr_median_ = data_.begin();
            median_ = *curr_median_;
        } else {
            ///  before    after
            ///   odd    -> even
            ///   3/2= 1    4/2 = 2    -> index of mean will + 1
            ///   1         2 & 2-1 
            ///             num <= median -> curr_median, prev(curr_median)
            ///             num >  median -> curr_median = next(curr_median)
            ///
            ///   even   -> odd        -> index of mean will keep the same
            ///   4/2= 2    5/2 = 2
            ///
            ///   2 & 2-1   2
            ///             num <= median  -> curr_median = prev(curr_median)
            ///             num >  median  -> curr_median
            if(size()%2 == 1) {
                if(num <= *curr_median_)
                    curr_median_ = prev(curr_median_);
                median_ = *curr_median_;
            } else {
                if(num > *curr_median_)
                    curr_median_ = next(curr_median_);
                median_ = (*curr_median_ + *prev(curr_median_)) / 2.0;
            }
        }
    }
    
    list<int>::iterator findInsertPos(int num) {
        /// always insert the same num in the left
        for(auto iter=data_.begin(); iter!=data_.end(); iter++)
            if(num <= *iter)
                return iter;
        return data_.end();
    }
    
    void insert(int num) {
        data_.insert(findInsertPos(num), num);
    }
    
    int size() {
        return data_.size();
    }
    
    list<int> data_;
    list<int>::iterator curr_median_ = data_.end();
    double median_;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */