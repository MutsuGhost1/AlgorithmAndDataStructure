class AutocompleteSystem {
public:
    class Trie{
    friend class AutocompleteSystem;
    public:
        void insert(const string &word) {
            Trie *cnode = this;
            for(char c : word) {
                if(nullptr == cnode->nodes[c])
                    cnode->nodes[c] = new Trie();
                cnode = cnode->nodes[c];
                cnode->strs.push_back(word);
            }
        }
        vector<string> getStrCandidates(const string &prefix) {
            Trie *cnode = this;
            for(char c : prefix) {
                if(nullptr == cnode->nodes[c])
                    return vector<string>();
                cnode = cnode->nodes[c];
            }
            return cnode->strs;
        }
    private:
        vector<string> strs;
        unordered_map<char,Trie*> nodes;
    };
    
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        for(int i=0; i<times.size(); i++) {
            cnt[sentences[i]] = times[i];
            t.insert(sentences[i]);
        }
    }
    
    vector<string> getStrCandidates(const string &prefix, int num=3) {
        vector<string> strs = t.getStrCandidates(prefix);
        sort(strs.begin(), strs.end(),
             [&](string &s1, string &s2){
                 return cnt[s1] == cnt[s2] ? s1 < s2 : cnt[s1] > cnt[s2];
             });
        return strs.size() > num ? vector<string>(strs.begin(), strs.begin()+num) : strs;
    }
    
    vector<string> input(char c) {
        if('#' != c) {
            buffer += c;
            return getStrCandidates(buffer);
        } else {
            if(0 == cnt[buffer])
                t.insert(buffer);
            cnt[buffer]++;
            buffer="";
            return vector<string>();
        }
    }
    
    private:
    Trie t;
    string buffer;
    unordered_map<string, int> cnt;
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */