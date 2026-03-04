class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        kRowNum = grid.size();
        kColNum = grid[0].size();
        
        int fresh_cnt = 0;
        queue<pair<int,int>> q;
        for(int row=0; row<kRowNum; row++)
            for(int col=0; col<kColNum; col++)
                switch(grid[row][col]) {
                    case 1:
                        fresh_cnt++;
                    break;
                    case 2:
                        q.push({row, col});
                    break;
                }
    
        if(0 == fresh_cnt)
            return 0;

        int minutes = 0;
        while(!q.empty()) {
            minutes++;
            for(int i=0, lvl_num=q.size(); i<lvl_num; i++) {
                auto [c_row, c_col] = q.front();
                q.pop();
                for(auto [o_r, o_c] : dirs) {
                    int n_row = c_row + o_r, n_col = c_col + o_c;
                    if(isValidCell(n_row, n_col) && 1 == grid[n_row][n_col]) {
                        if(0 == --fresh_cnt)
                            return minutes;
                        grid[n_row][n_col] = 2;
                        q.push({n_row, n_col});
                    }
                }
            }
        }
        return -1;
    }

    bool isValidCell(int row, int col) {
        return 0 <= row && row < kRowNum && 0 <= col && col < kColNum;
    }
    
    vector<pair<int, int>> dirs = {{ 1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int kRowNum;
    int kColNum;
};

/// Time Complexity: O(MN)
///   1. Scan all the cells in the grid                               -> O(M*N)
///   2. Run BFS and the worst case is all the cells put in the queue -> O(M*N)
///   therefore, O(2MN) = O(MN)
/// Space Complexity: O(MN)
///   1. The worst case is the q is filled with all the rotten orange -> O(M*N)