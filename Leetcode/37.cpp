class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        canSolve(board);
    }
    
    bool canSolve(vector<vector<char>>& board, int c_row=0, int c_col=0) {
        /// next row
        if(c_col == board.size())
            return canSolve(board, c_row+1, 0);
        /// fill the final blank then get the solution
        if(c_row == board.size())
            return true;

        if('.' != board[c_row][c_col]) {
            return canSolve(board, c_row, c_col+1);
        } else {
            for(int digit=1; digit<=board.size(); digit++) {
                if(validSudoku(board, c_row, c_col, digit + '0')) {
                    board[c_row][c_col] = digit + '0';
                    if(canSolve(board, c_row, c_col+1))
                        return true;
                    board[c_row][c_col] = '.';
                }
            }
        }
        return false;

    }

    bool validSudoku(vector<vector<char>>& board, int row, int col, char c) {
        for(int i=0;i<9;i++)
        {
            if(board[row][i]==c)
                return false;
            if(board[i][col]==c)
                return false;
            
            if(board[3*(row/3)+i/3][3*(col/3)+i%3]==c)
            {
                return false;
            }
            
        }
       return true;
    }
};