class Solution {
public:
    
    class Trie {
    public:
        void insert(string &word) {
            Trie *curr = this;
            curr->prefix_strs.push_back(word);
            for(char ch : word) {
                if(!curr->next[ch])
                    curr->next[ch] = new Trie();
                curr = curr->next[ch];
                curr->prefix_strs.push_back(word);
            }
        }
        
        vector<string> findPrefixStrs(string &prefix) {
            Trie *node = findNode(this, prefix);
            return node ? node->prefix_strs : vector<string>();
        }
        
    private:
        static Trie* findNode(Trie* curr, string &prefix) {
            for(char ch : prefix) {
                if(!curr->next[ch])
                    return nullptr;
                curr = curr->next[ch];
            }
            return curr;
        }
        vector<string> prefix_strs;
        unordered_map<char,Trie*> next;
    };
    
    vector<vector<string>> wordSquares(vector<string>& words) {
        /// words = ["area","lead","wall","lady","ball"]
        ///
        /// "ball",
        /// "area", [1][0]
        /// "lead", [2][0], [2][1]
        /// "lady"  [3][0], [3][1], [3][2]
        Trie t;
        for(auto word : words)
            t.insert(word);
        vector<string> tmp;
        vector<vector<string>> ans;
        solve(t, words[0].size(), tmp, ans);
        return ans;
    }
    
    /// approach 1 - backtracking without Trie (TLE)
    void solve(vector<string>& words,
               vector<string> &tmp, vector<vector<string>> &ans) {
        if(tmp.size() == words[0].size()) {
            ans.push_back(tmp);
            return;
        }
        for(int i=0; i<words.size(); i++) {
            /// TODO: 
            //    > we can use Trie to speed up the process
            string prefix;
            for(int j=0; j<tmp.size(); j++)
                prefix += tmp[j][tmp.size()];
            if(0 != words[i].compare(0, tmp.size(), prefix))
                continue;
            tmp.push_back(words[i]);
            solve(words, tmp, ans);
            tmp.pop_back();
        }
    }
    
    /// approach 2 - backtracking with Trie
    void solve(Trie &t, const int num, vector<string> &tmp, vector<vector<string>> &ans) {
        if(tmp.size() == num) {
            ans.push_back(tmp);
            return;
        }
        string prefix;
        for(int j=0; j<tmp.size(); j++)
            prefix += tmp[j][tmp.size()];
        vector<string> words = t.findPrefixStrs(prefix);
        for(int i=0; i<words.size(); i++) {
            tmp.push_back(words[i]);
            solve(t, num, tmp, ans);
            tmp.pop_back();
        }
    }    
};