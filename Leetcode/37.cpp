class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        canSolve(board);
    }
    
    bool canSolve(vector<vector<char>>& board, int c_row=0, int c_col=0) {
        /// get the solution
        if(c_row == board.size())
            return true;

        int n_row = c_row + (c_col+1)/board.size();
        int n_col = (c_col+1)%board.size();
        if('.' != board[c_row][c_col]) {
            return canSolve(board, n_row, n_col);
        } else {
            for(int digit=1; digit<=board.size(); digit++) {
                board[c_row][c_col] = digit + '0';
                if(validRowCol(board, c_row, c_col) && validGroup(board, c_row, c_col)) {
                    if(canSolve(board, n_row, n_col))
                        return true;
                }
                board[c_row][c_col] = '.';
            }
        }
        return false;
    }
    
    bool validRowCol(vector<vector<char>>& board, int c_row, int c_col) {
        vector<int> r_visited(board.size(), 0);
        vector<int> c_visited(board.size(), 0);
        for(int i=0; i<board.size(); i++) {
            if('.' != board[c_row][i]) {
                if(0 != r_visited[board[c_row][i]-'1']) {
                    return false;
                } else
                    r_visited[board[c_row][i]-'1']++;
            }
            if('.' != board[i][c_col]) {
                if(0 != c_visited[board[i][c_col]-'1']) {
                    return false;
                } else
                    c_visited[board[i][c_col]-'1']++;
            }
        }
        return true;
    }
        
    bool validGroup(vector<vector<char>>& board, int c_row, int c_col) {
        vector<int> visited(board.size(), 0);
        int s_row=c_row/3*3, s_col=c_col/3*3;
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++){
                if('.' != board[s_row+i][s_col+j]) {
                    if(0 != visited[board[s_row+i][s_col+j]-'1']) {
                        return false;
                    } else
                        visited[board[s_row+i][s_col+j]-'1']++;                    
                }
            }
        }
        return true;           
    }
};