class MyHashMap {
public:
    using PII = pair<int,int>;

    MyHashMap() {
        
    }
    
    void put(int key, int value) {
        if(auto iter=find(key); iter!=end(key)) {
            iter->second = value;
        } else {
            buckets[hash(key)].push_back(make_pair(key, value));
        }
    }
    
    int get(int key) {
        if(auto iter=find(key); iter!=end(key))
            return iter->second;
        return -1;
    }
    
    void remove(int key) {
        if(auto iter=find(key); iter!=end(key))
            buckets[hash(key)].erase(iter);
   }
    

private:
    
    int hash(int key) {
        return key % kBucketNum;
    }

    list<PII>::iterator find(int key) {
        return find_if(buckets[hash(key)].begin(),
                       buckets[hash(key)].end(), 
                       [key](PII &p){
                           return p.first == key;
                       });
    }
    
    list<PII>::iterator end(int key) {
        return buckets[hash(key)].end();
    }
    
    static const int kBucketNum = 1001;
    array<list<PII>, kBucketNum> buckets;
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */