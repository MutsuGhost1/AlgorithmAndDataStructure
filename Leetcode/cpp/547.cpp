class Solution {
public:
    
    void dfs(vector<vector<int>> &neighbors, vector<bool> &visited, int cur,
             vector<int> *p_path=NULL) {
        visited[cur] = true;
        if(p_path) p_path->push_back(cur);
        for(auto neighbor : neighbors[cur])
            if(!visited[neighbor])
                dfs(neighbors, visited, neighbor, p_path);
    }
    
    int findCC(int v_num, vector<vector<int>> &neighbors, vector<vector<int>> *p_ccs=NULL) {
        int cnt=0;
        vector<bool> visited(v_num, false);
        for(int i=0; i<visited.size(); i++) {
            if(!visited[i]) {
                cnt++;
                if(p_ccs) p_ccs->push_back(vector<int>()); 
                dfs(neighbors, visited, i, p_ccs ? &p_ccs->back() : NULL);
            }
        }
        return cnt;
    }
    
    int findCircleNum(vector<vector<int>>& board) {
        vector<vector<int>> neighbors(board.size());
        for(int i=0; i<board.size(); i++)
            for(int j=0; j<board[0].size(); j++)
                if(1 == board[i][j])
                    neighbors[i].push_back(j);
        // vector<vector<int>> ccs;
        return findCC(board.size(), neighbors/*, &ccs*/);
    }
};

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        /// 1. use dfs traverse border cell and mark its cc as '#'
        row_num = board.size(), col_num = board[0].size();
        const char tmp_label='#';
        for(int col=0; col<col_num; col++) {
            if('O' == board[0][col])
                dfsMark(board, 0, col, tmp_label);
            if('O' == board[row_num-1][col])
                dfsMark(board, row_num-1, col, tmp_label);
        }
        for(int row=0; row<row_num; row++) {
            if('O' == board[row][0])
                dfsMark(board, row, 0, tmp_label);
            if('O' == board[row][col_num-1])
                dfsMark(board, row, col_num-1, tmp_label);
        }
        /// 2. check all symbol in board
        ///    a. process cc reach the border 
        ///       -> change '#' to 'O'
        ///    b. process cc doesn't reach the border
        ///       -> change 'O' to 'X'
        for(int row=0; row<row_num ; row++)
            for(int col=0; col<col_num; col++)
                switch(board[row][col]){
                    case tmp_label:
                        board[row][col] = 'O';
                    break;
                    case 'O':
                        board[row][col] = 'X';
                    break;
                }
    }
    
    void dfsMark(vector<vector<char>>& board, int c_row, int c_col, char label) {
        board[c_row][c_col] = label;
        for(auto [o_r, o_c] : dirs) {
            int n_row=c_row+o_r, n_col=c_col+o_c;
            if(isValidCell(n_row, n_col) && 'O' == board[n_row][n_col])
                dfsMark(board, n_row, n_col, label);
        }
    }
    
    bool isValidCell(int row, int col) {
        return 0 <= row && row < row_num && 0 <= col && col < col_num;
    }
    
    bool isBorderCell(int row, int col) {
        return 0 == row || 0 == col || row == row_num-1 || col == col_num-1;
    }
    
    int row_num;
    int col_num;
    const vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
};