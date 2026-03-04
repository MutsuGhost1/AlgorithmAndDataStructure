class Solution {
public:
        
    bool exist(vector<vector<char>>& board, string word) {
        for(int i=0; i<board.size(); i++)
            for(int j=0; j<board[0].size(); j++)
                if(solve(board, i, j, word))
                    return true;
        return false;
    }
    
    bool solve(vector<vector<char>>& board, int c_row, int c_col, string word) {
        char ch = board[c_row][c_col];
        if(ch != word[0])
            return false;
        if(ch == word[0] && 1 == word.size())
            return true;
        board[c_row][c_col] = '#';
        for(auto [o_r, o_c] : dirs) {
            int n_row = c_row+o_r, n_col = c_col+o_c;
            if(isValidCell(board, n_row, n_col) && '#' != board[n_row][n_col])
                if(solve(board, n_row, n_col, word.substr(1))) {
                    board[c_row][c_col] = ch;
                    return true;
                }
        }
        board[c_row][c_col] = ch;
        return false;
    }
    
    bool isValidCell(const vector<vector<char>>& board, int row, int col) {
        return 0 <= row && row < board.size() &&
               0 <= col && col < board[0].size();
    }
    
    const vector<pair<int,int>> dirs = { {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
};
