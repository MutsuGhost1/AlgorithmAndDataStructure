class WordDictionary {
public:
    
    /// addWord("bad")
    ///
    /// addWord("dad")
    
    class Trie {
    public:
        void addWord(const string &s) {
            Trie *curr_node = this;
            for(char ch : s) {
                if(nullptr == curr_node->nexts[ch])
                    curr_node->nexts[ch] = new Trie();
                curr_node = curr_node->nexts[ch];
            }
            curr_node->is_word = true;
        }
        
        bool searchWord(const string &word) {
            return Trie::searchWord(this, word);
        }
    private:
        static bool searchWord(Trie *t, const string &word, int curr=0) {
            if(nullptr == t)
                return false;
            if(word.size() == curr)
                return t->is_word;
            if('.' != word[curr]) {
                return searchWord(t->nexts[word[curr]], word, curr+1);
            } else {
                for(int i=0; i<26; i++)
                    if(searchWord(t->nexts['a'+i], word, curr+1))
                        return true;
                return false;
            }
        }
        bool is_word = false;
        unordered_map<char,Trie*> nexts;
    };
    
    WordDictionary() {
        
    }
    
    void addWord(string word) {
        t.addWord(word);
    }
    
    bool search(string word) {
        return t.searchWord(word);
    }
private:
    Trie t;
};