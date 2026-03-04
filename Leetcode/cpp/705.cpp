class MyHashSet {
public:
    MyHashSet() {
    }
    
    void add(int key) {
        if(!contains(key))
            buckets[hash(key)].push_back(key);
    }
    
    void remove(int key) {
        if(auto iter = findPos(key); iter != end(key))
            buckets[hash(key)].erase(iter);
    }
    
    bool contains(int key) {
        return findPos(key) != end(key);
    }
        
private:
    
    int hash(int key) {
        return key % kBucketNum;
    }

    list<int>::iterator findPos(int key) {
        return find(buckets[hash(key)].begin(), buckets[hash(key)].end(), key);
    }
    
    list<int>::iterator end(int key) {
        return buckets[hash(key)].end();
    }
    
    static const int kBucketNum = 1001;
    array<list<int>, kBucketNum> buckets;
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */