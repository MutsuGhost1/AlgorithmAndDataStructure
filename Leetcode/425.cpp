class Solution {
public:
    
    class Trie {
        
    };
    
    vector<vector<string>> wordSquares(vector<string>& words) {
        /// words = ["area","lead","wall","lady","ball"]
        ///
        /// "ball",
        /// "area", [1][0]
        /// "lead", [2][0], [2][1]
        /// "lady"  [3][0], [3][1], [3][2]
        vector<bool> visited(words.size(), false);
        vector<string> tmp;
        vector<vector<string>> ans;
        solve(words, visited, tmp, ans);
        return ans;
    }
    
    void solve(vector<string>& words, vector<string> &tmp, vector<vector<string>> &ans) {
        if(tmp.size() == words[0].size()) {
            ans.push_back(tmp);
            return;
        }
        for(int i=0; i<words.size(); i++) {
            if(!visited[i]) {
                bool is_skip=false;
                /// TODO: 
                //    > we can use Trie to speed up the process
                for(int j=0; j<tmp.size(); j++)
                    if(words[i][j] != tmp[j][tmp.size()]) {
                        is_skip=true;
                        break;
                    }
                if(is_skip)
                    continue;
                tmp.push_back(words[i]);
                solve(words, visited, tmp, ans);
                tmp.pop_back();
            }
        }
    }
};