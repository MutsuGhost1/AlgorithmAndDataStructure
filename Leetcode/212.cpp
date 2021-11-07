class Solution {
public:
    
    class Trie {
        void insert(string &word) {
            Trie *curr = this;
            for(char ch : word) {
                if(!curr->next[ch])
                    curr->next[ch] = new Trie();
                curr = curr->next[ch];
            }
            curr->val = word;
        }
    private:
        string val;
        unordered_map<char, Trie*> next;
    friend class Solution;
    };
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie t;
        for(string &word : words)
            t.insert(word);
        set<string> s;
        for(int r=0; r<board.size(); r++)
            for(int c=0; c<board[0].size(); c++)
                solve(board, r, c, &t, s, words.size());
        return vector<string>(s.begin(), s.end());
    }
    
    void solve(vector<vector<char>>& board, int c_row, int c_col,
               Trie *t, set<string> &s, const int num) {
        char ch = board[c_row][c_col];
        if(!t || s.size() == num)
            return;
        if(!t->next[ch])
            return;
        /// can't pass edge case 
        /// [["a"]] & ["a"]
        /*
            if(0 != t->val.size())
                s.insert(t->val);
         */
        if(0 != t->next[ch]->val.size())
            s.insert(t->next[ch]->val);
        board[c_row][c_col] = '#';
        for(auto [o_r, o_c] : dirs) {
            int n_row = c_row+o_r, n_col = c_col+o_c;
            if(isValidCell(board, n_row, n_col) && '#' != board[n_row][n_col]) {
                solve(board, n_row, n_col, t->next[ch], s, num);
            }
        }
        board[c_row][c_col]=ch;
    }
    
    bool isValidCell(const vector<vector<char>>& board, int row, int col) {
        return 0 <= row && row < board.size() &&
               0 <= col && col < board[0].size();
    }

    const vector<pair<int,int>> dirs = { {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
};